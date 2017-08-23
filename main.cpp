#include <iostream>
#include "converter.h"
using namespace std;
int main(){
    Converter conv;
    cout << "### Welcome to the converter ###\n\n\n";
    cout << "Choose what to convert\n";
    cout << "1 - weight\n";
    cout << "0 - exit\n";
    int choice;
    float value;
    float result;
    cin >> choice;
    if(choice == 1){
        cout << "\n\n1 - Kg to Lbs\n";
        cout << "2 - Lbs to Kg\n";
        cin >> choice;
        cout << "Input value\n";
        cin >> value;
        if(choice ==1){
            result=conv.convertKg2Lb(value);
        }
        else{
            result=conv.convertLb2Kg(value);
        }
        cout << "Result: " << result << "\n";
    }
    return 0;
    
}
