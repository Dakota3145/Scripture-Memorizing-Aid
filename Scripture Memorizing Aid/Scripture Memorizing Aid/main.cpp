#include <iostream>
#include <cctype>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <iomanip>
#define MAX_DIFFICULTY 5
using namespace std;

string StripVerseNumber(string wholeScripture) {
	for (int i = 0; i < wholeScripture.size(); i++) {
		if (isdigit(wholeScripture.at(i))) {
			wholeScripture.erase(i, 1);
			i--;
		}
		else if (isspace(wholeScripture.at(i)) && i == 0) {
			wholeScripture.erase(i, 1);
		}
	}
	string scriptureNoNumbers = wholeScripture;
	return scriptureNoNumbers;
}
bool FindInVec(int index, vector<int> intVec) {
	for (int j = 0; j < intVec.size(); j++) {
		if (intVec.at(j) == index) {
			return true;
		}
	}
	return false;
}
vector<string> StripPunctuation(vector <string> ScriptureList) {
	for (int i = 0; i < ScriptureList.size(); i++) {
		for (int j = 0; j < ScriptureList.at(i).size(); j++) {
			switch (ScriptureList.at(i).at(j)) {
			case ':':
				ScriptureList.at(i).erase(j, 1);
				break;
			case ';':
				ScriptureList.at(i).erase(j, 1);
				break;
			case '.':
				ScriptureList.at(i).erase(j, 1);
				break;
			case '!':
				ScriptureList.at(i).erase(j, 1);
				break;
			case ',':
				ScriptureList.at(i).erase(j, 1);
				break;
			case '?':
				ScriptureList.at(i).erase(j, 1);
				break;
			case '-':
				ScriptureList.at(i).erase(j, 1);
				break;
			case '[':
				ScriptureList.at(i).erase(j, 1);
				break;
			case ']':
				ScriptureList.at(i).erase(j, 1);
				break;
			case '(':
				ScriptureList.at(i).erase(j, 1);
				break;
			case ')':
				ScriptureList.at(i).erase(j, 1);
				break;
			case '“':
				ScriptureList.at(i).erase(j, 1);
				break;
			case '”':
				ScriptureList.at(i).erase(j, 1);
				break;
			case '\'':
				ScriptureList.at(i).erase(j, 1);
				break;
			default:
				break;
			}
		}
	}
	vector<string> plainScripture = ScriptureList;
	return plainScripture;
}
void TryNew(string& wholeScripture, vector<string>& ScriptureList, vector<int> blockedIndexList) {
	ScriptureList.clear();
	cout << endl << "Copy and Paste the scripture you want to memorize here: " << endl;
	getline(cin, wholeScripture);
	if (wholeScripture == "") {
		cout << "No scripture captured." << endl;
	}
	string scriptureNoNumbers = StripVerseNumber(wholeScripture);
	scriptureNoNumbers.append(" ");
	for (int i = 0; i < scriptureNoNumbers.size(); i++) {
		if (isspace(scriptureNoNumbers.at(i))) {
			ScriptureList.push_back(scriptureNoNumbers.substr(0, i));
			scriptureNoNumbers.erase(0, i + 1);
			i = 0;
		}
	}
	cout << endl << "Enter your difficulty from 1-5, where 1 is the easiest(20% of the words are hidden) and 5 is the hardest(every word is " << endl;
	cout << "hidden): ";
	int levelOfDifficulty = 0;
	cin >> levelOfDifficulty;
	int numBlockedOutWords = (ScriptureList.size() * levelOfDifficulty) / MAX_DIFFICULTY;
	for (int i = 0; i < numBlockedOutWords; i++) {
		int randIndex = rand() % ScriptureList.size();
		bool isFound = FindInVec(randIndex, blockedIndexList);
		if (isFound == false) {
			blockedIndexList.push_back(randIndex);
		}
		else {
			i--;
		}
	}
	sort(blockedIndexList.begin(), blockedIndexList.end());
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << setw(50) << fixed << right << "HERE'S THE SCRIPTURE" << endl << endl << endl << endl;
	int blockedWordIndex = 1;
	for (int i = 0; i < ScriptureList.size(); i++) {
		bool isFound = FindInVec(i, blockedIndexList);
		if (isFound == true) {
			cout << blockedWordIndex;
			for (int k = 0; k < ScriptureList.at(i).size(); k++) {
				switch (ScriptureList.at(i).at(k)) {
				case ':':
					cout << ":";
					break;
				case ';':
					cout << ";";
					break;
				case '.':
					cout << ".";
					break;
				case '!':
					cout << "!";
					break;
				case ',':
					cout << ",";
					break;
				case '?':
					cout << "?";
					break;
				case '-':
					cout << "-";
					break;
				case '[':
					cout << "[";
					break;
				case ']':
					cout << "]";
					break;
				case '(':
					cout << "(";
					break;
				case ')':
					cout << ")";
					break;
				case '“':
					cout << "“";
					break;
				case '”':
					cout << "”";
					break;
				case '\'':
					cout << "\'";
					break;
				default:
					cout << "_";
				}
			}
			blockedWordIndex++;
		}
		else {
			cout << ScriptureList.at(i);
		}
		cout << " ";
	}
	cout << endl << endl;
	cout << "Guess each of the missing words. You don't need to add any punctuation; however you do need to have the right " << endl;
	cout << "upper/lower case. Hit \"Enter\" after each word to move on." << endl << endl;
	vector<string> guessWords;
	string tempGuessWord;
	for (int i = 0; i < blockedIndexList.size(); i++) {
		cout << i + 1 << ": ";
		cin >> tempGuessWord;
		cin.ignore();
		guessWords.push_back(tempGuessWord);
	}
	vector<string> plainScripture = StripPunctuation(ScriptureList);
	cout << setw(40) << fixed << right << endl << "RESULTS" << endl << endl;
	double numRightWords = 0;
	for (int i = 0; i < guessWords.size(); i++) {
		cout << i + 1 <<  ": " << guessWords.at(i) << " is ";
		if (guessWords.at(i) == plainScripture.at(blockedIndexList.at(i))) {
			cout << "CORRECT!" << endl;
			numRightWords++;
		}
		else {
			cout << "WRONG. The right answer is " << plainScripture.at(blockedIndexList.at(i)) << endl;
		}
	}
	cout << endl;
	double rightPercentage = 100.00 * (numRightWords / blockedIndexList.size());
	cout << fixed << setprecision(2) << "You got " << rightPercentage << "%" << " of the answers correct. To retry this same scripture, enter \"retry\"." << endl << endl;
}
void Retry(string wholeScripture, vector<string> ScriptureList, vector<int> blockedIndexList) {
	if (wholeScripture == "") {
		cout << "There's no scripture already stored." << endl;
	}
	else {
		cout << endl << "Enter your difficulty from 1-5, where 1 is the easiest(20% of the words are hidden) and 5 is the hardest(every word is " << endl;
		cout << "hidden): ";
		int levelOfDifficulty = 0;
		cin >> levelOfDifficulty;
		int numBlockedOutWords = (ScriptureList.size() * levelOfDifficulty) / MAX_DIFFICULTY;
		for (int i = 0; i < numBlockedOutWords; i++) {
			int randIndex = rand() % ScriptureList.size();
			bool isFound = FindInVec(randIndex, blockedIndexList);
			if (isFound == false) {
				blockedIndexList.push_back(randIndex);
			}
			else {
				i--;
			}
		}
		sort(blockedIndexList.begin(), blockedIndexList.end());
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		cout << setw(50) << fixed << right << "HERE'S THE SCRIPTURE" << endl << endl << endl << endl;
		int blockedWordIndex = 1;
		for (int i = 0; i < ScriptureList.size(); i++) {
			bool isFound = FindInVec(i, blockedIndexList);
			if (isFound == true) {
				cout << blockedWordIndex;
				for (int k = 0; k < ScriptureList.at(i).size(); k++) {
					switch (ScriptureList.at(i).at(k)) {
					case ':':
						cout << ":";
						break;
					case ';':
						cout << ";";
						break;
					case '.':
						cout << ".";
						break;
					case '!':
						cout << "!";
						break;
					case ',':
						cout << ",";
						break;
					case '?':
						cout << "?";
						break;
					case '-':
						cout << "-";
						break;
					case '[':
						cout << "[";
						break;
					case ']':
						cout << "]";
						break;
					case '(':
						cout << "(";
						break;
					case ')':
						cout << ")";
						break;
					case '“':
						cout << "“";
						break;
					case '”':
						cout << "”";
						break;
					case '\'':
						cout << "\'";
						break;
					default:
						cout << "_";
					}
				}
				blockedWordIndex++;
			}
			else {
				cout << ScriptureList.at(i);
			}
			cout << " ";
		}
		cout << endl << endl;
		cout << "Guess each of the missing words. You don't need to add any punctuation; however you do need to have the right " << endl;
		cout << "upper/lower case. Hit \"Enter\" after each word to move on." << endl << endl;
		vector<string> guessWords;
		string tempGuessWord;
		for (int i = 0; i < blockedIndexList.size(); i++) {
			cout << i + 1 << ": ";
			cin >> tempGuessWord;
			cin.ignore();
			guessWords.push_back(tempGuessWord);
		}
		vector<string> plainScripture = StripPunctuation(ScriptureList);
		cout << setw(35) << fixed << right << endl << "RESULTS" << endl << endl;
		double numRightWords = 0;
		for (int i = 0; i < guessWords.size(); i++) {
			cout << i + 1 << ": " << guessWords.at(i) << " is ";
			if (guessWords.at(i) == plainScripture.at(blockedIndexList.at(i))) {
				cout << "CORRECT!" << endl;
				numRightWords++;
			}
			else {
				cout << "WRONG. The right answer is " << plainScripture.at(blockedIndexList.at(i)) << endl;
			}
		}
		cout << endl;
		double rightPercentage = 100.00 * (numRightWords / blockedIndexList.size());
		cout << fixed << setprecision(2) << "You got " << rightPercentage << "%" << " of the answers correct. To retry this same scripture, enter \"retry\"." << endl << endl;
	}
}
int main() {
	srand(time(NULL));
	string menuSelection;
	string wholeScripture;
	vector<string> ScriptureList;
	vector<int> blockedIndexList;
	do {
		cout << "\tScripture Mastery Menu" << endl;
		cout << "try new:   try a new scripture" << endl;
		cout << "retry:\t   retry a scripture you've already typed in" << endl;
		cout << "quit:\t   Exit the program." << endl << endl;
		cout << "Please type an option: ";
		getline(cin, menuSelection);
		if (menuSelection == "try new") {
			TryNew(wholeScripture, ScriptureList, blockedIndexList);
		}
		else if (menuSelection == "retry") {
			Retry(wholeScripture, ScriptureList, blockedIndexList);
		}
		else if (menuSelection != "quit") {
			cout << "Invalid Response. Please choose one of the three options." << endl;
		}
		cout << endl;
	} while (menuSelection != "quit");
}