/*******************************************************************************
* main.cpp
*
* Description: The source file of "Everything Quadratics" which is a program to
* solve and manipulate user-inputted quadratic equations.
*
* By Stefan Kussmaul
*******************************************************************************/

/** INCLUDE FILES ***************************************************/

#include <iostream> //  input output commands:  cout & cin
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;


/** FUNCTION PROTOTYPES**********************************************/
/* gets equation from the user */
void InputEquation(double equation[3]);
/* finds the quadratic roots of the equation and puts them into solution[2] */
void CalculateRoots(double equation[3], double solution[2],
                    bool & has_solution);
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
double StringToDouble(string s);
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
bool LoadCurrentEquation(double equation[3]);
/* saves current equation to equation list */
void SaveEquation(string a, string b, string c);
/* removes chosen equation from equation list */
void RemoveEquation(double equation[3]);
/* displays equation list */
void LoadEquation(double equation[3], int equation_number);
/* read a chosen equation from file given parameters */
void ReadEquation(double equation[3], string file_name, bool load);
/* prints a properly formatted equation given a, b, and c values */
void PrintEquation(double equation[3]);
void FlipBool(bool &bool_to_flip);
void ClearScreen();


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
    LoadSettings(calc_vertex, calc_yintercept, print_table, calc_sumproduct,
                 factor_equation, table_boundaries);
//    LoadEquation(equation);
    cout << "\nAvailable Functions\n";
    cout << "---------------------------------\n";
    cout << "1. Options\n";
    cout << "2. Equation\n";
    cout << "3. Quit\n";
    cout << "---------------------------------\n";
    cout << "Enter choice: ";
    cin >> menu_input;
    do {
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
          cout << "Please enter a valid number between 1 and 3\n\n";
          break;
      }
    }
    while (menu_input != 1 && menu_input != 2 && menu_input != 3);
    cout << "\n\nHit enter to return to menu "; // not working
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
  	if (current_equation.is_open()) /* write values to file for future use */
  	{
  		current_equation << equation[0] << ',' << equation[1] << ',' << equation[2];
  		current_equation.close();
  	}
  	cout << "Save equation? (y/n) ";
  	cin >> choice;
//  	if(choice == 'y')
 // 		SaveEquation(equation);
}
void CalculateRoots(double equation[3], double solution[2],
                    bool & has_solution) {
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
  } while (choice > 7 || choice < 1);
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
  PrintEquation(equation);
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
string Factor(double equation[3], double solution[2]) {
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
void SaveEquation(double equations[3]){
	ofstream current_equation("quadratics_current");
	if(current_equation.is_open()) {

	}
}
/// what will this do?
void RemoveEquation(double equation[3]) {

}
void DisplayEquations(double equation[3]) {
	string line, a, b, c;
	int line_counter = 1, choice;
	ifstream equations("quadratics_equations");
	if(equations.is_open()) {
		while(getline(equations, line)) {
			ReadEquation(equation, "quadratics_equations", true);
			cout << line_counter << ". ";
//			PrintEquation(equation);
			line_counter++;
		}
		cout << "Choose equation: ";
		cin >> choice;
		LoadEquation(equation, choice);
	} else
		cout << "Error: No saved equations.\n";
}
void LoadEquation(double equation[3], int equation_number) {
	string line;
	int line_counter = 1, location_b, location_c;
	ifstream equations("quadratics_equations");
	if(equations.is_open()) {
		while (getline(equations, line)) {
			if(equation_number == line_counter) { /* found line corresponding to chosen equation */
				ReadEquation(equation, "quadratics_equations", true);
			}
			line_counter++;
		}
	}
}
void ReadEquation(double equation[3], string file_name, bool load) {
	/* file_name -> which file to read? load -> should values be loaded into equation[]? */
	string line, a, b, c;
	int location_b, location_c;
	ifstream current_equation(file_name.c_str());
	if(current_equation.is_open()) {
		location_b = line.find(','); /* find first comma */
		location_c = line.find(',', location_b + 1); /* find second comma */
		while (getline(current_equation, line)) {
			for(int i = 0; i < (int)line.size(); i++) { /* read in values for equation array */
				if(i < location_b)
					a = a + line[i];
				else if(i > location_b && i < location_c)
					b = b + line[i];
				else
					c + c + line[i];
			}
		}
		if(load) { /* "loads" values in to equation[] according to parameter */
			equation[0] = StringToDouble(a);
			equation[1] = StringToDouble(b);
			equation[2] = StringToDouble(c);
		}
		//return true; /* equation loaded successfully */
	}
	//return false; /* file not found; no equation to load */
}
double StringToDouble(string s)
{
	string decimal = "";
	int x, location;
	double num = 0.0, dec = 0.0;
	bool negative = 0;

		location = s.find('.');
		if(s[0] == '-') {
			negative = 1;
			for(x = 1; x < location; x++) {
				num = num * 10 + (s[x] - '0');
			}
		}
		else {
			for(x = 0; x < location; x++)
			{
				num = num * 10 + (s[x] - '0');
			}
		}
		for(x = location + 1; x < (int)s.size(); x++)
		{
			decimal = decimal + s[x];
		} for(x = decimal.size() - 1; x > -1; x--)
		{
			dec = dec * 0.1 + 0.1 * (decimal[x] - '0');
		}
		num = num + dec;
		if(negative == 1) {
			num = num * -1;
		}
		return num;
}
void PrintEquation(double equation[3]) {
  /* the output will be stored here */
  string equation_output;
  /* if the coefficient is 0, nothing happens */
  if (equation[0] != 0) {
    /* outputs the coefficient as long as it isn't 1 */
    if (equation[0] != 1) {
      equation_output += to_string(equation[0]);
    }
    equation_output += "x^2";
  }

  if (equation[1] != 0) {
    /* outputs the sign of the coefficient */
    equation_output += GetSign(equation[1]);
    if (equation[1] != 1) {
      equation_output += to_string(equation[1]);
    }
    equation_output += 'x';
  }
  if (equation[2] != 0) {
    equation_output += GetSign(equation[2]);
    if (equation[2] != 1) {
      equation_output += to_string(equation[2]);
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
