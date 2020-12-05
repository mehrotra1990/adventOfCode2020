#include <iostream>
#include <vector>
#include<map>
#include <fstream>
#include <string>

// https://adventofcode.com/2020/day/1

bool isPasswordValidPart1(const std::string* line, std::string* password) {
	// Extract the min
#ifdef PRINT
	std::cout<<*line<<"\n";
#endif

	int min = 0;
	int idx = 0;
	char c;
	char n = line->at(idx++);
	while(n != '-') {
		min *= 10;
		min += n - 48;
		n = line->at(idx++);
	}

#ifdef PRINT
	std::cout<<min<<" ";
#endif

	int max = 0;
	// Extract the max
	n = line->at(idx++);
	while(n != ' ') {
		max *= 10;
		max += n - 48;
		n = line->at(idx++);
	}

#ifdef PRINT
	std::cout<<max<<" ";
#endif

	c = line->at(idx++);


#ifdef PRINT
	std::cout<<c<<" ";
#endif
	// For :
	idx++;
	// For space
	idx++;
	size_t length = line->size();
	int count = 0;

	while(idx<length) {
		n = line->at(idx++);
		if(n == c) count++;
		*password += n;
	}


#ifdef PRINT
	std::cout<<*password<<"\n";
	std::cout<<"Count of "<<c<<": "<<count<<"\n";
#endif

	if(count >= min && count <= max) return true;

	std::cout<<"Returning false\n";
	std::cout<<*line<<"\n";
	std::cout<<"Count of "<<c<<": "<<count<<"\n";
	return false;

}

bool isPasswordValidPart2(const std::string* line, std::string* password) {
	// Extract the min
#ifdef PRINT
	std::cout<<*line<<"\n";
#endif

	int min = 0;
	int idx = 0;
	char c;
	char n = line->at(idx++);
	while(n != '-') {
		min *= 10;
		min += n - 48;
		n = line->at(idx++);
	}

#ifdef PRINT
	std::cout<<min<<" ";
#endif

	int max = 0;
	// Extract the max
	n = line->at(idx++);
	while(n != ' ') {
		max *= 10;
		max += n - 48;
		n = line->at(idx++);
	}

#ifdef PRINT
	std::cout<<max<<" ";
#endif

	c = line->at(idx++);


#ifdef PRINT
	std::cout<<c<<" ";
#endif
	// For :
	idx++;
	// For space
	idx++;
	size_t length = line->size();
	int count = 0;

	while(idx<length) {
		n = line->at(idx++);
		if(n == c) count++;
		*password += n;
	}

	length = password->size();

	if(min-1 < length && max-1 <=length) {
		if((password->at(min-1) == c || password->at(max-1) == c) && password->at(min-1) != password->at(max-1))
		{
			return true;
		}
	}

	return false;

}

int main() {

	std::ifstream file("inputFileDay2.txt");

	// Map of policy and password
	std::map<std::string, std::string> passwordsMap;

	int validPasswords = 0;

	std::string line;

	while (getline(file, line)) {
		std::string password;
		if(isPasswordValidPart2(&line, &password))
			validPasswords++;
	}
	std::cout<<validPasswords<<std::endl;
}
