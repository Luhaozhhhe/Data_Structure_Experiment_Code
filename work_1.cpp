/*
#include<iostream>
#include<fstream>
using namespace std;
long long fibonacci(int n) {
	if (n == 1 || n == 2) {
		return 1;
	}
	else {
		return fibonacci(n - 1) + fibonacci(n - 2);
	}
}



int main() {
	ifstream in("input.txt");
	int n;
	in>> n;
	

	if (n < 0 || n>90) {
		cout << "WRONG" << endl;
	}
	else {
		cout << fibonacci(n) << endl;
	}

	return 0;
}
*/
#include<iostream>
#include<fstream>
using namespace std;
long long Fibonacci(long long *F, int n)
{
	F[0] = 0;
	if (F[n]!=0||n==0)
	{
		return F[n];
	}
	else
	{
		F[n] = Fibonacci(F, n - 1) + Fibonacci(F, n - 2);
	}
	return F[n];
}
int main()
{
	ifstream infile("input.txt");
	int n;
	infile >> n;
	long long *F= new long long[91];
	F[1] = F[2] = 1;
	for (int i = 3; i < 91; i++)
	{
		F[i] = 0;
	}
	if (n < 0 || n > 90)
	{
		cout << "WRONG" << endl;
	}
	else
	{
		
		F[n] = Fibonacci(F, n);
		cout << F[n] << endl;
	}
}