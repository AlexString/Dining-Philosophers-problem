#include <iostream>
#include <random>
#include <ctime>
#include <mutex>
#include <thread>

#define no_philosophers 5

class PhilosophersProblem{
private:
	// Main attributes
	/* 	Properties description:
			timeOuts: list of times that each philosopher is going to end eating. 
			Forks: These need to be blocked so they have mutex.
	*/
	int timeOuts[no_philosophers];
	struct Forks{
		public:
			Forks(){;}
			std::mutex mu_handler;
	};
	
	// ---- Main functioning ---- 
	void proceed();

	// 	Setting timeouts
	void setData();
	// 	Displays philosophers end times
	void displayDetails();

public:

	PhilosophersProblem();
	~PhilosophersProblem();
	void execute();
};

void PhilosophersProblem::proceed(){
	//  lambda function for threading 
	auto eat = [](Forks &left_fork, Forks& right_fork, int philosopher_number, int timeOut) {
		// locking forks 
		std::unique_lock<std::mutex> llock(left_fork.mu_handler); 
		std::unique_lock<std::mutex> rlock(right_fork.mu_handler);
		
		std::cout << "Philosopher [" << philosopher_number << "] is eating..." << std::endl;

		// Setting release time of the locks of this thread.	
		std::chrono::milliseconds endTime(timeOut*1000);
		std::this_thread::sleep_for(endTime);
		
		std::cout << "** Philosopher [" << philosopher_number << "] has finished eating." << std::endl;
	};

	// Create forks
	Forks fork_list[no_philosophers];
	// Create philosophers
	std::thread philosopher[no_philosophers];

	// First philosopher start thinking
	std::cout << "Philosopher [1] is thinking..." << std::endl;
	philosopher[0] = std::thread(eat, std::ref(fork_list[0]), std::ref(fork_list[no_philosophers-1]), (0+1), timeOuts[0]);

	// Threading all philosophers left
	for(int i = 1; i < no_philosophers; ++i) {
		std::cout << "Philosopher [" << (i+1) << "] is thinking..." << std::endl;
		philosopher[i] = std::thread(eat, std::ref(fork_list[i]), std::ref(fork_list[i-1]), (i+1), timeOuts[i]);
	}
	// Join them all 
	for(auto &ph: philosopher) {
		ph.join();
	}

}

PhilosophersProblem::PhilosophersProblem(){
	setData(); 
	std::cout << "The philosophers have sat on the table."<< std::endl<<std::endl;
	displayDetails();
}

PhilosophersProblem::~PhilosophersProblem(){}

void PhilosophersProblem::execute(){
	proceed();
}

void PhilosophersProblem::setData(){
	// Setting random end time to philosophers and remaining time
	std::srand(std::time(nullptr));
	for(int i=0; i<no_philosophers; i++)
		timeOuts[i] = rand() % (10)+2; // Random number 
}

void PhilosophersProblem::displayDetails(){
	std::cout << "Philosopher\t Time to finish eating:" << std::endl;	
	for(int i=0; i<no_philosophers; i++)
		std::cout << i+1 << "\t\t\t" << timeOuts[i] << std::endl;
	
}
