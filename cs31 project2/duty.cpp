#include <iostream>
using namespace std;

//determine the duty for a particular amount of cheese

int main ()
{
    string cheeseType;
    double value;
    string importer;
    
    
    cout << "Cheese type: ";
    getline(cin, cheeseType); //getting the line of input with cheese type
    
    cout << "Value: ";
    cin >> value; // getting the input
    cin.ignore(10000, '\n');
    
    cout << "Importer: ";
    getline(cin, importer); // getting the line of input with importer
    
    
    double amount = 0.0; // amount for the duty
    
    
    
    if (value <= 1000){ // if the value is less than 1000
        amount = 0.011*value; // 1.1% duty
    }
        
    
    if (value > 1000 && value <= 13000){ // if the value is between 1000 and 13,000
        if (cheeseType == "cheshire" || cheeseType == "stilton" ){
            amount = (0.011*1000) + ((value-1000)*0.014); // 1.1% for first 1000 and then 1.4% for remaining
        }
        
        else{
            amount = (0.011*1000) + ((value-1000)*0.02); // 1.1% for first 1000 and then 2% for remaining
        }
    }
    
    
 
    if (value > 13000){ // if the value is greater than 13,000
        if (cheeseType == "cheshire" || cheeseType == "stilton" ){ //accounts for different tax on these two types
            amount = (0.011*1000) + (12000*0.014) + ((value - 13000)*0.029); //1.1% for first 1000, 1.4% for next 12000, 2.9% for remaining
        }
        else{
            amount = (0.011*1000) + (12000*0.02) + ((value - 13000)*0.029); //1.1% for first 1000, 2% for neext 12000, 2.9% for remaining
        }
    }
    
    
    cout.setf(ios::fixed);
    cout.precision(2); // making sure the value only has two digits after the decimal
    
    cout << "---"<< endl; // accounting for the line with three dashes and a new line
    
    
    if (cheeseType == ""){ // lines accounting for input errors
        cout << "You must enter a cheese type" << endl;
    }
    else if (value <= 0){
        cout << "The value must be positive" << endl;
    }
    else if (importer == ""){
        cout << "You must enter an importer" << endl;
    }
    else { // line that prints for valid input
        cout << "The import duty for " << importer << " is $" << amount << endl;
    }
    
}
