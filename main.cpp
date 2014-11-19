/*******************************************************************************
* main.cpp
*
* Description: The source file of "Everything Quadratics" which is a program to
* solve and manipulate user-inputted quadratic equations.
*
* By Stefan Kussmaul and Matthew Mcmullin
*******************************************************************************/

/** INCLUDE FILES ***************************************************/

#include <iostream> //  input output commands:  cout & cin
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;


/** FUNCTION PROTOTYPES**********************************************/
/* gets equation from the user */
void InputEquation(double equation[3]);
/* finds the quadratic roots of the equation and puts them into solution[2] */
void CalculateRoots(double equation[3], double solution[2],
                    bool & has_solution, bool print);
/* finds the vertex of the parabola */
void CalculateVertex(double equation[3], double vertex[2]);
/// description needed, also options needs to be a verb
void Options(bool & calc_vertex, bool & calc_yintercept, bool & print_table,
             bool & calc_sumproduct, bool & factor_equation, int table_boundaries[2]);
/* takes in an equation and returns its y intercept */
double CalculateYIntercept(double equation[3]);
/* outputs a table of values for the equation */
void Table(double equation[3], bool print_table, int table_boundaries[2]);
/// description needed
void Display(double equation[3], double vertex[2], double solution[2],
             bool & has_solution, bool calc_vertex, bool calc_yintercept, bool print_table,
             bool calc_sumproduct, bool factor_equation, int table_boundaries[2]);
/* returns factored equation */
string Factor(double equation[3], double solution[2]);
/// description needed - also, we need to decide on settings vs options
void LoadSettings(bool & calc_vertex, bool & calc_yintercept,
                  bool & print_table, bool & calc_sumproduct, bool & factor_equation,
                  int table_boundaries[2]);
/* returns the result of plugging int x into double equation[3] */
double PlugIn(double x, double equation[3]);
/* converts strings to doubles (used when loading the equation) */
/* the following are type conversion functions: */
string BoolToString(bool bool_to_convert);
/* converts characters to bools (used when loading settings) */
bool CharToBool(char c);
/* returns boolean's value as TRUE or FALSE */
char BoolToChar(bool b);
/* returns the sign of the double */
char GetSign(double input);
/* displays the status of the current options (true or false) */
void DisplayOptions(bool & calc_vertex, bool & calc_yintercept,
                    bool & print_table, bool & calc_sumproduct,
                    bool & factor_equation, int table_boundaries[2]);

/* loads most recently used equation */
void SaveEquation(double a, double b, double c);
/* removes chosen equation from "quadratics_equations" */
void RemoveEquationFromList(int line_number);
/* displays equation list */
void DisplayEquations(double equation[3]);
/* gets an equation from specified file */
bool GetEquationFromFile(string file_name, int line_number, bool load, double equation[3], bool print);
/* takes three doubles and puts them in a format that can be written to a file */
string EquationToString(double a, double b, double c);
/* prints a properly formatted equation given a, b, and c values */
void PrintEquation(double a, double b, double c);
void FlipBool(bool &bool_to_flip);
void ClearScreen();


/** MAIN FUNCTION ***************************************************/
int main() {
 /* set default values */
  bool calc_vertex = true, calc_yintercept = true, print_table = true,
       calc_sumproduct = true, factor_equation = true, equation_loaded = false;
  /* equation_loaded tells if there is currently an equation entered */
  int table_boundaries[2] = { -10, 10};
  double equation[3], vertex[2], solution[2];
  bool has_solution;
  cout << "Plain+Simple Quadratic Solver\n";
  cout << "        Press enter\n";
  cin.get();
  int menu_input;
  do {
	/* load settings from file */
    LoadSettings(calc_vertex, calc_yintercept, print_table, calc_sumproduct,
                 factor_equation, table_boundaries);
    /* attempt to load last equation used from "quadratics_current" file */
    equation_loaded = GetEquationFromFile("quadratics_current", 1, 1, equation, 0);
    if(equation_loaded) {
    	cout << "Current equation loaded: ";
    	PrintEquation(equation[0], equation[1], equation[2]);
    	cout << endl << endl;
    }
    else
    	cout << "No equation loaded\n\n";
    int line_counter = 1;
    cout << "\nAvailable Functions\n";
    cout << "---------------------------------\n";
    if(equation_loaded) {
    	/* only display if an equation is loaded and ready for use */
    	cout << line_counter << ". Solve Equation\n";
    	line_counter++;
    	cout << line_counter << ". Factor Equation\n"; /// I'm sure you can figure out a more efficient way to do this
    	line_counter++;
    	cout << line_counter << ". Analyze Equation\n";
    	line_counter++;
    }
    cout << line_counter << ".  Enter New Equation\n";
    line_counter++;
    cout << line_counter << ".  Choose From Equation List\n";
    line_counter++;
    cout << line_counter << ".  Options\n";
    line_counter++;
    cout << line_counter << ". Help\n";
    line_counter++;
    cout << line_counter << ". Quit\n";
    line_counter++;
    cout << "---------------------------------\n";
    cout << "Enter choice: ";
    cin >> menu_input;
    if(equation_loaded) {
    	/* menu when equation IS loaded */
    	do {
    		switch (menu_input) {
    		case 1:
    			CalculateRoots(equation, solution, has_solution, true);
          break;
    		case 2:
    			cout << Factor(equation, solution);
    			break;
    		case 3:
    			Display(equation, vertex, solution, has_solution, calc_vertex,
        	        calc_yintercept, print_table, calc_sumproduct, factor_equation,
        	        table_boundaries);
    			break;
    		case 4:
    			InputEquation(equation);
    			break;
    		case 5:
    			DisplayEquations(equation);
    			break;
    		case 6:
    			Options(calc_vertex, calc_yintercept, print_table, calc_sumproduct,
        	                factor_equation, table_boundaries);
    			break;
    		case 7:
    			cout << "This function has not been created yet\n\n";
    			break;
    		case 8:
    			exit(0);
    			break;
    		default:
    			cout << "Please enter a valid number between 1 and 8\n\n";
    			break;
    		}
    }while (menu_input < 1 || menu_input > 8);
    }
    else {
    	/* menu when equation IS NOT loaded */			/// there's a better way to do this
    	do{
    		switch(menu_input) {
    		case 1:
    		 	InputEquation(equation);
    		    break;
    		case 2:
    		    DisplayEquations(equation);
    		    break;
    		case 3:
    		    Options(calc_vertex, calc_yintercept, print_table, calc_sumproduct,
    		         factor_equation, table_boundaries);
    		    break;
    		case 4:
    		    cout << "This function has not been created yet\n\n";
    		    break;
    		case 5:
    			exit(0);
    		    break;
    		default:
    			cout << "Please enter a valid number between 1 and 5\n\n";
    		    break;
    		}
    	}while(menu_input < 1 || menu_input > 5);
    }
    cout << "\n\nHit enter to return to menu "; /// want this to make the program wait until user hits enter
    /// what isn't working? In what way?
    /// this happens when we use a combination of cin, getline, and other stuff. We will have to figure out one to use to standardize everything
    cin.get();
    cin.get(); /* has to be repeated once */
  }
  while (menu_input != 3);
  return 0;
}

/** FUNCTIONS *******************************************************/
void InputEquation(double equation[3]) {
	char choice;
  cout << "Equation will be entered in the form ax^2 + bx + c = 0\n\n";
  for (int i = 0; i < 3; i++) {
    /* 97 is the ascii character a, so this goes from a to c in the loop */
    cout << "Enter << " << char(i + 97) << " >> term: ";
    cin >> equation[i];
  }
  ofstream current_equation ("quadratics_current");
  	if (current_equation.is_open()) /* write values to file for future use */ {
  		current_equation << EquationToString(equation[0], equation[1], equation[2]); /* write equation to file */
  		current_equation.close();
  	}
  	cout << "Save equation? (y/n) ";
  	cin >> choice;
  	if(choice == 'y')
  		SaveEquation(equation[0], equation[1], equation[2]);
}
void CalculateRoots(double equation[3], double solution[2],
                    bool & has_solution, bool print) {
  /* b^2 - 4ac */
  int discriminant = pow(equation[1], 2) - (4 * equation[0] * equation[2]);
  if (discriminant < 0) {
    has_solution = false;
  }
  else {
    has_solution = true;
    /* -b + root b^2 - 4ac / 2a */
    solution[0] = (-equation[1] + sqrt(discriminant)) / (2 * equation[0]);
    /* -b - root b^2 - 4ac / 2a */
    solution[1] = (-equation[1] - sqrt(discriminant)) / (2 * equation[0]);
  }
  if(print) {
	  if (!has_solution) {
	    cout << "Equation has no solutions\n";
	  }
	  else {
	    if (solution[0] == solution[1]) {
	      cout << "Root(s): (0," << solution[1] << ")";
	    }
	    if (solution[0] != solution[1]) {
	      cout << " and (0," << solution[1] << ")";
	    }
	    cout << endl;
	  }
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
             bool & calc_sumproduct, bool & factor_equation,
             int table_boundaries[2]) {
  LoadSettings(calc_vertex, calc_yintercept, print_table, calc_sumproduct,
               factor_equation, table_boundaries);
  DisplayOptions(calc_vertex, calc_yintercept, print_table, calc_sumproduct,
                 factor_equation, table_boundaries);
  cout << "Enter number of choice you would like to change: ";
  int choice;
  do{
    cin >> choice;
    switch (choice) {
      case 1:
        calc_vertex = !calc_vertex;
        cout << "Calculate Vertex set to << " << BoolToString(calc_vertex) << " >>\n";
        break;
      case 2:
        calc_yintercept = ! calc_yintercept;
        cout << "Calculate y-Intercept set to << " << BoolToString(
               calc_yintercept) << " >>\n";
        break;
      case 3:
        print_table = !print_table;
        cout << "Print Table set to << " << BoolToString(print_table) << " >>\n";
        break;
      case 4:
        calc_sumproduct = !calc_sumproduct;
        cout << "Calculate Sum and Product set to << " << BoolToString(
               calc_sumproduct) << " >>\n";
        break;
      case 5:
        factor_equation = !factor_equation;
        cout << "Factor Equation set to << " << BoolToString(factor_equation) <<
             " >>\n";
        break;
      case 6:
        cout << "Enter lower bound: ";
        cin >> table_boundaries[0];
        cout << "Enter upper bound: ";
        cin >> table_boundaries[1];
        cout << "New bounds set to (" << table_boundaries[0] << "," <<
             table_boundaries[1] << ")\n";
        break;
      case 7:
        break; /* this does nothing so that the thing after the switch case takes it but it doesn't activate the default case */
      default:
        cout << "\nPlease enter a choice between 1 and 7:\n";
        break;
    }
  } while (choice < 1 || choice > 7);
  string string_settings = "" + BoolToChar(calc_vertex) + BoolToChar(
                             calc_yintercept) + BoolToChar(print_table) + BoolToChar(
                             calc_sumproduct) + BoolToChar(factor_equation) + to_string(
                             table_boundaries[0]) + ',' + to_string(table_boundaries[1]);
  ofstream settings_file("quadratics_settings");
  if (settings_file.is_open()) {
    settings_file << string_settings;
  }
  settings_file.close();
}
void Table(double equation[3], bool print_table, int table_boundaries[2]) { /// needs to be formatted
  cout << "   x             f(x)\n";
  for (int i = table_boundaries[0]; i <= table_boundaries[1]; i++) {
    cout << "   " << i << "          " << PlugIn(i, equation) << endl;
  }
}
void Display(double equation[3], double vertex[2], double solution[2],
             bool & has_solution, bool calc_vertex, bool calc_yintercept, bool print_table,
             bool calc_sumproduct, bool factor_equation, int table_boundaries[2]) {

  cout << endl << endl;
  if (calc_vertex) {
    CalculateVertex(equation, vertex);
  }
  if (calc_yintercept) {
    /// ok, it's calculated - now it needs to be stored!
    CalculateYIntercept(equation);
  }
  cout << "Equation: ";
  PrintEquation(equation[0], equation[1], equation[2]);
  CalculateRoots(equation, solution, has_solution, true);
  if (calc_sumproduct) {
    cout << "Sum of roots = " << solution[0] + solution[1] <<
         endl;
    cout << "Product of roots = " << solution[0] * solution[1] << endl;
  }
  if (factor_equation) {
    string f = Factor(equation, solution);
    cout << f;
  }
  if (calc_vertex == 1) {
    cout << "Vertex: (" << vertex[0] << "," << vertex[1] << ")\n";
  }
  if (calc_yintercept == 1) {
    cout << "y-Intercept: (0," << equation[1] << ")\n";
  }
  if (print_table == 1) {
    Table(equation, print_table, table_boundaries);
  }
}
string Factor(double equation[3], double solution[2]) { /// why does this return a string?
														/// why not just void, and print it directly?
  /* plug in 1 */
  double equation_factor = PlugIn(1, equation) /
                    ((1 - solution[0]) * (1 - solution[1]));
  if (solution[0] != solution[1]) {
    return to_string(equation_factor) +
           "(x" + GetSign(solution[0]) + to_string(solution[0]) + ")" +
           "(x" + GetSign(solution[1]) + to_string(solution[1]) + ")";
  } else {
    return to_string(equation_factor) +
           "(x" + GetSign(solution[0]) + to_string(solution[0]) + ")^2";
  }
}
string BoolToString(bool bool_to_convert) {
  if (bool_to_convert == true) {
    return "TRUE";
  }
  else {
    return "FALSE";
  }
}
/// this should probably be a bool to return a success or failure of load
void LoadSettings(bool & calc_vertex,
                  bool & calc_yintercept,
                  bool & print_table,
                  bool & calc_sumproduct,
                  bool & factor_equation,
                  int table_boundaries[2]) {
  string line, table_lower_bound = "", table_upper_bound = "";
  bool comma_reached = 0;
  ifstream settings_file("quadratics_settings");
  if (settings_file.is_open()) {
    while (getline(settings_file, line)) {
      calc_vertex = CharToBool(line[0]);
      calc_yintercept = CharToBool(line[1]);
      print_table = CharToBool(line[2]);
      calc_sumproduct = CharToBool(line[3]);
      factor_equation = CharToBool(line[4]);
      for (int i = 5; i < (int)line.size(); i++) {
        if (line[i] == ',') {
          comma_reached = 1;
        }
        else if (!(comma_reached))
          /* build table_boundaries[0] */
        {
          table_lower_bound = table_lower_bound + line[i];
        }
        else if (comma_reached)
          /* build table_boundaries[1] */
        {
          table_upper_bound = table_upper_bound + line[i];
        }
      }
      table_boundaries[0] = atoi(table_lower_bound.c_str());
      table_boundaries[1] = atoi(table_upper_bound.c_str());
    }
    settings_file.close();
    /* set default values and write "quadratics_settings" with default values */
  }
  else {
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
  if (c == '0') {
    return false;
  }
  else {
    return true;
  }
}
char BoolToChar(bool b) {
  if (b == 0) {
    return '0';
  }
  else {
    return '1';
  }
}

double PlugIn(double x, double equation[3]) {
  /* ax^2 + bx + c */
  return (equation[0] * pow(x, 2)) + (equation[1] * x) + (equation[2]);
}

char GetSign(double input) {
  if (input >= 0) {
    return '+';
  } else {
    return '-';
  }
}

void DisplayOptions(bool & calc_vertex, bool & calc_yintercept, bool & print_table,
             bool & calc_sumproduct, bool & factor_equation, int table_boundaries[2]) {
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
       << table_boundaries[0] << "," << table_boundaries[1] << ")\n"
       << "\n7. Back to Main Menu\n"
       << "---------------------------------------------\n\n";
}
/* saves equation to "quadratics_equations" */
void SaveEquation(double a, double b, double c) {
	string line, string_equation;
	vector<string> equations;
	ifstream file("quadratics_equations"); /* access file */
	if(file.is_open()) {
		while(getline(file, line)) {
			/* copy in line by line to vector */
			equations.push_back(line);
		}
	}
	ofstream new_file("quadratics_equations"); /* access file again in ofstream */
	if(new_file.is_open()) {
		/* overwrite with original equations */
		for(int i = 0; i < (int)equations.size(); i++)
			new_file << equations[i];
		/* add newest equation to file */
		new_file << EquationToString(a, b, c);
		new_file.close();
	}
}
/* Removes chosen equation from "quadratics_equations" */
void RemoveEquationFromList(int line_number) {
	string line;
	int line_counter = 1;
	vector<string> equations;
	ifstream file("quadratics_equations");
	if(file.is_open()) {
		while(getline(file, line)) {
			if(line_counter != line_number)
				equations.push_back(line); /* copy all equations except chosen one
											* to vector */
			line_counter++;
		}
	}
	ofstream write_file("quadratics_equations");
	if(write_file.is_open()) {
		for(int i = 0; i < (int)equations.size(); i++) {
			write_file << equations[i]; /* write equations back into file */
		}
		write_file.close();
	}
}
/* Displays equations stored in "quadratics_equations"
 * User can choose to load an equation into equations[] for use in program,
 * or can delete an equation from the file */
void DisplayEquations(double equation[3]) {
	string line, a, b, c;
	int line_counter = 1, choice, remove;
	ifstream equations("quadratics_equations");
	if(equations.is_open()) {
		while(getline(equations, line)) {
			GetEquationFromFile("quadratics_equations", line_counter, 0, equation, 1);
			cout << line_counter << ". ";
//			PrintEquation(equation);
			line_counter++;
		}
		cout << line_counter << ". " << "Delete equation\n";
		cout << "Enter choice: ";
		cin >> choice;
		if(choice == line_counter) { /* choice is to delete an equation */
			cout << "Enter number of equation to remove: ";
			cin >> remove;
			do {
				if(remove < 1 || remove > line_counter - 1) {
					cout << "Error: Invalid choice. Please try again: ";
					cin >> remove;
				}
			}while(remove < 1 || remove > line_counter -1);
			RemoveEquationFromList(remove);
		}
		else
			GetEquationFromFile("quadratics_equations", choice, 1, equation, 0);
	} else
		cout << "Error: No saved equations.\n";
}
/* Reads "file_name" and finds specified line number. If load = true, this
   function will load information from the line into equations[] for use by the
   user. If print = true, the equation will be printed. */
   /// did you mean equation[] or something else? equations[] doesn't exist
bool GetEquationFromFile(string file_name, int line_number, bool load, double equation[3], bool print) {
	string line, a, b, c;
	int line_counter = 1;
	bool file_exists = false;
	ifstream current_equation(file_name.c_str());
	if(current_equation.is_open()) {
		file_exists = true;
		while (getline(current_equation, line)) {
			if(line_counter == line_number) {
				int first_comma = line.find(','); /* find first comma */
				int second_comma = line.find_last_of(','); /* find second comma */
				/* REMINDER: line.substr() takes in the size of the substring, NOT the
				             ending point as the second parameter (yes, that sucks) */
				a = line.substr(0, first_comma);
				b = line.substr(first_comma + 1, second_comma - first_comma);
				/* c starts at the second comma, and the size of c is the size of the
				   whole line minus the size of a, b, and the 2 commas */
        c = line.substr(second_comma + 1,
                        line.size()  - (a.size() + b.size() + 2));
			}
			line_counter++;
		if(load) { /* "loads" values in to equation[] according to parameter */
			equation[0] = atof(a.c_str());
			equation[1] = atof(b.c_str());
			equation[2] = atof(c.c_str());
		}
		if(print)
			PrintEquation(equation[0], equation[1], equation[2]);
		}
	}
	return file_exists;
}

/* converts numerical values of equation into string form.
* This will be used to write our equations to files */
string EquationToString(double a, double b, double c) {
	string equation = to_string(a) + ',' + to_string(b) + ',' + to_string(c);
	return equation;
}
/* Prints equation with proper formatting */
void PrintEquation(double a, double b, double c) {
  /* the output will be stored here */
  string equation_output;
  /* if the coefficient is 0, nothing happens */
  if (a != 0) {
    /* outputs the coefficient as long as it isn't 1 */
    if (a != 1) {
      equation_output += to_string(a);
    }
    equation_output += "x^2";
  }

  if (b != 0) {
    /* outputs the sign of the coefficient */
    equation_output += GetSign(b);
    if (b != 1) {
      equation_output += to_string(b);
    }
    equation_output += 'x';
  }
  if (c != 0) {
    equation_output += GetSign(c);
    if (c != 1) {
      equation_output += to_string(c);
    }
  }
  equation_output += "=0";
  cout << equation_output << endl;
}
void FlipBool(bool &bool_to_flip) {
	bool_to_flip = !bool_to_flip;
}
void ClearScreen() {
  cout << "\x1b[2J\x1b[H" << flush;
}
