#include<iostream>
#include<fstream>
using namespace std;
int a[26];
void change(int a[]) {
	for (int i = 0; i < 26; i++) {
		if (a[i]) cout << char('a' + i) << " ";
	}
	cout << endl;
}
void findzc(int first, int len, int a[]) {
	if (len == 0) return;
	else {
		a[first] = 1;
		change(a);
		findzc(first + 1, len - 1, a);
		a[first] = 0;
		findzc(first + 1, len - 1, a);
	}
}
int main() {
	ifstream infile("input.txt");
	int n;
	infile >> n;
	if (n < 1 || n>26) {
		cout << "WRONG" << endl;
		return 0;
	}
	findzc(0, n, a);
	return 0;
}