#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <signal.h>
#include <iostream>
#include "Tests.h"
#include "UI.h"

using std::cout;

//void clear_screen_handler(int signal) {
//	system("cls");
//	cout << signal;
//}


void run() {
	Tests tests;
	tests.runAllTests();

	BookRepository bookRepository;
	Validator bookValidator;
	Library bookLibrary{ bookRepository, bookValidator };
	ConsoleUI ui{ bookLibrary };


	ui.run();
}


int main() {
	//signal(SIGINT, clear_screen_handler);
	run();

	_CrtDumpMemoryLeaks();
	return 0;
}	