#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
int main() {

	std::ifstream file("inputFileDay3.txt");
	std::string line;
	std::vector<std::string> forest;

	int height = 0, width;

	while(getline(file, line)) {
		forest.push_back(line);
		height++;

	}
	width = forest[0].size();

#ifdef PRINT
	for(auto line : forest) {
		std::cout<<line<<"\n";
	}
	std::cout<<"Forest printed with width: "<<width<<" amd height: "<<height<<std::endl;
#endif
	std::vector<std::tuple<int, int>> slopes = {
		std::make_tuple(1,1),
		std::make_tuple(3,1),
		std::make_tuple(5,1),
		std::make_tuple(7,1),
		std::make_tuple(1,2)
	
	};

	int productOfAllTrees = 1;

	for(auto slope : slopes) {
		int toboggan = std::get<1>(slope);
		int currPosition = 0;
		int numTrees = 0;

		while(toboggan<height) {
			currPosition += std::get<0>(slope);
#ifdef PRINT
			std::cout<<"Position: "<<toboggan<<","<<currPosition<<std::endl;
#endif
			if(currPosition >= width) {
				currPosition = currPosition % width;
			}
			if(forest[toboggan].at(currPosition) == '#') numTrees++;

#ifdef PRINT
			std::cout<<"Position at "<<toboggan<<","<<currPosition<<" contains "<<forest[toboggan].at(currPosition)<<"\n";
#endif
			toboggan+=std::get<1>(slope);
		}
		std::cout<<"The number of trees: "<<numTrees<<std::endl;
		productOfAllTrees *= numTrees;
	}

	std::cout<<"Product of all: "<<productOfAllTrees<<std::endl;
}
