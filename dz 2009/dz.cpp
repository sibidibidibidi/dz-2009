#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

void replaceinfile(string filename, string oldword, string newword) {
	ifstream infile(filename);
	int pos;
	string str, filecontent="";
	while (!infile.eof()) {
		getline(infile, str);
		pos = str.find(oldword);
		if (pos != string::npos) {
			str.insert(pos, newword);
			filecontent += str;
		}
	}
	ofstream outfile(filename);
	if (!outfile) {
		cerr << "Error opening file for writing." << endl;
		return;
	}
	outfile << filecontent;
}
void upperletter(string filename) {
	ifstream infile(filename);
	string str, filecontent="";
	while (getline(infile, str)) {
		for (int i = 0; i < str.size();i++) {
			if ((int)str[i] == 33 || (int)str[i] == 46 || (int)str[i] == 63) {
				int k = 0;
				for (int j = 1;j < str.size() - i;j++) {
					k += j;
					if ((int)str[i + k] >= 97 && (int)str[i + k] <= 122) {
						str[i+k]=(char)((int)str[i + k] - 32);
						break;
					}
					else if ((int)str[i + k] >= 65 && (int)str[i + k] <= 90) {
						break;
					}
				}
			}
		}
		filecontent += str;
	}
	ofstream outfile(filename);
	if (!outfile) {
		cerr << "Error opening file for writing." << endl;
		return;
	}
	outfile << filecontent;
	outfile.close();
}
void eachletter(string filename, vector<char> letters, vector<int> quantity) {
	ifstream infile(filename);
	string str;
	while (getline(infile, str)) {
		for (int i = 0;i < str.size(); i++) {
			if (((int)str[i] >= 65 && (int)str[i] <= 90) || ((int)str[i] >= 97 && (int)str[i] <= 122)) {
				bool notinvector = true;
				for (int j = 0;j < letters.size();j++){
					if ((letters[j] == str[i]) || ((int)letters[j] < 91 && (int)letters[j] == (int)str[i] - 32) || ((int)letters[j] > 96 && (int)letters[j] == (int)str[i] + 32)) {
						notinvector = false;
					}
					else {
						notinvector = true;
						break;
					}
				}if (notinvector) {
					letters.push_back(str[i]);
				}
			}
		}
		for (int i = 0;i < letters.size();i++) {
			if ((int)letters[i] >= 65 && (int)letters[i] <= 90) {
				letters[i] = (char)((int)letters[i] + 32);
			}
		}
		for (int i = 0;i < letters.size();i++) {
			int k = 0;
			for (int j = 0;j < str.size();j++) {
				if (((int)str[i] == (int)letters[j]) || ((int)str[i] == (int)letters[j] - 32)) {
					k += 1;
				}
			}
			quantity.push_back(k);
		}
	}
}
int numbers(string filename) {
	ifstream file(filename);
	string str;
	int k=0;
	while (getline(file, str)) {
		for (int i = 0;i < str.size();i++) {
			if ((int)str[i] >= 48 && (int)str[i] <= 57) {
				k += 1;
			}
		}
	}
	return k;
}
int main() {
	ifstream file("file.txt");
	string oldword, newword;
	vector<int> quantity;
	vector<char> letters;
	cout << "Enter the word you want to replace: ";
	cin >> oldword;
	cout << "Enter new word: ";
	cin >> newword;
	replaceinfile("file.txt", oldword, newword);
	upperletter("file.txt");
	eachletter("file.txt", letters, quantity);
	for (int i = 0;i < letters.size();i++) {
		cout << letters[i] << " - " << quantity[i] << endl;
	}
	int k = numbers("file.txt");
	cout << "Numbers - " << k << endl;
	return 0;
}