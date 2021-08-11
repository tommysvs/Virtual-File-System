#include <iostream>
#include <conio.h>
#include "system.h"

using namespace std;

int main() {
	string text;

	System system;

	cout << "user:$ ";
	getline(cin, text);

	while (true)
		system.get_input(text);

	_getch();
}