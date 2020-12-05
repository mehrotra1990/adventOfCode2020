#include <iostream>
#include <vector>
#include<map>
#include <fstream>
#include <string>

// https://adventofcode.com/2020/day/1

int main() {

	std::ifstream file("inputFile.txt");

	std::vector<int> vec;

	std::map<int, int> elementsMap;
	int elementSum = 2020;
	std::string line;

	while (getline(file, line)) {
		int element = std::stoi(line);
		vec.push_back(element);
	}

#ifndef THREESUM
	for(auto element : vec) {
		int diff = 2020 - element;
		if(elementsMap.find(diff) != elementsMap.end()) {
			// Found!
			std::cout<<"Result is: "<<diff<<" & "<<element<<std::endl;
		} else {
			elementsMap[element] = 1;
		}
	}
#else
	// Add the sum of two numbers and their products to the map
	for(int i = 0; i < vec.size(); i++ ){
		for(int j = i; j < vec.size(); j++) {
			elementsMap[vec[i] + vec[j]] = vec[i] * vec[j];
		}
	}
	for(auto element : vec) {
		int diff = 2020 - element;
		if(elementsMap.find(diff) != elementsMap.end()) {
			// Found!
			std::cout<<"Result is: "<<elementsMap[diff] * element<<std::endl;
			break;
		}
	}
#endif

}
