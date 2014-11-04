/** COMMENTS ********************************************************/
/*	Your name: Stefan Kussmaul
	Class block: A			Date: 5/27/14
	Title: Everything Quadratics
*/

/** INCLUDE FILES ***************************************************/

#include <iostream>	//	input output commands:	cout & cin
#include <math.h>
using namespace std;

// CHANGE "SIMPLIFY" FUNCTION TO "STANDARDIZE" FUNCTION, CHANGE ALL OCCURENCES TO SAY "STANDARD FORM"
// CHANGE "SOLUTIONS" TO "ROOTS" FUNCTION, CHANGE ALL OCCURENCES TO SAY "ROOTS"
// ADD IN CHECKS TO MAKE SURE FUNCTION ENTERED IS VALID
// ADD IN FACTORED FORM
// ADD IN SUM AND PRODUCT OF ROOTS
// ADD COMPLEX SOLUTIONS
// WORK OUT WHAT HAPPENS WHEN YOU HAVE + A NEGATIVE NUMBER


/** FUNCTION PROTOTYPES**********************************************/
void InputEquation(double parameters [8]);
void Roots(double parameters [8]);
void Vertex(double parameters [8]);
void Options(int settings [7]);
void Intercepts(double parameters [8]);
void Table(double parameters [8], int settings [7]);
void Display(double parameters [8], int settings [7]);
void Factor(double parameters [8]);

/** MAIN FUNCTION ***************************************************/
int main()
{
	/** VARIABLE DECLARATION ****************************************/
	int menuInput, settings[5] = 0, settings[6] = 0;
	bool plotting = 0, vertex = 1, settings[1] = 1, settings[2] = 1, parameters[7] = 0, settings[3] = 1, factor = 1;
	double orig_a, orig_b, orig_c, origD, origE, origF, parameters[0], parameters[1], parameters[2], parameters[3], parameters[4], settings[1]_value = 0, parameters[5], parameters[6];
	/** FUNCTION CALLS***********************************************/
	int settings[7];
	             /* 0 - vertex
	              * 1 - settings[1]
	              * 2 - settings[2]
	              * 3 - settings[3]
	              * 4 - factor
	              * 5 - settings[5]
	              * 6 - settings[6] */
	double parameters[8];
	/* 0 - a
	 * 1 - b
	 * 2 - c
	 * 3 - parameters[3]
	 * 4 - parameters[4]
	 * 5 - parameters[5]
	 * 6 - parameters[6]
	 * 7 - parameters[7]
	 */
	cout << "Everything Quadratics!\n";
	cout << "      Press enter\n";
	cin.get();
	do
	{
		cout << "\nAvailable Functions\n";
		cout << "---------------------------------\n";
		cout << "1. Options\n";
		cout << "2. Equation\n";
		cout << "3. Quit\n";
		cout << "---------------------------------\n";
		cout << "Enter choice: ";
		cin >> menuInput;
	if(menuInput == 1)
		Options(settings);
	else if(menuInput == 2)
		{
		InputEquation(parameters);
		Roots(parameters);
		Display(parameters, settings);
		}
	cout << "\n\nHit enter to return to menu ";
	cin.get();
	}while(menuInput != 3);
   return 0;
}

/** FUNCTIONS *******************************************************/
void InputEquation(double parameters [8])
{
	string raw_equation, a = "", b = "", c = "";
	cout << "Equation will be entered in the form ax^2 + bx + c = 0\n\n";
	cout << "Enter equation: ";
	getline(cin, raw_equation);
	getline(cin, raw_equation); /* has to be repeated */
/*	int location_a = raw_equation.find('x^2');
	for(int i = location_a; i >= 0; i--) {

	}
*/	cout << "Equation will be enter in the form ax^2 + bx + c = dx^2 + ex + f.\n";
	cout << "Enter << a >> term: ";
	cin >> orig_a;
	cout << "Enter << b >> term: ";
	cin >> orig_b;
	cout << "Enter << c >> term: ";
	cin >> orig_c;
	cout << "Enter << d >> term: ";
	cin >> origD;
	cout << "Enter << e >> term: ";
	cin >> origE;
	cout << "Enter << f >> term: ";
	cin >> origF;
}
void Roots(double parameters [8])
{
	int discriminant;
	discriminant = parameters[1] * parameters[1] - 4 * parameters[0] * parameters[2];
	if(discriminant < 0)
		parameters[7] = 1;
	else
	{
	parameters[5] = ((-1 * parameters[1]) + sqrt(parameters[1] * parameters[1] - 4 * parameters[0] * parameters[2])) / (2 * parameters[0]);
	parameters[6] = ((-1 * parameters[1]) - sqrt(parameters[1] * parameters[1] - 4 * parameters[0] * parameters[2])) / (2 * parameters[0]);
	}
}
void Vertex(double parameters [8])
{
	parameters[3] = (parameters[1] * -1) / (2 * parameters[0]);
	parameters[4] = parameters[0] * parameters[3] * parameters[3] + parameters[1] * parameters[3] + parameters[2];
}
void Intercepts(double parameters [8])
{
		settings[1]_value = parameters[2];
}
void Options(int settings [7])
{
	char choice;
	cout << "Calculate Vertex? (y/n) ";
	cin >> choice;
		if(choice == 'y')
			vertex = 1;
		else
			vertex = 0;
//	choice = 'n';
	cout << "Calculate y-Intercept? (y/n) ";
	cin >> choice;
		if(choice == 'y')
			settings[1] = 1;
		else
			settings[1] = 0;
//	choice = 'n';
	cout << "Display settings[2]? (y/n) ";
	cin >> choice;
		if(choice == 'y')
		{
			settings[2] = 1;
			choice = 'n';
			do
			{
			cout << "Enter lower bound for settings[2]: ";
			cin >> settings[5];
			cout << "Enter upper bound for settings[2]: ";
			cin >> settings[6];
				if(settings[5] > settings[6])
					cout << "Error! Lower bound cannot be greater than upper bound!\n";
			}while(settings[5] > settings[6]);
		}
		else
			settings[2] = 0;
//	choice = 'n';
	cout << "Calculate sum and product of roots? (y/n)";
	cin >> choice;
	if(choice == 'y')
		settings[3] = 1;
	else
		settings[3] = 0;
//	choice = 'n';
	cout << "Display factored form? (y/n)";
	cin >> choice;
	if(choice == 'y')
		factor = 1;
	else
		factor = 0;
}
void settings[2](double parameters [8], int settings [7])
{
	int x;
	cout << "settings[2]\n";
	cout << "   x             f(x)\n";
	for(x = settings[5]; x <= settings[6]; x++)
	{
		cout << "   " << x << "          " << parameters[0] * x * x + parameters[1] * x + parameters[2] << endl;
	}
}
void Display(double parameters [8], int settings [7])
{
	if(vertex == 1)
		Vertex(parameters[0], parameters[1], parameters[2], parameters[3], parameters[4]);
	if(settings[1] == 1)
		Intercepts(parameters[0], parameters[1], parameters[2], settings[1]_value);
	cout << "Original Equation: " << orig_a << "x^2 + " << orig_b << "x + " << orig_c << " = " << origD << "x^2 + " << origE << "x + " << origF << endl;
	cout << "Equation in Standard Form: " << parameters[0] << "x^2 + " << parameters[1] << "x + " << parameters[2] << " = 0\n";
	if(parameters[7] == 1)
		cout << "Equation has no solutions\n";
	else
	{
		if(parameters[5] == parameters[6])
			cout << "Root is x= " << parameters[5] << endl;
		else
			cout << "Roots are x = " << parameters[5] << " and x = " << parameters[6] << endl;
	}
	if(settings[3] == 1 && parameters[7] == 0)
		{
		cout << "Sum of roots = " << parameters[5] + parameters[6] << endl; // NOT SURE WHAT HAPPENS IF ONLY ONE SOLUTION
		cout << "Product of roots = " << parameters[5] * parameters[6] << endl;
		}
	if(factor == 1 && parameters[7] == 0)
		Factor(parameters[0], parameters[5], parameters[6], parameters[7]);
	if(vertex == 1)
		cout << "Vertex at point (" << parameters[3] << "," << parameters[4] << ")\n";
	if(settings[1] == 1)
		cout << "y-Intercept at point (0," << settings[1]_value << ")\n";
	if(settings[2] == 1)
		settings[2](settings[5], settings[6], parameters[0], parameters[1], parameters[2]);
}
void Factor(double parameters [8])
{
	if(parameters[5] == parameters[6])
	{
		cout << parameters[0] << "(x-" << parameters[5] << ")^2\n";
	}
	else
		cout << parameters[0] << "(x-" << parameters[5] << ")(x-" << parameters[6] << ")\n";
}
