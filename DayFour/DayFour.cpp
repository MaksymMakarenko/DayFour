#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>



std::vector<__int8> splitStringComma(std::string str) {

	int i = 0;
	std::string val;
	std::vector<__int8> vectorVal;


	while (i < str.length())
	{

		if (str[i] == ',') {

			vectorVal.push_back(stoi(val));
			val = "";
		}
		else {
			val.push_back(str[i]);
		}
		i++;
	}
	vectorVal.push_back(stoi(val));

	return vectorVal;
}

std::vector<std::vector<__int8>> splitStringBacspace(
	std::vector<std::vector<__int8>> vectorVal,
	std::vector<std::vector<bool>>& vectorBool, int i, std::string str) {

	int iter = 0;
	std::string val;

	while (iter < str.length()) {

		if (str[iter] == ' ' && val.length()) {
			vectorVal[i].push_back(stoi(val));
			vectorBool[i].push_back(0);
			val = "";
		}

		else {

			val.push_back(str[iter]);

		}
		iter++;
	}

	vectorVal[i].push_back(stoi(val));
	vectorBool[i].push_back(0);

	return vectorVal;
}

void closeNumber(std::vector<std::vector<__int8>> vectorVal,
	std::vector<std::vector<bool>>& vectorBool, int val) {

	int i = 0;

	while (i < vectorVal.size()) {						//traversing boards
		int j = 0;

		while (j < vectorVal[i].size()) {

			if (vectorVal[i][j] == val) {

				vectorBool[i][j] = 1;
				break;
			}
			j++;
		}
		i++;
	}
}

int winHorizontal(std::vector<std::vector<bool>> vectorBool) {

	int i = 0;

	while (i < vectorBool.size()) {							//traversing boards

		for (int j = 0; j < vectorBool[i].size() / 5; j++) {

			int val = 0;

			for (int iter = 0; iter < 5; iter++) {

				val += vectorBool[i][j + iter];
			}
			if (val == 5) {

				return i + 1;
			}
		}
		i++;
	}
	return 0;
}

bool winHorizontal(std::vector<bool> vectorBool, int row) {
	int val = 0;
	for (int i = 0; i < 5; i++) {
		val += vectorBool[row*5 + i];
	}
	if (val == 5) {

		return 1;
	}
	return 0;
}

int winVertical(std::vector<std::vector<bool>> vectorBool)
{
	int i = 0;

	while (i < vectorBool.size()) {							//traversing boards

		for (int j = 0; j < vectorBool[i].size() / 5; j++) {//traversing the board by column

			int val = 0;

			for (int iter = 0; iter < 5; iter++) {

				val += vectorBool[i][j + iter * 5];
			}

			if (val == 5)									// if all numbers closed values = 5
			{
				return i + 1;
			}
		}
		i++;
	}
	return 0;
}

bool winVertical(std::vector<bool> vectorBool,
	int column) {
	int val = 0;

	for (int j = 0; j < 5; j++) {

		val += vectorBool[column + j * 5];
	}
	if (val == 5) {										// if all numbers closed values = 5

		return 1;
	}

	return 0;
}

int sumFreeValues(std::vector<__int8> vectorVal,
	std::vector<bool> vectorBool) {

	int sum = 0;
	int i = 0;

	while (i < vectorVal.size()) {

		if (!vectorBool[i]) {
			sum += vectorVal[i];
		}

		i++;
	}

	return sum;
}

bool lastWin(std::vector<bool> vectorBool) {

	int sum = std::accumulate(vectorBool.begin(), vectorBool.end(), 0);
	if (sum == vectorBool.size()) {
		return 1;
	}
	return 0;
}

bool closeNumber(std::vector<std::vector<__int8>> vectorVal,
	std::vector<std::vector<bool>>& vectorBool,
	std::vector<bool>& winBoardBool, int val) {				//closing the numbers on the boards
															//win check
	int i = 0;
	bool win = 0;
	
	while (i < vectorVal.size()) {							//traversing boards

		int j = 0;

		while (j < vectorVal[i].size()) {

			if (vectorVal[i][j] == val) {
				vectorBool[i][j] = 1;
				if ((winHorizontal(vectorBool[i], j / 5) || 
					winVertical(vectorBool[i], j % 5)) && !winBoardBool[i] ) {
					winBoardBool[i] = 1;

					if (lastWin(winBoardBool))
					{
						std::cout << val * sumFreeValues(vectorVal[i], vectorBool[i]);
						win = 1;
					}
				}


				break;
			}
			j++;
		}
		if (win) { return 1; }
		i++;
	}
	return 0;
}

int main()
{
	std::string path("inputFour.txt");

	std::ifstream in(path); 
	std::string line;
	std::vector<__int8> vectorVal;
	std::vector<std::vector<__int8>> board;
	std::vector<std::vector<bool>> boardBool;
	std::vector<bool> winBoardBool;


	if (in.is_open())
	{
		getline(in, line);
		vectorVal = splitStringComma(line);
		getline(in, line);
		std::string str;
		int i = 0;
		while (!in.eof())
		{
			getline(in, line);
			if (line != "") {
				board.resize(i + 1);
				boardBool.resize(i + 1);
				board = splitStringBacspace(board, boardBool, i, line);
			}
			else i++;
		}
	}
	else std::cout << "File not found";
	in.close();   

	winBoardBool.resize(board.size(), 0);

	/*for (int i = 0; i < vectorVal.size(); i++)
	{
		closeNumber(board, boardBool, vectorVal[i]);
		int winBoardHorizontal = winHorizontal(boardBool);
		int winBoardVertical = winVertical(boardBool);
		if (winBoardHorizontal)
		{
			std::cout << vectorVal[i]*sumFreeValues(board[winBoardHorizontal-1],
			boardBool[winBoardHorizontal-1]);
			break;
		}
		else if (winBoardVertical)
		{
			std::cout << vectorVal[i]*sumFreeValues(board[winBoardVertical-1],
			boardBool[winBoardVertical-1]);
			break;
		}

	}*/

	for (int i = 0; i < vectorVal.size(); i++)
	{
		if (closeNumber(board, boardBool, winBoardBool, vectorVal[i])) {
			break;
		}
	}

	system("pause");
	return 0;
}