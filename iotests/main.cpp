//
//  main.cpp
//  iotests
//
//  Created by Valentine on 06.09.13.
//  Copyright (c) 2013 silvansky. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

std::string symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// integer power
int powi(int number, int power)
{
	return (int)std::pow(number, power);
}

// number for symbol (0-9, A-Z)
int numberFromSymbol(char symbol)
{
	if (isdigit(symbol))
	{
		return atoi(&symbol);
	}
	return symbol - 'A' + 10;
}

// convert to numeric system of custom base
std::string convertToBase(int base, int number)
{
	int ostatok = number;
	std::string result;
	while (ostatok != 0)
	{
		ostatok = number % base;
		number = number / base;

		result = symbols[ostatok] + result;
	}
	return result;
}

// convert from custom base system to decimal
int convertFromBase(int base, std::string number)
{
	int result = 0;
	for (int i = 0; i < number.length(); i++)
	{
		int num = numberFromSymbol(number[i]);
		int power = (int)number.length() - i - 1;
		power = powi(base, power);
		result += num * power;
	}
	return result;
}

int main(int argc, const char * argv[])
{
	// loading numbers
	std::ifstream inputFile;
	inputFile.open("INPUT.TXT");
	std::vector<int> numbers;
	if (inputFile)
	{
		int a;
		while (inputFile >> a)
		{
			numbers.push_back(a);
			std::cout << "read number " << a << std::endl;
			std::cout << "base 19 number " << convertToBase(19, a) << std::endl;
		}
		inputFile.close();
	}
	else
	{
		std::cout << "Failed to open input file!" << std::endl;
		return 1;
	}

	// minimum and maximum numbers

	int max = numbers[0];
	int min = numbers[0];
	for (int i = 1; i < numbers.size(); i++)
	{
		int x = numbers[i];
		if (x > max)
		{
			max = x;
		}
		if (x < min)
		{
			min = x;
		}
	}
	std::cout << "maximum number is " << max << std::endl;
	std::cout << "minimum number is " << min << std::endl;

	// reversing

	int size = (int)numbers.size();
	for (int i = 0; i < size / 2; i++)
	{
		int j = size - 1 - i;
		int tmp = numbers[i];
		numbers[i] = numbers[j];
		numbers[j] = tmp;
	}

	std::cout << "Reversed numbers: ";

	for (int i = 0; i < size; i++)
	{
		std::cout << numbers[i] << " ";
	}

	std::cout << std::endl;

	// saving

	std::ofstream outputFile;
	outputFile.open("OUTPUT.TXT");
	if (outputFile)
	{
		outputFile << min << " " << max << std::endl;
		for (int i = 0; i < size; i++)
		{
			outputFile << numbers[i] << " ";
		}

		outputFile << std::endl;
		outputFile.close();
	}
	else
	{
		std::cout << "Failed to open output file!" << std::endl;
		return 1;
	}

	std::cout << "hex 0xD002AC is " << convertFromBase(16, "D002AC") << std::endl;

	// multidimensional arrays

	// create
	int **x = new int*[10];
	for (int i = 0; i < 10; i++)
	{
		x[i] = new int[10];
	}

	// fill
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			x[i][j] = i + j;
		}
	}

	// print
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::cout << x[i][j] << " ";
		}
		std::cout << std::endl;
	}

	// destroy
	for (int i = 0; i < 10; i++)
	{
		delete [] x[i];
	}

	delete [] x;


    return 0;
}

