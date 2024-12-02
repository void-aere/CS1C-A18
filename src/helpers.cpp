#include "helpers.hpp"
#include <string>
#include <iostream>
#include <limits>
#include <chrono>
#include <unordered_map>

using std::string;
using std::cout, std::cin, std::endl;

/**
 * Clear the screen.
 * 
 * This function can be used anywhere to overwrite whatever's been printed.
*/
void clearScreen() {
    if (!system("cls") == 0) std::cout << "\033[2J\033[1;1H";
}

//Use this if you want to use getline() after using cin >>
/**
 * Politely ignore whatever CIN has to say.
 * 
 * A cleaner way of calling cin.ignore(). Used internally by data-getters.
*/
void ignoreLine() {
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * Get user confirmation for something.
 * 
 * This function prints a yes/no confirmation question and waits for the user's response.
 * 
 * @param prompt The string propmt to present the user, e.g. "Prompt? (y/n): "
*/
bool confirm(const string& prompt) {
	cout << prompt;
	string confirm;
	getline(cin, confirm);
	if (lowercase(confirm).front() == 'y') return true;
	return false;
}

/**
 * Wait for the user to press RETURN.
 * 
 * If there are any issues, blame inputInt() and inputFloat().
*/
void waitForInput() {
	cout << "Press RETURN to continue";
	cin.get();
}

/**
 * Makes a string the right length, no matter what.
 * 
 * This function sets the length of a string to whatever you want.
 * If it's too long, cull the excess.
 * If it's too short, pad it with spaces.
 * 
 * @param str	The string to be modified
 * @param width	The correct length
 * @returns		The modified string. It \b WILL be the correct length.
*/
string chop(const string& str, int width) {
	string str2 = str.substr(0, width);
	int len = str2.length();
	int buff = width - len;
	return str2 + string(buff, ' ');
}

string center(const string& str, int width) {
    string str2 = str.substr(0, width);
    int buff = (width - str2.length()) / 2;
    return string(buff, ' ') + str2 + string(buff, ' ');
}

/**
 * Create a blank string of specified length.
 * 
 * Glorified string constructor that returns the specified amount of spaces.
 * 
 * @param width	The number of spaces to print.
 * @returns		A new string made of \p width spaces.
*/
string pad(int width) {
	return string(width, ' ');
}

/**
 * Make a string all lowercase.
 * 
 * This function returns the string passed to it, except all capital letters are lowercase.
 * 
 * @param str	The string to convert.
 * @returns		The same string, but all lowercase.
*/
string lowercase(const string& str) {
	const char* cstr = str.c_str();
	string out;
	int i = 0;
	while (cstr[i]) {
		out += tolower(cstr[i]);
		i++;
	}
	return out;
}

/**
 * Search for a string within another string.
 * 
 * Returns the earliest instance of \p query within \p source.
 * This function is case-sensitive, so use lowercase() on the parameters.
 * 
 * @param query		The string to look for.
 * @param source	The string to search.
 * @returns			The index of the first instance of \p query, or -1 if not found.
*/
int searchraw(const string& source, const string& query) {
	int slen = source.length();
	int qlen = query.length();

	string s = lowercase(source);
	string q = lowercase(query);

	if (qlen > slen) return -1;
	for (int i = 0; i <= slen - qlen; i++) if (s.substr(i, qlen).compare(q) == 0) return i;
	return -1;
}

/**
 * Get a string input
 * 
 * This non-printing function returns the next line of input in the input buffer.
 * 
 * @return The next string.
*/
string inputString() {
	string out;
	getline(cin, out);
	return out;
}

/**
 * Get a string input
 * 
 * This function prints a user prompt, then returns the next string in the input buffer.
 * 
 * @param prompt The prompt to present the user.
 * @return The next string.
*/
string inputString(const string &prompt) {
    cout << prompt;
	string out;
	getline(cin, out);
	return out;
}

/**
 * Get an integral input.
 * 
 * This non-printing function returns the next integer passed to the input buffer.
 * ignoreLine() is called automatically, so CIN will always be clean after use.
 * 
 * @return The next int, or -1 on fail.
*/
int inputInt() {
	int input;
	cin >> input;
	ignoreLine();

	if (!cin.good()) {
		cin.clear();
		ignoreLine();
		return -1;
	} else return input;
}

/**
 * Get an integral input.
 * 
 * This function prints a user prompt, then returns the next integer passed to the input buffer.
 * ignoreLine() is called automatically, so CIN will always be clean after use.
 * 
 * @param prompt The prompt to present the user.
 * @return The next int, or -1 on fail.
*/
int inputInt(const string& prompt) {
	cout << prompt;
	return inputInt();
}

long long inputLL() {
    long long input;
    std::cin >> input;
    ignoreLine();

    if (!cin.good()) {
        cin.clear();
        ignoreLine();
        return -1;
    } else return input;
}

long long inputLL(const std::string& prompt) {
    std::cout << prompt;
    return inputLL();
}

/**
 * Get an floating-point input.
 * 
 * This non-printing function returns the next float passed to the input buffer.
 * ignoreLine() is called automatically, so CIN will always be clean after use.
 * 
 * @return The next float, or -1 on fail.
*/
float inputFloat() {
	float input;
	cin >> input;
	ignoreLine();

	if (!cin.good()) {
		cin.clear();
		ignoreLine();
		return -1;
	} else return input;
}

/**
 * Get an floating-point input.
 * 
 * This function prints a user prompt, then returns the next float passed to the input buffer.
 * ignoreLine() is called automatically, so CIN will always be clean after use.
 * 
 * @param prompt The prompt to present the user.
 * @return The next float, or -1 on fail.
*/
float inputFloat(const string& prompt) {
	cout << prompt;
	return inputFloat();
}

/**
 * Get a double-precision floating-point input (double).
 * 
 * This non-printing function returns the next double passed to the input buffer.
 * ignoreLine() is called automatically, so CIN will always be clean after use.
 * 
 * @return The next double, or -1 on fail.
*/
double inputDouble() {
	double input;
	cin >> input;
	ignoreLine();

	if (!cin.good()) {
		cin.clear();
		ignoreLine();
		return -1;
	} else return input;
}

/**
 * Get a double-precision floating-point input (double).
 * 
 * This function prints a user prompt, then returns the next double passed to the input buffer.
 * ignoreLine() is called automatically, so CIN will always be clean after use.
 * 
 * @param prompt The prompt to present the user.
 * @return The next double, or -1 on fail.
*/
double inputDouble(const string& prompt) {
	cout << prompt;
	return inputDouble();
}

/**
 * Get a constrained integral input for use with menus.
 * 
 * This function gets the next int in the input buffer, and checks that it falls between 0 and \p high.
 * You probably want getMenuOptionAuto().
 * 
 * @param high	The highest allowable menu option, assuming the lowest is 0.
 * @returns 	The user-provided menu option, or -1 if too low, too high, or illegal.
*/
int getMenuOption(int high) {
	int option = inputInt();

	if (option < 1 || option > high) return -1;
	else return option;
}

/**
 * Get a constrained integral input for use with menus, *automatically*.
 * 
 * This function gets the next int in the input buffer, and checks that it falls between 0 and \p high.
 * It extends getMenuOption() in that it deals with the user automtically, prompting them for you.
 * 
 * @param high	The highest allowable menu option, assuming the lowest is 0.
 * @returns 	The user-provided menu option, or -1 if too low, too high, or illegal.
*/
int getMenuOptionAuto(int high) {
	cout << pad(0) << "Enter your choice: ";
	int option = inputInt();

	if (option < 1 || option > high) {
		cout << pad(0) << "Invalid input." << endl;
		cout << pad(0);
		waitForInput();
		return -1;
	} else return option;
}

/**
 * Get the current date, in the serendipity format.
 * 
 * Using magic, ask C++ for the current date, then pretty-print it.
 * 
 * @returns The date, in the format "mm-dd-yyy" as desired by serendipity.
*/
string currentDate() {
	auto const now = std::chrono::current_zone()
		->to_local(std::chrono::system_clock::now());
	return format("{:%m-%d-%Y}", now);	// mm-dd-yyyy
}

/**
 * Validate a date string (haha).
 * 
 * This function verifies that the string passed to it is in the format "mm-dd-yyyy".
 * 
 * @param date	The date (string) to be verified.
 * @returns		\p true if the date looks good, \p false otherwise.
*/
bool valiDate(const string& date) {
	const char* cdate = date.c_str();
	
	for (int i = 0; (size_t)i < date.length(); i++) {
		if (i == 2 || i == 5) { if (cdate[i] != '-' && cdate[i] != '/') return false; }
		else if (!isdigit(cdate[i])) return false;
	}
	return true;
}

size_t hashword(const string& word) {
    // TBH I don't really know what's happening here
    std::hash<string> hash;
    return hash(word);
}
