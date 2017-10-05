#include "currency.h"
#include "curler.h"
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QString>
//In this file, I implement the CurrencyHandler class.

using namespace std;

//In the consturrctor, i set the standard path as well as the current date as
//"ERROR".
CurrencyHandler::CurrencyHandler(){
    sPath="CurrentRates.txt";
    date="ERROR";
}

//This function returns the rate from str to Euros. This value is obtained from 
//the toEurRates map.
double CurrencyHandler::getToRate(string str){
    if(set){
        return toEurRates[str];
    }
    return 0; 
}

//Same as the function above, but instead gets the rate from Eur to str. This
//rate is stored in the fromEurRates map.
double CurrencyHandler::getFromRate(string str){
    if(set){
        return fromEurRates[str];
    }
    return 0;
}

//Function that returns the date.
 string CurrencyHandler::getDate(){
    return date;
}

//Function that returns the date in the first line of the path file, or "ERROR"
//if the file doesn't exist/fails to open.
 string CurrencyHandler::getDateFromFile(string path){
    ifstream myfile;
    myfile.open(path);
    string st;
    if(myfile.is_open()){
        getline(myfile,st);
        myfile.close();
        return st.erase(0,5);
    }
    return "ERROR";
}
//Function that takes the raw currency data, in the form of a string, and converts into a usable vector.
 vector<string> CurrencyHandler::listify(string str){
     string token;
     vector<std::string> ls;
     string delimiter = ",";
    size_t pos;
    while ((pos = str.find(delimiter)) !=  string::npos) {
        
        token = str.substr(0, pos);
        
        ls.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    return ls;
}
//Function that was meant to remove all the un-needed characters from the list.
//I ended up impementing this part in the fillMap function, so tihs function
//isn't even used in the code anymore. Never produced the desired effects 
//either...
 vector<string> CurrencyHandler::cleanList(vector<string> ls){
    vector<string> result;
    vector<string>::const_iterator it;
    string::iterator strIt;
    ostringstream *aux =new ostringstream();
    size_t pos;
    int i = 1;
    for(it=ls.begin()+1;it<ls.end();it++,i++){
        string str=(string)*it;
        if(i==2){
            pos=str.find(":");
            str.erase(0,pos+string(":").length());
        }
       for(strIt=str.begin();strIt<str.end();strIt++){
          
            if(isalnum(*strIt) || *strIt==':'){
                *aux << *strIt;

            }
       }
    result.push_back(aux->str());
    aux = new  ostringstream(); 
    }
    return result;
}
//Function that populates the maps given the vector of strings as well as set
//the date of the data.
void CurrencyHandler::fillMap( vector<string> ls){
    string start;
    string end;
    double rate;
    double one=1;
    QString  qstr;
    int i=0;
    vector<string>::iterator it;
    size_t pos;
    string semicolon = ":";

    for(vector<string>::const_iterator it=ls.begin()+1;it<ls.end();it++,i++){
        
        string str =*it;
    //first line is always data, needs to be handled differently. 
      if(i==0){
            pos=str.find(semicolon);
            str=str.erase(0,pos+semicolon.length());
            str = str.substr(1,str.length()-2);
            setDate(str);
        }
        else{
        //All others require the seperation of the unit from the rate, as well
        //as removal of characters such as " and ,.
            if(i==1){
                str=str.substr(9,str.length());
            }
            string test = start;
            pos=str.find(semicolon);
            start=str.substr(1,pos-2);

            end=str.erase(0,pos+semicolon.length());
            qstr = QString::fromStdString(end);
            rate= qstr.toDouble();
            fromEurRates[start]=rate;
            toEurRates[start]=one/rate;
        }
    }    
    
}
//Function that handles all the necessary steps to populating the maps with 
//currency data, as well as setting the set flag to 1 to indicatethat the 
//currency data has indeed been set. Does not check for errors though, not yet
//anyway. If you don't actually have an internet connection to obtain the data,
//it'll return an empty list causing the interface to have a "Currency" tab but
//no units to pick from.
//
void CurrencyHandler::update(){
   
    //1st step, obtain data from the internet with Curl.
    string str= Curler::getStuff();

    //2nd step, turn the string of data into a usable list (vector)
    vector<string> list;
    list = listify(str);

    //Lastly, set the state to "set" and fill the maps with the appropriate 
    //rates.
    set=1; 
    fillMap(list);

}
//Function that returns all units in the toEurRates map. Both maps have the
//same units of currency, so either one could be used here. This is required to
//populate the QT interface.
QStandardItemModel* CurrencyHandler::getUnits(){
    QStandardItemModel* qsim = new QStandardItemModel();
    QString st;
    for(map<std::string,double>::iterator it = toEurRates.begin(); it!= toEurRates.end(); it++){
        st = QString::fromStdString(it->first);
        qsim->appendRow(new QStandardItem(st));
        //Slight "hack". Since i'm not sorting the list, I require to add the
        //"EUR" unit that isn't present in the original data string (because
        //the string contain rates from X unit to Euros) at the correct moment.
        //This way it will be alphabetically ordered (until new units of 
        //currency are added to api.fixer.io/latest)
        if(it->first.compare("DKK")==0){
            qsim->appendRow(new QStandardItem("EUR"));
        }
    }
    return qsim;
}

//Function that writes the currency data in this class to a file for future use.
void CurrencyHandler::writeToFile(string path){
    ofstream myfile;
    myfile.open(path);
    if(myfile.is_open()){
        myfile << "Date:" << getDate() << endl;
        for(map<std::string,double>::iterator it= fromEurRates.begin(); it!= fromEurRates.end();it++){
            myfile << it->first << ":" << fromEurRates[it->first] << endl;
        }
        myfile.close();
    } 
}
//Function that reads currency data in path.
void CurrencyHandler::readFromFile(string path){
    ifstream myfile;
    myfile.open(path);
    size_t pos;
    string str;
    QString qstr;
    string unit;
    double value;
    double one = 1;
    string delimiter = ":";
    if (myfile.is_open()){
        //first line is always date if all went according to specifications.
        getline(myfile,str);
        pos = str.find(delimiter);
        str=str.erase(0,pos);
        setDate(str);
        set=1;
        while(getline(myfile,str)){
            pos = str.find(delimiter);
            unit=str.substr(0,pos);
            str=str.erase(0,pos+1);
            qstr = QString::fromStdString(str);
            value=qstr.toDouble();
            fromEurRates[unit]=value;
            toEurRates[unit]=one/value;



        }
    }
}
//function that sets date to d.
void CurrencyHandler::setDate(string d){
    date=d;
}
