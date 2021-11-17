// This program adds two large integers, and prints the result to the screen

#include <cctype>
#include <iostream>
using namespace std;

// Max number of digits in the large integer
const int MAXSIZE = 25;

// Initializes an integer array so that all positions are holding the value zero.
void initArray(int array[]);

// Gets a large integer from the keyboard and stores each individual digit
// into the array.
void getNum(int array[]);

// Prints a large integer to the screen. Leading zeros are not printed.
void printNum(int array[]);


int main()
{
	// TODO: Write code for the main function
	int number1[MAXSIZE];	// Array that holds first number to be added.
	int number2[MAXSIZE];	// Array that holds second number to be added.
	int sum[MAXSIZE];	// Array that holds the sum of inputted numbers.
	int carry = 0;	// Keeps track of whether the addition code needs to carry a one.
	int temp = 0;	// Stores the ones digit of the sum of each integer in input arrays.
	bool intoverflow = false;
	do
	{
		// Initializing arrays and storing user input into arrays.
		initArray(number1);
		initArray(number2);
		initArray(sum);
		getNum(number1);
		getNum(number2);

		// Calculating sum of arrays number1 and number2 and storing the sum in the sum array.
		// Calculating the sum one digit at a time and using a variable to carry a one if needed.
		for (int i = MAXSIZE - 1; i >= 0; i--)
		{
			temp = number1[i] + number2[i] + carry;
			carry = temp / 10;
			temp = temp % 10;
			sum[i] = temp;
		}

		// Check if sum is too large and print sum to screen.
		if (carry != 0)
		{
			cout << "Integer overflow" << endl;
			intoverflow = true;
		}
		else
		{
			intoverflow = false;
			cout << "The sum is: ";
			printNum(sum);
			cout << endl;
		}
	} while (intoverflow == true);

	cout << endl;
	return 0;
}


void initArray(int array[])
{
	// TODO: Write code for the function
	// Sets every entry in the array to zero.
	for (int i = 0; i < MAXSIZE; i++)
	{
		array[i] = 0;
	}
}


void printNum(int array[])
{
	// TODO: Write code for the function
	bool leadingZero = true;	// Variable used to keep track of when the for loop is done cycling through leading zeroes in array.

	// For loop cycles through entries in an array, outputting integers after leading zeroes.
	for (int i = 0; i < MAXSIZE; i++)
	{
		if (leadingZero == true)
		{
			if (array[i] != 0)
			{
				leadingZero = false;
			}
		}
		if (leadingZero == false)
		{
			cout << array[i];
		}
	}
	cout << endl;
}


void getNum(int array[])
{
	char input[MAXSIZE + 1];
	int length;
	bool inputOkay;

	do
	{
		inputOkay = true;

		cout << "Enter an integer: ";
		cin.getline(input, MAXSIZE + 1);

		// If user entered more than the max number of digits
		// then make them enter the large integer again
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Integer too long\n";
			cout << "Enter an integer: ";
			cin.getline(input, MAXSIZE + 1);
		}

		// Check to ensure that the user did not enter any non-digit values
		length = strlen(input);
		for (int x = 0; x < length && inputOkay; x++)
		{
			if (!isdigit(input[x]))
			{
				inputOkay = false;
				cout << "Invalid input\n";
			}
		}

	} while (!inputOkay);


	// TODO: Write code for the remaining portion of the function
	bool stringStart = false; // Used to start inputting integers into array once "\0" is found in the input array.
	int arrayCounter = MAXSIZE - 1; // Used to keep track of where in the parameter array integers should be stored.

	// For loop looks backwards in input array until it finds the ASCII value for "\0".
	// It then converts character values from input into integer values and stores them in the parameter array.
	for (int i = MAXSIZE; i >= 0; i--)
	{
		if (stringStart == true)
		{
			array[arrayCounter] = input[i] - 48;
			arrayCounter -= 1;
		}
		if (input[i] == 0)
		{
			stringStart = true;
		}
	}

}