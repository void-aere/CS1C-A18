#pragma once

#include <string>

// UI tools / formatting / string tools
void clearScreen();
void waitForInput();
std::string chop(const std::string& str, int width);
std::string center(const std::string& str, int width);
std::string pad(int width); //literally just <width> spaces
std::string lowercase(const std::string& str); //return a lowercased version of str
int searchraw(const std::string& source, const std::string& query);

// Getting user input
std::string inputString();
std::string inputString(const std::string& prompt);
int inputInt();
int inputInt(const std::string& prompt);
long long inputLL();
long long inputLL(const std::string& prompt);
float inputFloat();
float inputFloat(const std::string& prompt);
double inputDouble();
double inputDouble(const std::string& prompt);
int getMenuOption(int high); //gets a menu selection option between 1 and $high
int getMenuOptionAuto(int high); //works better but will return -1 on error
void ignoreLine(); // refined usage of cin.ignore()
bool confirm(const std::string& prompt); // Get user confirmation (y/n)

// Working with dates
std::string currentDate();
bool valiDate(const std::string& date); //validate a date (mm-dd-yyyy)

// Password tools
size_t hashword(const std::string& word); // compute a string's hash