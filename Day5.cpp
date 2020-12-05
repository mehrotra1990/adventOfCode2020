#include <iostream>
#include <fstream>
#include <string>
#include <map>

int getSeatId(std::string *seat) {

	int numRows = 127;
	int minRow = 0;
	int maxRow = numRows;
	int minCol = 0;
	int maxCol = 7;
	for(auto ch : *seat) {
		if(ch == 'F') {
			maxRow = (minRow + maxRow)/2;
		} else if(ch == 'B') {
			minRow = (minRow + maxRow)/2 + 1;
		} else if(ch == 'L') {
			maxCol = (minCol + maxCol)/2;
		} else {
			minCol = (minCol + maxCol)/2 + 1;
		}
	}
	// By this point, minRow should be equal to maxRow & minCol should be equal to maxCol
	int seatId = minRow * 8 + minCol;
	return seatId;
/*
Start by considering the whole range, rows 0 through 127.	minRow = 0; maRow = 127
F means to take the lower half, keeping rows 0 through 63.	minRow = 0; minRow = 127/2 = 63
B means to take the upper half, keeping rows 32 through 63.	minRow = 63/2 + 1 = 32; maxRow = 63
F means to take the lower half, keeping rows 32 through 47.	minRow = 32; maxRow (32 + 63)/2 = 47
B means to take the upper half, keeping rows 40 through 47.	minRow = (32 + 47/2) + 1 = 39 + 1 = 40; maxRow = 47
B keeps rows 44 through 47.					minRow = (40 + 47)/2 + 1 = 43 + 1 = 44; maxRow = 47 
F keeps rows 44 through 45.					minRow = 44; maxRow = (44 + 47)/2 = 45
The final F keeps the lower of the two, row 44.			minRow = 44; maxRow = (44 + 45)/2 = 44

Start by considering the whole range, columns 0 through 7.	minCol = 0; maxCol = 7
R means to take the upper half, keeping columns 4 through 7.	minCol = 7/2 + 1 = 4; maxCol = 7
L means to take the lower half, keeping columns 4 through 5.	minCol = 4; maxCol = (4 + 7)/2 = 5
The final R keeps the upper of the two, column 5.		minCol = (4 + 5)/2 + 1 = 5; maxCol = 5
*/

}
int main() {

	std::ifstream file("inputFileDay5.txt");
	std::string seat;
	int maxSeatId = 0;
	std::map<int, int> allSeatIds;
	while(getline(file, seat)) {
		int seatId = getSeatId(&seat);
		if(seatId > maxSeatId) maxSeatId = seatId;
		allSeatIds[seatId] = 1;
	}
	std::cout<<"Max seatId = "<<maxSeatId<<std::endl;

	// Now lets find the missing seats
	// My seat will not be in first 2 or last 2 rows since +1 and -1 row seats are present
	// We''ll anyways break as soon as we find y seat, so no need to take care of maxRow
	for(int nRow = 2; nRow <128; nRow++) {
		for(int nCol = 0; nCol < 8; nCol++) {
			// Check if this seat is mine
			int seatIdToCheck = nRow * 8 + nCol;
			if(allSeatIds.find(seatIdToCheck) == allSeatIds.end()) {
				//SeatID not present, see if mine
				if(allSeatIds.find(seatIdToCheck + 1) != allSeatIds.end() && allSeatIds.find(seatIdToCheck - 1) != allSeatIds.end()) {
					// Seat found;
					std::cout<<"Found seat: "<<seatIdToCheck<<std::endl;
				}
			}
		}
	}
}
