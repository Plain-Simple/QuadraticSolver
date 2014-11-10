/// REMINDER: Function names should be command verbs (ie. PrintTable(), FindIntercepts())



/** COMMENTS ********************************************************/
/*	Your name: Stefan Kussmaul
	Class block: A			Date: 5/27/14
	Title: Everything Quadratics
*/

/** INCLUDE FILES ***************************************************/

#include <iostream>	//	input output commands:	cout & cin
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;


/** FUNCTION PROTOTYPES**********************************************/
/* equation_standard[3], vertex[2], solution[2], has_solution is a bad name */
void InputEquation(double equation_standard[3], double vertex[2], double solution[2], bool & has_solution);
void CalculateRoots(double equation_standard[3], double vertex[2], double solution[2], bool & has_solution);
void CalculateVertex(double equation_standard[3], double vertex[2], double solution[2], bool & has_solution);
void Options(bool & calc_vertex, bool & calc_yintercept, bool & print_table, bool & calc_sumproduct, bool & factor_equation, int table_boundaries[2]);
void Intercepts(double equation_standard[3], double vertex[2], double solution[2], bool & has_solution);
void Table(double equation_standard[3], double vertex[2], double solution[2], bool & has_solution, bool calc_vertex, bool calc_yintercept, bool print_table, bool calc_sumproduct, bool factor_equation, int table_boundaries[2]);
void Display(double equation_standard[3], double vertex[2], double solution[2], bool & has_solution, bool calc_vertex, bool calc_yintercept, bool print_table, bool calc_sumproduct, bool factor_equation, int table_boundaries[2]);
void Factor(double equation_standard[3], double vertex[2], double solution[2], bool & has_solution);
void LoadSettings(bool & calc_vertex, bool & calc_yintercept, bool & print_table, bool & calc_sumproduct, bool & factor_equation, int table_boundaries[2]);
string BoolToString(bool bool_to_convert);
bool CharToBool(char c);
char BoolToChar(bool b);
string IntToString(int n);

/** MAIN FUNCTION ***************************************************/
int main() {
  bool calc_vertex = true, calc_yintercept = true, print_table = true, calc_sumproduct = true, factor_equation = true;
  int table_boundaries[2] = { -10, 10};
  double equation_standard[3], vertex[2], solution[2];
  bool has_solution;
  cout << "Plain+Simple Quadratic Solver\n";
  cout << "        Press enter\n";
  cin.get();
  int menu_input;
  do {
	  LoadSettings(calc_vertex, calc_yintercept, print_table, calc_sumproduct, factor_equation, table_boundaries);
    cout << "\nAvailable Functions\n";
    cout << "---------------------------------\n";
    cout << "1. Options\n";
    cout << "2. Equation\n";
    cout << "3. Quit\n";
    cout << "---------------------------------\n";
    cout << "Enter choice: ";
    cin >> menu_input;
    if(menu_input == 1) {
      Options(calc_vertex, calc_yintercept, print_table, calc_sumproduct,
              factor_equation, table_boundaries);
    } else if(menu_input == 2) {
      InputEquation(equation_standard, vertex, solution, has_solution);
      CalculateRoots(equation_standard, vertex, solution, has_solution);
      Display(equation_standard, vertex, solution, has_solution, calc_vertex,
              calc_yintercept, print_table, calc_sumproduct, factor_equation,
              table_boundaries);
      /// TODO: Input checker, quit function
    }
    cout << "\n\nHit enter to return to menu "; // not working
    /// this happens when we use a combination of cin, getline, and other stuff. We will have to figure out one to use to standardize everything
    cin.get();
    cin.get(); /* has to be repeated once */
  } while(menu_input != 3);
  return 0;
}

/** FUNCTIONS *******************************************************/
void InputEquation(double equation_standard[3], double vertex[2],
                   double solution[2], bool & has_solution) {
  cout << "Equation will be entered in the form ax^2 + bx + c = 0\n\n";
  cout << "Enter << a >> term: ";
  cin >> equation_standard[0];
  cout << "Enter << b >> term: ";
  cin >> equation_standard[1];
  cout << "Enter << c >> term: ";
  cin >> equation_standard[2];
}
void CalculateRoots(double equation_standard[3], double vertex[2], double solution[2],
           bool & has_solution) {
  int discriminant;
  discriminant = equation_standard[1] * equation_standard[1] - 4 *
                 equation_standard[0] *
                 equation_standard[2];
  if(discriminant < 0) {
    has_solution = false;
  } else {
    has_solution = true;
    solution[0] = ((-1 * equation_standard[1]) + sqrt(equation_standard[1] *      equation_standard[1] - 4 *
                   equation_standard[0] * equation_standard[2])) / (2 * equation_standard[0]);
    solution[1] = ((-1 * equation_standard[1]) - sqrt(equation_standard[1] *
                   equation_standard[1] - 4 *
                   equation_standard[0] * equation_standard[2])) / (2 * equation_standard[0]);
  }
}
void CalculateVertex(double equation_standard[3], double vertex[2], double solution[2],
            bool & has_solution) {
  vertex[0] = (equation_standard[1] * -1) / (2 * equation_standard[0]);
  vertex[1] = equation_standard[0] * vertex[0] * vertex[0] + equation_standard[1]
              *
              vertex[0] + equation_standard[2];
}
void Intercepts(double equation_standard[3], double vertex[2],
                double solution[2], bool & has_solution) {
  //		y_intercept_value = equation_standard[2]; /// can't remember the purpose of this function
}
void Options(bool & calc_vertex, bool & calc_yintercept, bool & print_table,
             bool & calc_sumproduct, bool & factor_equation, int table_boundaries[2]) {
	string string_settings = "";
  LoadSettings(calc_vertex, calc_yintercept, print_table, calc_sumproduct,
               factor_equation, table_boundaries);
  cout << "\n\nSettings: \n";
  cout << "---------------------------------------------\n";
  string symbol = BoolToString(calc_vertex);
  cout << "1. Calculate Vertex......................." << symbol << endl;
  symbol = BoolToString(calc_yintercept);
  cout << "2. Calculate y-Intercept.................." << symbol << endl;
  symbol = BoolToString(calc_sumproduct);
  cout << "3. Calculate Sum and Product.............." << symbol << endl;
  symbol = BoolToString(factor_equation);
  cout << "4. Factor Equation........................" << symbol << endl;
  symbol = BoolToString(print_table);
  cout << "5. Print Table............................" << symbol << endl;
  cout << "6. Set Table Boundaries...................("
       << table_boundaries[0] << "," << table_boundaries[1] << ")\n"; /// looks like we have some problems here, I'll fix that very soon
  cout << "7. Back to Main Menu\n";
  cout << "---------------------------------------------\n\n";
  cout << "Enter number of choice you would like to change: ";
  int choice;
  cin >> choice;
  switch(choice) {
  case 1:
    calc_vertex = !calc_vertex;
    symbol = BoolToString(calc_vertex);
    cout << "Calculate Vertex set to << " << symbol << " >>\n";
    break;
  case 2:
    calc_yintercept = ! calc_yintercept;
    symbol = BoolToString(calc_yintercept);
    cout << "Calculate y-Intercept set to << " << symbol << " >>\n";
    break;
  case 3:
    print_table = !print_table;
    symbol = BoolToString(print_table);
    cout << "Print Table set to << " << symbol << " >>\n";
    break;
  case 4:
    calc_sumproduct = !calc_sumproduct;
    symbol = BoolToString(calc_sumproduct);
    cout << "Calculate Sum and Product set to << " << symbol << " >>\n";
    break;
  case 5:
    factor_equation = !factor_equation;
    symbol = BoolToString(factor_equation);
    cout << "Factor Equation set to << " << symbol << " >>\n";
    break;
  case 6:
    cout << "Enter lower bound: ";
    cin >> table_boundaries[0];
    cout << "Enter upper bound: ";
    cin >> table_boundaries[1];
    cout << "New bounds set to (" << table_boundaries[0] << "," << table_boundaries[1] << ")\n";
    break;
  case 7:
	  break; /* this does nothing so that the thing after the switch case takes it but it doesn't activate the default case */
  default:
    /// it should give the user an error
    break;
  }
  string_settings = string_settings + BoolToChar(calc_vertex) + BoolToChar(calc_yintercept) + BoolToChar(print_table);
  string_settings = string_settings + BoolToChar(calc_sumproduct) + BoolToChar(factor_equation);
  string_settings = string_settings + IntToString(table_boundaries[0]) + ',' + IntToString(table_boundaries[1]);

  ofstream settings_file("quadratics_settings");
  if(settings_file.is_open()) {
    settings_file << string_settings;
  }
  settings_file.close();
}
void Table(double equation_standard[3], double vertex[2], double solution[2],
           bool & has_solution, bool calc_vertex, bool calc_yintercept, bool print_table,
           bool calc_sumproduct, bool factor_equation, int table_boundaries[2]) {
  cout << "   x             f(x)\n";
  for(int i = table_boundaries[0]; i <= table_boundaries[1]; i++) {
    cout << "   " << i << "          " << equation_standard[0] * i * i +
         equation_standard[1] * i
         + equation_standard[2] << endl;
  }
}
void Display(double equation_standard[3], double vertex[2], double solution[2],
             bool & has_solution, bool calc_vertex, bool calc_yintercept, bool print_table,
             bool calc_sumproduct, bool factor_equation, int table_boundaries[2]) {
	cout << endl << endl;
  if(calc_vertex == 1) {
    CalculateVertex(equation_standard, vertex, solution, has_solution);
  }
  if(calc_yintercept == 1) {
    Intercepts(equation_standard, vertex, solution, has_solution);
  }
  cout << "Equation: ";
  if(equation_standard[0] == 1)
	  cout << "x^2 ";
  else if(equation_standard[0] != 0)
	  cout << equation_standard[0] << "x^2 ";
  if(equation_standard[1] > 0)
	  cout << "+ ";
  else if(equation_standard[0] < 0)
	  cout << "- ";
  if(equation_standard[1] == 1)
	  cout << "x ";
  else if(equation_standard[1] != 0)
	  cout << equation_standard[1] << "x ";
  if(equation_standard[2] > 0)
	  cout << "+ ";
  else if(equation_standard[2] < 0)
	  cout << "- ";
  if(equation_standard[2] != 0)
       cout << equation_standard[2];
  cout << " = 0\n";
  if(!has_solution) {
    cout << "Equation has no solutions\n";
  } else {
    if(solution[0] == solution[1]) {
      cout << "Root(s): (0," << solution[1] << ")";
    } if(solution[0] != solution[1]) {
      cout << " and (0," << solution[1] << ")";
    }
    cout << endl;
  }
  if(calc_sumproduct) {
    cout << "Sum of roots = " << solution[0] + solution[1] <<
         endl;
    cout << "Product of roots = " << solution[0] * solution[1] << endl;
  }
  if(factor_equation) {
    Factor(equation_standard, vertex, solution, has_solution);
  }
  if(calc_vertex == 1) {
    cout << "Vertex: (" << vertex[0] << "," << vertex[1] << ")\n";
  }
  if(calc_yintercept == 1) {
    cout << "y-Intercept: (0," << equation_standard[1] << ")\n";
  }
  if(print_table == 1) {
    Table(equation_standard, vertex, solution, has_solution, calc_vertex,
          calc_yintercept, print_table, calc_sumproduct, factor_equation,
          table_boundaries);
  }
}
void Factor(double equation_standard[3], double vertex[2], double solution[2],
            bool & has_solution) {
	cout << "Factored: ";
  if(solution[0] == solution[1]) {
    if(equation_standard[0] == 0)
    	cout << "0";
    else if(equation_standard[0] != 1)
	  cout << equation_standard[0];
	if(equation_standard[0] != 0) {
	  cout << "(x ";
	  if(solution[0] == 0)
		  cout << ")^2\n";
	  else if(solution[0] > 1)
		  cout << "- " << solution[0] << ")^2\n";
	  else
		  cout << "+ " << -1 * solution[0] << ")^2\n";
    }
  } else {
    cout << equation_standard[0] << "(x-" << solution[0] << ")(x-" << solution[1] <<
         ")\n";
  }
}
string BoolToString(bool bool_to_convert) {
  if(bool_to_convert == true) {
    return "TRUE";
  } else {
    return "FALSE";
  }
}
/// this should probably be a bool to return a success or failure of load
void LoadSettings(bool & calc_vertex, bool & calc_yintercept,
                  bool & print_table, bool & calc_sumproduct, bool & factor_equation,
                  int table_boundaries[2]) {
  /// this needs to be seriously reworked now that we have moved away from arrays - this is a github todo
	string line, table_lower_bound = "", table_upper_bound = "";
	bool comma_reached = 0;
	ifstream settings_file("quadratics_settings");
	if(settings_file.is_open()) {
		while ( getline (settings_file, line) ) {
			calc_vertex = CharToBool(line[0]);
			calc_yintercept = CharToBool(line[1]);
			print_table = CharToBool(line[2]);
			calc_sumproduct = CharToBool(line[3]);
			factor_equation = CharToBool(line[4]);
			for(int i = 5; i < line.size(); i++) {
				if(line[i] == ',') {
					comma_reached = 1;
				}
				else if(!(comma_reached))
					table_lower_bound = table_lower_bound + line[i]; /* build table_boundaries[0] */
				else if(comma_reached)
					table_upper_bound = table_upper_bound + line[i]; /* build table_boundaries[1] */
			}
			table_boundaries[0] = atoi(table_lower_bound.c_str());
			table_boundaries[1] = atoi(table_upper_bound.c_str());
		} settings_file.close();
	} else { /* set default values and write "quadratics_settings" with default values */
		calc_vertex = true;
		calc_yintercept = true;
		print_table = true;
		calc_sumproduct = true;
		factor_equation = true;
		table_boundaries[0] = -10;
		table_boundaries[1] = 10;
		ofstream settings_file("quadratics_settings");
		if (settings_file.is_open()) {
			settings_file << "11111-10,10";
			settings_file.close();
		}
	}
}
bool CharToBool(char c) {
	if(c == '0')
		return false;
	else
		return true;
}
char BoolToChar(bool b) {
	if(b == 0)
		return '0';
	else
		return '1';
}
string IntToString(int n) { /// had to write my own function because there weren't any good references online
	bool is_negative = 0;
	char digit;
	int number, remainder; /// kind of bad names
	string s = "";
	number = n;
	if(number < 0) {
		is_negative = 1;
		number = number * -1;
	} while(number != 0) { /* loops until whole number has been converted */
		remainder = number % 10;
		number = number / 10;
		digit = char(remainder + 48); /* convert remainder to a char */
		s = digit + s; /* build s */
	} if(is_negative)
		s = '-' + s;
	return s;
}



