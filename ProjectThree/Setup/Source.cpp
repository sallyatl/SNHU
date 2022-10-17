/* 
Project Three  
Sally Keith
CS 210
10/10/22 
*/

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

/* This is the menu function that will be called in main */

void Menu() {
	bool program_Run = true;
	bool correct_Input;
	int userNum;

	// boolean for true or false, so that the program keeps running after the user selects a choice
	// do operation for this as well that starts by printing the menu with choices 

	do {
		cout << "" << endl;
		cout << "-- The Corner Grocer --" << endl;
		cout << "1. All Items Purchased History" << endl;
		cout << "2. Individual Item Purchase history" << endl;
		cout << "3. Histogram" << endl;
		cout << "4. Exit Program" << endl;
		cout << "Enter your selection as a number 1, 2, 3, or 4." << endl;

	// try operation, where user can enter their choice 
	// error code when input is invalid 

		try {
			std::cin >> userNum;

			while (cin.fail()) {
				cin.clear();
				cin.ignore(256, '\n');
				cout << "" << endl;
				cout << "*** Error: Enter your selection as a number 1, 2, 3, or 4 ***" << endl;
				cout << "" << endl;
			}

			if (userNum >= 0) {
				correct_Input = true;
			}
			else { throw (userNum); }

		}

		catch (...) { cout << "*** Error: Enter your selection as a number 1, 2, 3, or 4 ***" << endl; }

	// the if operation for the menu choices that calls the python functions 

		if (userNum == 1) {

			cout << "" << endl;
			cout << "- All Items Purchased History -" << endl;
			cout << "-Item-               -Quantity-" << endl;
			CallProcedure("ReadList");
		}
		else if (userNum == 2) {
			string userInput;

			cout << "" << endl;
			cout << "Enter the Item name: " << endl;

	// asks for user input again for this choice 
	// provides error message if item is not found on the list 

			std::cin >> userInput;

			int totalpurchase = callIntFunc("PurchaseHistory", userInput);

			if (totalpurchase = -1) {
				cout << "The Item could not be located in the file. Please try again." << endl;
			}
			else {
				cout << totalpurchase << " " << userInput << " sold." << endl;
			}
		}
		else if (userNum == 3) {
			cout << "" << endl;
			CallProcedure("readAndWrite");
		}
		else { program_Run = false; }
	} while (program_Run == true);
}

	// the main function which calls the menu function

int main() {
	
	Menu();
	return 0;

}