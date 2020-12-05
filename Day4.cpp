#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

std::vector<std::string> validFields = {
	"byr",
	"iyr",
	"eyr",
	"hgt",
	"hcl",
	"ecl",
	"pid",
};

void populatePassportEntries(std::vector<std::map<std::string, std::string>> *entries) {
	std::ifstream file("inputFileDay4.txt");
	std::string line;
	std::vector<std::string> forest;

	int numTokens = 0;

	while(getline(file, line)) {
		std::map<std::string, std::string> myFields;
		do {
			// This loop is for each passport entry, so break as soon as a new line is encountered
#ifdef PRINT
			std::cout<<"New line: "<<line<<" of size"<<line.size()<<"\n";
#endif
			int length = line.size();
			if(length == 0){
				break;
			}


			std::string lastToken = "";
			std::string  word= "";

			int idx = 0;


			// Belo loop is for tokenizing each line
			while(line[idx]) {
				word += line[idx++];

				if(line[idx] == ':') {
					// Found a complete token
					lastToken = word;
					myFields[lastToken] = "";
#ifdef PRINT
					std::cout<<"Token found: "<<lastToken<<"\n";
#endif
					numTokens++;

					// Only to debug
					//if(numTokens > 20) return;
					
					word = "";
					idx++;
				}
				else if(line[idx] == ' ' || idx>= length) {
					// This is not a token, but a value of the previous token
					myFields[lastToken] = word;
					word = "";
					idx++;
					lastToken = "";
				}
			}

		}while(getline(file, line));

#ifdef PRINT
		std::cout<<"============Moving to next entry==========\n";
#endif

		entries->push_back(myFields);
	}

#ifdef PRINT
	std::cout<<"Entries populated\n";
#endif
}

bool checkIfValid(std::map<std::string, std::string>* entry) {

	bool invalid = false;

#ifdef PRINTENTRIES
		std::cout<<"Current entry: \n";
		for(auto key : *entry) {
			std::cout<<"\t"<<key.first<<" "<<key.second<<"\n";
		}
		std::cout<<"\n";
#endif

	for(auto field : validFields) {
		if(entry->find(field) == entry->end()) {
			// Invalid Password
#ifdef PRINTENTRIES
			std::cout<<"Invalid entry found: "<<field<<" is missing \n";
#endif
			invalid = true;
			break;
		}
		else {
			// Not taking care of edge cases for now
			if(field == "byr") {
				int byr = std::stoi((*entry)[field]);
				if(byr < 1920 || byr > 2002) {
#ifdef PRINTENTRIES
					std::cout<<field<<" "<<(*entry)[field]<<" is invalid"<<"\n";
#endif
					invalid = true;
					break;
				}
			} else if (field == "iyr") {
				int iyr = std::stoi((*entry)[field]);
				if(iyr < 2010 || iyr > 2020) {
#ifdef PRINTENTRIES
					std::cout<<field<<" "<<(*entry)[field]<<" is invalid"<<"\n";
#endif
					invalid = true;
					break;
				}
			} else if (field == "eyr") {
				int eyr = std::stoi((*entry)[field]);
				if(eyr < 2020 || eyr > 2030) {
#ifdef PRINTENTRIES
					std::cout<<field<<" "<<(*entry)[field]<<" is invalid"<<"\n";
#endif
					invalid = true;
					break;
				}
			} else if (field == "hgt") {
				std::string value = (*entry)[field];
				int len = value.size();
				int height = std::stoi(value.substr(0, len-2));
				if(value[len - 2] == 'c') {
					if(height < 150 || height > 193) {
#ifdef PRINTENTRIES
					std::cout<<field<<" "<<(*entry)[field]<<" is invalid"<<"\n";
#endif
						invalid = true;
						break;
					}
				} else {
					if(height <59 || height > 76) {
#ifdef PRINTENTRIES
					std::cout<<field<<" "<<(*entry)[field]<<" is invalid"<<"\n";
#endif
						invalid = true;
						break;
					}
				
				}

			} else if (field == "hcl") {
				std::string value = (*entry)[field];
				int len = 0;
#ifdef PRINTENTRIES
				std::cout<<"value"<<value<<std::endl;
#endif
				for(auto ch : value) {
					if(len == 0) {
						if(ch != '#') {
							invalid = true;
							break;
						}
					}
					else if( !((ch >= 48 || ch <= 57 ) || (ch >= 97 || ch <= 122)) ) {
#ifdef PRINTENTRIES
						std::cout<<"ch "<<ch<<std::endl;
#endif
						invalid = true;
						break;
					}

					len++;
				}
				if(len != 7 || invalid) {
#ifdef PRINTENTRIES
					std::cout<<field<<" "<<(*entry)[field]<<" is invalid"<<"\n";
#endif
					invalid = true;
					break;
				}
			
			} else if (field == "ecl") {
				std::string value = (*entry)[field];
				if( !(value == "amb" ||
						value == "blu" ||
						value == "brn" ||
						value == "gry" ||
						value == "grn" ||
					        value == "hzl" ||
						value == "oth")) {
#ifdef PRINTENTRIES
					std::cout<<field<<" "<<(*entry)[field]<<" is invalid"<<"\n";
#endif
					invalid = true;
					break;
				}

			} else if (field == "pid") {
				std::string value = (*entry)[field];
				int len = 0;
				for(auto ch : value) {
					if(ch < 48 || ch > 57) {
						invalid = true;
						break;
					}
					len++;
				}
				if(len!=9 || invalid) {
#ifdef PRINTENTRIES
					std::cout<<field<<" "<<(*entry)[field]<<" is invalid"<<"\n";
#endif
					invalid = true;
					break;
				}

			}
		}
	}

	if(!invalid)
		return true;
	
	return false;
}

int main() {


	std::vector<std::map<std::string, std::string>> passportEntries;

	populatePassportEntries(&passportEntries);

	int valid = 0;

	for(auto entry : passportEntries) {
		if(checkIfValid(&entry)) valid++;
	}
	std::cout<<"Number of valid passports: "<<valid<<std::endl;
}
