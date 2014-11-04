/** COMMENTS ********************************************************/
/*	Your name: Stefan Kussmaul
	Class block: A			Date: 5/27/14
	Title: Everything Quadratics
*/

/** INCLUDE FILES ***************************************************/

#include <iostream>	//	input output commands:	cout & cin
#include <math.h>
using namespace std;

/** FUNCTION PROTOTYPES**********************************************/
void InputEquation(double parameters [8]);
void Roots(double parameters [8]);
void Vertex(double parameters [8]);
void Options(int settings [7]);
void Intercepts(double parameters [8]);
void Table(double parameters [8], int settings [7]);
void Display(double parameters [8], int settings [7]);
void Factor(double parameters [8]);
string TrueFalse(int n);

/** MAIN FUNCTION ***************************************************/
int main()
{
	int settings[7] = {1,1,1,1,1,-10,10}; // just for now, until I can write a real options menu
	             /* 0 - vertex
	              * 1 - y intercept
	              * 2 - table
	              * 3 - sum and product
	              * 4 - factor
	              * 5 - table lower bound
	              * 6 - table upper bound */
	double parameters[8];
	/* 0 - a
	 * 1 - b
	 * 2 - c
	 * 3 - x-value of vertex
	 * 4 - y-value of vertex
	 * 5 - solution 1
	 * 6 - solution 2
	 * 7 - no solutions
	 */
	cout << "Everything Quadratics!\n";
	cout << "      Press enter\n";
	cin.get();
	int menu_input;
	do
	{
		cout << "\nAvailable Functions\n";
		cout << "---------------------------------\n";
		cout << "1. Options\n";
		cout << "2. Equation\n";
		cout << "3. Quit\n";
		cout << "---------------------------------\n";
		cout << "Enter choice: ";
		cin >> menu_input;
	if(menu_input == 1)
		Options(settings);
	else if(menu_input == 2)
		{
		InputEquation(parameters);
		Roots(parameters);
		Display(parameters, settings);
		}
	cout << "\n\nHit enter to return to menu "; // not working
	cin.get(); 
	cin.get(); /* has to be repeated once */ 
	}while(menu_input != 3);
   return 0;
}

/** FUNCTIONS *******************************************************/
void InputEquation(double parameters [8])
{
	cout << "Equation will be entered in the form ax^2 + bx + c = 0\n\n";
	cout << "Enter << a >> term: ";
	cin >> parameters[0];
	cout << "Enter << b >> term: ";
	cin >> parameters[1];
	cout << "Enter << c >> term: ";
	cin >> parameters[2];
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
//		y_intercept_value = parameters[2]; /// can't remember the purpose of this function
}
void Options(int settings [7])
{
	cout << "\n\nSettings: \n";
	cout << "---------------------------------------------\n";
	string symbol = TrueFalse(settings[0]);
	cout << "1. Calculate Vertex......................." << symbol << endl;
	symbol = TrueFalse(settings[1]);
	cout << "2. Calculate y-Intercept.................." << symbol << endl;
	symbol = TrueFalse(settings[2]);
	cout << "3. Print Table............................" << symbol << endl;
	cout << "4. Set Table Parameters...................(" << settings[5] << "," << settings[6] << ")\n";
	symbol = TrueFalse(settings[4]);
	cout << "5. Factor Equation........................" << symbol << endl;
	symbol = TrueFalse(settings[3]);
	cout << "6. Calculate Sum and Product.............." << symbol << endl;
	cout << "7. Back to Main Menu\n";
	cout << "---------------------------------------------\n\n";
	cout << "Enter number of choice you would like to change: ";
	int choice;
	cin >> choice;
}
void Table(double parameters [8], int settings [7])
{
	cout << "settings[2]\n";
	cout << "   x             f(x)\n";
	for(int i = settings[5]; i <= settings[6]; i++)
	{
		cout << "   " << i << "          " << parameters[0] * i * i + parameters[1] * i + parameters[2] << endl;
	}
}
void Display(double parameters [8], int settings [7])
{
	if(settings[0] == 1)
		Vertex(parameters);
	if(settings[1] == 1)
		Intercepts(parameters);
	cout << "Equation: " << parameters[0] << "x^2 + " << parameters[1] << "x + " << parameters[2] << " = 0\n";
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
	if(settings[4] == 1 && parameters[7] == 0)
		Factor(parameters);
	if(settings[0] == 1)
		cout << "Vertex at point (" << parameters[3] << "," << parameters[4] << ")\n";
	if(settings[1] == 1)
		cout << "y-Intercept at point (0," << parameters[1] << ")\n";
	if(settings[2] == 1)
		Table(parameters, settings);
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
string TrueFalse(int n) {
	if(n == 1)
		return "TRUE";
	else if(n == 0)
		return "FALSE";
}
