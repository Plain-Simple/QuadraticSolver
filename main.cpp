/// REMINDER: Function names should be command verbs (ie. PrintTable(), FindIntercepts())

/// note - we need to figure out how to use the settings. Should all the functions be called and the functions decide whether to run, or should functions only be called if they are set to run in settins?


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
/* equation[3], vertex[2], solution[2], has_solution is a bad name */
/// please explain what makes them bad
/* gets equation from the user */
void InputEquation(double equation[3]);
/* finds the quadratic rots of the equation */
void CalculateRoots(double equation[3], double solution[2], bool & has_solution);
/* finds the vertex of the parabola */
void CalculateVertex(double equation[3], double vertex[2]);
/// description needed, also options needs to be a verb
void Options(bool & calc_vertex, bool & calc_yintercept, bool & print_table, bool & calc_sumproduct, bool & factor_equation, int table_boundaries[2]);
/* takes in an equation and returns its y intercept */
double CalculateYIntercept(double equation[3]);
/* outputs a table of values for the equation */
/// does it really need all these parameters?
void Table(double equation[3], double vertex[2], double solution[2], bool & has_solution, bool calc_vertex, bool calc_yintercept, bool print_table, bool calc_sumproduct, bool factor_equation, int table_boundaries[2]);
/// description needed
void Display(double equation[3], double vertex[2], double solution[2], bool & has_solution, bool calc_vertex, bool calc_yintercept, bool print_table, bool calc_sumproduct, bool factor_equation, int table_boundaries[2]);
/// description needed
void Factor(double equation[3], double vertex[2], double solution[2], bool & has_solution);
/// description needed - also, we need to decide on settings vs options
void LoadSettings(bool & calc_vertex, bool & calc_yintercept, bool & print_table, bool & calc_sumproduct, bool & factor_equation, int table_boundaries[2]);
/* returns the result of plugging int x into double equation[3] */
double PlugIn(double x, double equation[3]);

/* the following are type conversion functions: */
string BoolToString(bool bool_to_convert);
bool CharToBool(char c);
char BoolToChar(bool b);


/** MAIN FUNCTION ***************************************************/
int main() {
  bool calc_vertex = true, calc_yintercept = true, print_table = true,
       calc_sumproduct = true, factor_equation = true;
  int table_boundaries[2] = { -10, 10};
  double equation[3], vertex[2], solution[2];
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
    switch (menu_input) {
      case 1:
        Options(calc_vertex, calc_yintercept, print_table, calc_sumproduct,
                factor_equation, table_boundaries);
        break;
      case 2:
        InputEquation(equation);
        CalculateRoots(equation, solution, has_solution);
        Display(equation, vertex, solution, has_solution, calc_vertex,
                calc_yintercept, print_table, calc_sumproduct, factor_equation,
                table_boundaries);
        break;
      case 3:
        exit(0);
        break;
      default:
        /// check input
        break;
    }
    cout << "\n\nHit enter to return to menu "; // not working
     /// what isn't working? In what way?
    /// this happens when we use a combination of cin, getline, and other stuff. We will have to figure out one to use to standardize everything
    cin.get();
    cin.get(); /* has to be repeated once */
  } while(menu_input != 3);
  return 0;
}

/** FUNCTIONS *******************************************************/
void InputEquation(double equation[3]) {
  cout << "Equation will be entered in the form ax^2 + bx + c = 0\n\n";
  for (int i = 0; i < 3; i++) {
    cout << "Enter << " << i + 99 << " >> term: ";
    cin >> equation[i];
  }
}
void CalculateRoots(double equation[3], double solution[2], bool & has_solution) {
  /* b^2 - 4ac */
  int discriminant = pow(equation[1], 2) - (4 * equation[0] * equation[2]);
  if (discriminant < 0) {
    has_solution = false;
  } else {
    has_solution = true;
    /* -b + root b^2 - 4ac / 2a */
    solution[0] = (-equation[1] + sqrt(discriminant)) / (2 * equation[0]);
    /* -b - root b^2 - 4ac / 2a */
    solution[1] = (-equation[1] - sqrt(discriminant)) / (2 * equation[0]);
  }
}
void CalculateVertex(double equation[3], double vertex[2]) {
  vertex[0] = (-equation[1]) / (2 * equation[0]);
  vertex[1] = PlugIn(vertex[0], equation);
}
double CalculateYIntercept(double equation[3]) {
  return PlugIn(0, equation);
}
void Options(bool & calc_vertex, bool & calc_yintercept, bool & print_table,
             bool & calc_sumproduct, bool & factor_equation, int table_boundaries[2]) {
  LoadSettings(calc_vertex, calc_yintercept, print_table, calc_sumproduct,
               factor_equation, table_boundaries);
  cout << "\n\nSettings: \n"
       << "---------------------------------------------\n"
       << "1. Calculate Vertex......................."
       << BoolToString(calc_vertex)
       << "\n2. Calculate y-Intercept.................."
       << BoolToString(calc_yintercept)
       << "\n3. Calculate Sum and Product.............."
       << BoolToString(calc_sumproduct)
       << "\n4. Factor Equation........................"
       << BoolToString(factor_equation)
       << "\n5. Print Table............................"
       << BoolToString(print_table)
       << "\n6. Set Table Boundaries...................("
       /// looks like we have some problems here, I'll fix that very soon
       << table_boundaries[0] << "," << table_boundaries[1] << ")\n"
       << "\n7. Back to Main Menu\n"
       << "---------------------------------------------\n\n"
       << "Enter number of choice you would like to change: ";
  int choice;
  cin >> choice;
  switch(choice) {
  case 1:
    calc_vertex = !calc_vertex;
    cout << "Calculate Vertex set to << " << BoolToString(calc_vertex) << " >>\n";
    break;
  case 2:
    calc_yintercept = ! calc_yintercept;
    cout << "Calculate y-Intercept set to << " << BoolToString(calc_yintercept) << " >>\n";
    break;
  case 3:
    print_table = !print_table;
    cout << "Print Table set to << " << BoolToString(print_table) << " >>\n";
    break;
  case 4:
    calc_sumproduct = !calc_sumproduct;
    cout << "Calculate Sum and Product set to << " << BoolToString(calc_sumproduct) << " >>\n";
    break;
  case 5:
    factor_equation = !factor_equation;
    cout << "Factor Equation set to << " << BoolToString(factor_equation) << " >>\n";
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
  string string_settings = "" + BoolToChar(calc_vertex) + BoolToChar(calc_yintercept) + BoolToChar(print_table) + BoolToChar(calc_sumproduct) + BoolToChar(factor_equation) + to_string(table_boundaries[0]) + ',' + to_string(table_boundaries[1]);

  ofstream settings_file("quadratics_settings");
  if(settings_file.is_open()) {
    settings_file << string_settings;
  }
  settings_file.close();
}
void Table(double equation[3], bool print_table, int table_boundaries[2]) {
  cout << "   x             f(x)\n";
  for(int i = table_boundaries[0]; i <= table_boundaries[1]; i++) {
    cout << "   " << i << "          " << PlugIn(i, equation) << endl;
  }
}
void Display(double equation[3], double vertex[2], double solution[2],
             bool & has_solution, bool calc_vertex, bool calc_yintercept, bool print_table,
             bool calc_sumproduct, bool factor_equation, int table_boundaries[2]) {
	cout << endl << endl;
  if(calc_vertex) {
    CalculateVertex(equation, vertex);
  }
  if(calc_yintercept) {
    /// ok, it's calculated - now it needs to be stored!
    CalculateYIntercept(equation);
  }
  /// please comment the following lines
  cout << "Equation: ";
  if(equation[0] == 1)
	  cout << "x^2 ";
  else if(equation[0] != 0)
	  cout << equation[0] << "x^2 ";
  if(equation[1] > 0)
	  cout << "+ ";
  else if(equation[0] < 0)
	  cout << "- ";
  if(equation[1] == 1)
	  cout << "x ";
  else if(equation[1] != 0)
	  cout << equation[1] << "x ";
  if(equation[2] > 0)
	  cout << "+ ";
  else if(equation[2] < 0)
	  cout << "- ";
  if(equation[2] != 0)
       cout << equation[2];
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
    Factor(equation, vertex, solution, has_solution);
  }
  if(calc_vertex == 1) {
    cout << "Vertex: (" << vertex[0] << "," << vertex[1] << ")\n";
  }
  if(calc_yintercept == 1) {
    cout << "y-Intercept: (0," << equation[1] << ")\n";
  }
  if(print_table == 1) {
    Table(equation, print_table, table_boundaries);
  }
}
void Factor(double equation[3], double vertex[2], double solution[2],
            bool & has_solution) {
	cout << "Factored: ";
  if(solution[0] == solution[1] && has_solution) {
    if(equation[0] == 0) /* should this even happen? That's not a quadratic. */
    	cout << "0";
    else if(equation[0] != 1) {
      cout << equation[0];
    }
	if(equation[0] != 0) {
	  cout << "(x ";
	  if(solution[0] == 0)
		  cout << ")^2\n";
	  else if(solution[0] > 1)
		  cout << "- " << solution[0] << ")^2\n";
	  else
		  cout << "+ " << -solution[0] << ")^2\n";
    }
  } else {
    cout << equation[0] << "(x-" << solution[0] << ")(x-" << solution[1] <<
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
			for(int i = 5; i < (int)line.size(); i++) {
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

double PlugIn(double x, double equation[3]) {
  /* ax^2 + bx + c */
  return (equation[0] * pow(x, 2)) + (equation[1] * x) + (equation[2]);
}
