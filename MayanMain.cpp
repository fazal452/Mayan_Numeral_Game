#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;


// Global Variables
const int ARR_SIZE = 3;
const int MAYA_BASE = 20;
const int VAL_PER_LINE = 5;
const int VAL_PER_DOT = 1;
const int VAL_PER_SHELL = 0;
const int BLACK_DOT = 254;
const int BLACK_BAR = 223;
const string SHELL = "(/)";

// Mayan Numeral Functions

//Find Max Degree of Any given number respective to its base(2,10,16....)
int max_divisor(int decimal_number, int base);

//Print Mayan Symbools from 0-19 (lines and dots and shell)
void print_mayan_symbol(int mayan_digit);

//Print out complete mayan number with different Base Places and symbols
void print_mayan_number(int decimal_number);


// Game Functions

//Shuffle a 3x1 Matrix in Place in order to create random order
void array_shuffler(int arr[]);

//Return a uniformly random number within a given range
int rand_value_gen(int min, int max);

//Mayan Number Game with choices and combination of different function
int choosing_game();


int main()
{

	print_mayan_number(5212);
	cout << "\n\n";

	//Commence Game
	choosing_game();

	return(0);

}

//-------------CODE FOR MAYAN CONVERSION-------------//
int max_divisor(int decimal_number, int base) {
	//Set max power to 0
	int max_divisor_power = 0;

	int remainder = decimal_number;

	while (remainder >= base) {

		//increment power if remainder is divisble by base
		remainder = decimal_number / pow(base, max_divisor_power + 1);
		max_divisor_power++;
	}

	//return max degree
	return(max_divisor_power);
}

void print_mayan_symbol(int mayan_digit) {

	//Get 0 case out of the way
	if (mayan_digit == VAL_PER_SHELL) {
		cout << (SHELL);
	}

	//Get num of lines and dots to be printed
	int num_of_lines = 0;
	int num_of_dots = 0;

	num_of_lines = mayan_digit / VAL_PER_LINE;
	num_of_dots = mayan_digit % VAL_PER_LINE;

	//Print out dots
	for (int i = 0; i < num_of_dots; i++) {
		cout << char(BLACK_DOT) << " ";
	}
	//Add a space if lines follow the dots
	if (num_of_dots > 0 && num_of_lines != 0) {
		cout << endl;
	}

	//Print out lines
	for (int i = 0; i < num_of_lines; i++) {

		//PRINT BAR
		for (int i = 0; i < 7; i++) {
			cout << char(BLACK_BAR);
		}
		//Only add space if not last line in sequence
		if (num_of_lines - 1 - i > 0) {
			cout << endl;
		}
	}

}

void print_mayan_number(int decimal_number) {

	//Store max degree and value entered
	int max_degree = max_divisor(decimal_number, MAYA_BASE);
	int remainder = decimal_number;

	//Go through degrees from top to bottom
	while (max_degree >= 0) {

		//Store and print digit in degrees place
		int value = remainder / int(pow(MAYA_BASE, max_degree));

		print_mayan_symbol(value);

		//Print divider only if not the last degrees
		if (max_degree != 0) {
			cout << endl << "-------" << endl;
		}

		//Calculate value to be placed in lower degree
		remainder = remainder - (value) * (int(pow(MAYA_BASE, max_degree)));

		//Decrement max degree currently dealt with
		max_degree--;
	}

}

//-------------------CODE FOR GAME-------------------//
int rand_value_gen(int min, int max) {
	//This Function has many different calculations to try and get as uniform distribution possible


	srand(time(NULL));

	//Create an array with list of 10 random numbers
	//Made sure the max number stored is less than 2^31
	int rand_arr[10];

	for (int i = 0; i < 10; i++) {
		rand_arr[i] = rand() * pow(i, 4);
	}

	//Randomize number as uniform as I can, without going over 2^31 in any calculations, even if number generated is far less 
	//Just Create a very random number
	int first_seed = pow(rand_arr[(rand() % 10)] % int(sqrt(pow(2, 31))), 2);

	//Reduce the random number to fit within given range
	int middle = max - min;
	int random_number = min + (first_seed % (middle + 1));

	return(random_number);
}

void array_shuffler(int arr[]) {

	//Shuffle a 3x1 Array in Place
	//3x1 Since that is the number of options(A,B,C)
	arr[ARR_SIZE - 3] = 0; arr[ARR_SIZE - 2] = 0; arr[ARR_SIZE - 1] = 0;

	//Keep shuffling until arr is acceptable
	while (arr[0] == arr[1] || arr[1] == arr[2] || arr[2] == arr[0]) {

		arr[ARR_SIZE - 3] = rand_value_gen(0, 5) % 3;
		arr[ARR_SIZE - 2] = rand_value_gen(5, 10) % 3;
		arr[ARR_SIZE - 1] = rand_value_gen(10, 15) % 3;
	}

}

int choosing_game() {

	cout << "Welcome to the Mayan Number Game! " << endl;

	//Store game variables
	bool game_is_active = true;
	int times_played = 0;


	while (game_is_active) {

		// Change text based on whether its first time or not
		if (times_played == 0) {
			cout << "Enter a number greater than or equal to 10 to play. OR less than to quit \nEnter here: ";
		}

		else {
			cout << "\nEnter another number greater than or equal to 10 to play. OR less than to quit \nEnter here: ";
		}

		//Ask for users input
		int user_number = 0;
		cin >> user_number;

		//Input Checking
		while (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "You have enter wrong type input, Try again: ";
			cin >> user_number;
			cout << endl;
		}

		//clear input stream
		cin.clear();
		cin.ignore(10000, '\n');

		// Check to make sure if number is within range
		if (user_number < 10) {
			game_is_active = false;
			cout << "Game Ended";
			return(0);
		}


		// Create three values to become options
		int actual = 0;
		int fake_1 = 0;
		int fake_2 = 0;


		//Generate 3 different numbers based off users input
		actual = rand_value_gen(4, user_number);
		fake_1 = rand_value_gen(actual / 2, actual * 3 / 2);
		fake_2 = rand_value_gen(actual / 2, actual * 3 / 2);

		//Keep assigning values to fake1 or fake2 till they are all distinct
		while (fake_1 == actual || fake_1 == fake_2 || fake_2 == actual) {
			fake_1 = rand_value_gen(actual / 2, actual * 3 / 2);
			fake_2 = rand_value_gen(actual / 2, actual * 3 / 2);
		}


		/*
		//Print out all 3 random variables
		cout << endl;
		cout << "actual = " << actual << endl;
		cout << "first fake = " << fake_1 << endl;
		cout << "second fake = " << fake_2 << endl;
		cout << endl;
		*/

		// Create array in order to jumble thier order
		int arr_options[] = { actual, fake_1, fake_2 };
		int arr_order[ARR_SIZE];

		//Shuffle around array
		array_shuffler(arr_order);

		//Create options based of shuffled order
		int option_a = arr_options[arr_order[0]];
		int option_b = arr_options[arr_order[1]];
		int option_c = arr_options[arr_order[2]];

		//Print out options
		cout << endl << "Which one of these Mayan numbers is equal to " << actual << "?" << endl;

		cout << "option A is:" << "\n\n";
		print_mayan_number(option_a);

		cout << "\n\n" << "option B is:" << "\n\n";
		print_mayan_number(option_b);

		cout << "\n\n" << "option C is:" << "\n\n";
		print_mayan_number(option_c);


		//Store correct answer
		char answer;

		if (option_a == actual) {
			answer = 'a';
		}
		else if (option_b == actual) {
			answer = 'b';
		}
		else if (option_c == actual) {
			answer = 'c';
		}

		//Ask for guess
		cout << "\n\nWhat is your guess? A, B or C? \nEnter here: ";

		char guess;
		cin >> guess;
		guess = tolower(guess);

		//clear input stream
		cin.clear();
		cin.ignore(10000, '\n');

		while (guess != 'a' && guess != 'b' && guess != 'c') {
			cout << "entered wrong input\nTry again: ";
			cin >> guess;
			guess = tolower(guess);
			cin.clear();
			cin.ignore(10000, '\n'); //clear input stream
		}

		//Check if input is correct
		if (guess == answer) {
			cout << "\nCORRECT! ";
		}
		else {
			cout << "\nINCORRECT!! ";
		}

		//Inform the correct answer
		cout << "The correct representation of the Mayan Number of " << actual << " is: \n\n";
		print_mayan_number(actual);

		//Increment no. of games played
		times_played++;
		cout << endl;
	}

	return(0);
}
