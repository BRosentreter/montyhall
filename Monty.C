#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <vector>

using namespace std;

// three doors, prize behind one

int getRand13() {
	return rand() % 3;
}

int getRand12() {
	return rand() % 2;
}

struct MontyRun {
	bool doors[3]; // doors, 0 if no prize, 1 if prize
	bool open; // true if door has been opened
	bool won; // true if run won

	MontyRun() {
	// initialize
		doors[0] = doors[1] = doors[2] = false;
		doors[getRand13()] = true;
		open = false;
		won = false;
	}

	int getHint(int guess) {
		int doorSkips = getRand12(); // open the first door or the second
		int numSkips = 0;
		while(1){
			doorSkips = getRand12();
			numSkips = 0;
			for (int i = 0; i < 3; i++) {
				if (doors[i] == false && numSkips == doorSkips && i != guess) {
					return i;
				}
			if (doors[i] == true) continue;
				numSkips++;
			}
		}
		return -1;
	}

	bool getWon() { 
		return won; 
	}

};

double monty(unsigned num_runs, bool switch_doors) {
	vector<MontyRun> runs(num_runs);
	for (int i = 0; i < runs.size(); i++) {
		int guess = getRand13(); // we guess a door [0,1,2]
		int hint = runs[i].getHint(guess); // they open a door 'hint'
		if (switch_doors) {
			int new_guess = guess;
			while (new_guess == guess || new_guess == hint) {
				new_guess = ((new_guess + 1) % 3);
			}
			guess = new_guess;
		}
		if (runs[i].doors[guess]) runs[i].won = true;
	}
	int wins_total = 0;
	for (auto it : runs) { wins_total += it.getWon(); }
	cout << "Total Wins: " << wins_total << endl;
	return static_cast<double>(wins_total) / static_cast<double>(runs.size());
}

int main(int argc, char * argv[]) {
	srand (time(NULL));
	int num_runs = atoi(argv[1]);
	int switch_doors = atoi(argv[2]);
	cout << monty(num_runs, switch_doors > 0 ? true : false);
	cout << endl;
	return 0;
}
