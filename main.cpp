/// REMINDER: Function names should be command verbs (ie. PrintTable(), FindIntercepts())



/** COMMENTS ********************************************************/
/*	Your name: Stefan Kussmaul
	Class block: A			Date: 5/27/14
	Title: Everything Quadratics
*/

/** INCLUDE FILES ***************************************************/

#include <iostream>	//	input output commands:	cout & cin
#include <cmath> /// use cmath, not math.h
#include <fstream>
using namespace std;


/** FUNCTION PROTOTYPES**********************************************/
/* equation_standard[3], vertex[2], solution[2], has_solution is a bad name */
void InputEquation(double equation_standard[3], double vertex[2], double solution[2], bool & has_solution);
void Roots(double equation_standard[3], double vertex[2], double solution[2], bool & has_solution);
void Vertex(double equation_standard[3], double vertex[2], double solution[2], bool & has_solution);
void Options(bool & calc_vertex, bool & calc_yintercept, bool & print_table, bool & calc_sumproduct, bool & factor_equation, int table_boundaries[2]);
void Intercepts(double equation_standard[3], double vertex[2], double solution[2], bool & has_solution);
void Table(double equation_standard[3], double vertex[2], double solution[2], bool & has_solution, bool calc_vertex, bool calc_yintercept, bool print_table, bool calc_sumproduct, bool factor_equation, int table_boundaries[2]);
void Display(double equation_standard[3], double vertex[2], double solution[2], bool & has_solution, bool calc_vertex, bool calc_yintercept, bool print_table, bool calc_sumproduct, bool factor_equation, int table_boundaries[2]);
void Factor(double equation_standard[3], double vertex[2], double solution[2], bool & has_solution);
void LoadSettings(bool & calc_vertex, bool & calc_yintercept, bool & print_table, bool & calc_sumproduct, bool & factor_equation, int table_boundaries[2]);
/// the following function is obsolete:
//int StringToInt(string s);
string BoolToString(bool bool_to_convert);

/** MAIN FUNCTION ***************************************************/
int main() {
  bool calc_vertex = true, calc_yintercept = true, print_table = true, calc_sumproduct = true, factor_equation = true;
  int table_boundaries[2] = { -10, 10};
  double equation_standard[3], vertex[2], solution[2];
  bool has_solution;
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
  do {
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
      Roots(equation_standard, vertex, solution, has_solution);
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
void Roots(double equation_standard[3], double vertex[2], double solution[2],
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
void Vertex(double equation_standard[3], double vertex[2], double solution[2],
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
  LoadSettings(calc_vertex, calc_yintercept, print_table, calc_sumproduct,
               factor_equation, table_boundaries);
  cout << "\n\nSettings: \n";
  cout << "---------------------------------------------\n";
  string symbol = BoolToString(calc_vertex);
  cout << "1. Calculate Vertex......................." << symbol << endl;
  symbol = BoolToString(calc_yintercept);
  cout << "2. Calculate y-Intercept.................." << symbol << endl;
  symbol = BoolToString(print_table);
  symbol = BoolToString(calc_sumproduct);
  cout << "3. Calculate Sum and Product.............." << symbol << endl;
  symbol = BoolToString(factor_equation);
  cout << "4. Factor Equation........................" << symbol << endl;
  cout << "5. Print Table............................" << symbol << endl;
  cout << "6. Set Table equation_standard[3], vertex[2], solution[2], has_solution...................("
       << table_boundaries[0] << "," <<
       table_boundaries[1] << ")\n";
  cout << "7. Back to Main Menu\n";
  cout << "---------------------------------------------\n\n";
  cout << "Enter number of choice you would like to change: ";
  int choice;
  string string_settings = ""; /// why is this declared right here?
  cin >> choice;
  switch(choice) {
  case 1:
    calc_vertex = !calc_vertex;
    break;
  case 2:
    calc_yintercept = ! calc_yintercept;
    break;
  case 3:
    print_table = !print_table;
    break;
  case 4:
    calc_sumproduct = !calc_sumproduct;
    break;
  case 5:
    factor_equation = !factor_equation;
    break;
  case 6:
    /* this does nothing so that the thing after the switch case takes it but it doesn't activate the default case */
    break;
  default:
    /// it should give the user an error
    break;
  }
  /// some kind of string_settings stuff should be going on here
  if(choice ==
      7) {  /* choice = Set Table equation_standard[3], vertex[2], solution[2], has_solution */
    int bound;
    cout << "Enter lower bound: ";
    cin >> bound;
    table_boundaries[0] = bound;
    cout << "Enter upper bound: ";
    cin >> bound;
    table_boundaries[1] = bound;
  }
  ofstream settings_file("quadraticsolver_settings");
  if(settings_file.is_open()) {
    settings_file << string_settings;
  }
  settings_file.close();
}
void Table(double equation_standard[3], double vertex[2], double solution[2],
           bool & has_solution, bool calc_vertex, bool calc_yintercept, bool print_table,
           bool calc_sumproduct, bool factor_equation, int table_boundaries[2]) {
  cout << "print_table\n";
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
  if(calc_vertex == 1) {
    Vertex(equation_standard, vertex, solution, has_solution);
  }
  if(calc_yintercept == 1) {
    Intercepts(equation_standard, vertex, solution, has_solution);
  }
  cout << "Equation: " << equation_standard[0] << "x^2 + " << equation_standard[1]
       << "x + " <<
       equation_standard[2] << " = 0\n";
  if(!has_solution) {
    cout << "Equation has no solutions\n";
  } else {
    if(solution[0] == solution[1]) {
      cout << "Root is x= " << solution[0] << endl;
    } else {
      cout << "Roots are x = " << solution[0] << " and x = " << solution[1] <<
           endl;
    }
  }
  if(calc_sumproduct && !has_solution) {
    cout << "Sum of roots = " << solution[0] + solution[1] <<
         endl; // NOT SURE WHAT HAPPENS IF ONLY ONE SOLUTION
    cout << "Product of roots = " << solution[0] * solution[1] << endl;
  }
  if(factor_equation && !has_solution) {
    Factor(equation_standard, vertex, solution, has_solution);
  }
  if(calc_vertex == 1) {
    cout << "Vertex at point (" << vertex[0] << "," << vertex[1] << ")\n";
  }
  if(calc_yintercept == 1) {
    cout << "y-Intercept at point (0," << equation_standard[1] << ")\n";
  }
  if(print_table == 1) {
    Table(equation_standard, vertex, solution, has_solution, calc_vertex,
          calc_yintercept, print_table, calc_sumproduct, factor_equation,
          table_boundaries);
  }
}
void Factor(double equation_standard[3], double vertex[2], double solution[2],
            bool & has_solution) {
  if(solution[0] == solution[1]) {
    cout << equation_standard[0] << "(x-" << solution[0] << ")^2\n";
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
  /*
  string line;
  ifstream file_equation_standard[3], vertex[2], solution[2], has_solution("quadraticsolver_settings");
  if(file_equation_standard[3], vertex[2], solution[2], has_solution.is_open()) {
    while(getline(file_equation_standard[3], vertex[2], solution[2], has_solution, line)) {
      for(int i = 0; i < 5; i++) {
        settings[i] = (int)line[i] - 48;
      }
      string table_parameter = "";
      int stop_point;
      for(int j = 5; j < (int)line.size(); j++) {
        if(line[j] == ',') {
          stop_point = j;
          j = line.size(); // break loop
        } else {
          table_parameter = table_parameter + line[j];
        }
      }
      table_boundaries[0] = StringToInt(table_parameter);
      table_parameter = "";
      for(int k = stop_point; k < (int)line.size(); k++) {
        if(line[k] == ',') {
          k = line.size();  // break loop
        } else {
          table_parameter = table_parameter + line[k];
        }
      }
      table_boundaries[1] = StringToInt(table_parameter);
    }
    file_equation_standard[3], vertex[2], solution[2], has_solution.close();
  } else { // "stringmanipulator_equation_standard[3], vertex[2], solution[2], has_solution" does not exist - write a new file with default values
    ofstream file_equation_standard[3], vertex[2], solution[2], has_solution("quadraticsolver_settings");
    if(file_equation_standard[3], vertex[2], solution[2], has_solution.is_open()) {
      file_equation_standard[3], vertex[2], solution[2], has_solution << "11111-10,10";
      file_equation_standard[3], vertex[2], solution[2], has_solution.close();
    }
    calc_vertex = 1;
  }
  */
}
/// there is a function called atoi() that is built in and does this
/*
int StringToInt(string s) {
  int num;
  bool negative;
  for(int i = 0; i < (int)s.size(); i++) {
    if(s[i] == '-') {
      negative = 1;
    } else {
      num = num * 10 + (s[i] - '0');
    }
  }
  if(negative == 1) {
    return num * -1;
  }
  return num;
}
*/
