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
#include <iostream>
#include <algorithm>
using namespace std;
CurrencyHandler::CurrencyHandler(){
    path="CurrencyRates.txt";
    date="ERROR";
}

double CurrencyHandler::getToRate(string str){
    if(set){
        return toEurRates[str];
    }
    return 0; 
}

double CurrencyHandler::getFromRate(string str){
    if(set){
        return fromEurRates[str];
    }
    return 0;
}

 string CurrencyHandler::getDate(){
     string st;
     string error = "ERROR";
     cout << date << endl;
    cout << error << endl;
    if(date.compare(error)!=0){
        cout << "eh?" << endl;
        return date;
    }

    ifstream myfile(path);
    if (myfile.is_open()){
        getline(myfile,st);
        myfile.close();
        string semicolon=":";
        return st.erase(0,st.find(semicolon)+semicolon.length());
    }
    return "ERROR";
}

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
void CurrencyHandler::fillMap( vector<string> ls){
    string start;
    string end;
    double rate;
    double one=1;
    int i=0;
    vector<string>::iterator it;
    size_t pos;
    string::size_type st;
    string semicolon = ":";
    for(vector<string>::const_iterator it=ls.begin()+1;it<ls.end();it++,i++){
        
        string str =*it;
        
      if(i==0){
            cout << str;
            pos=str.find(semicolon);
            str=str.erase(0,pos+semicolon.length());
            str = str.substr(1,str.length()-2);
            setDate(str);
        }
        else{
            if(i==1){
                str=str.substr(9,str.length());
            }
            string test = start;
            pos=str.find(semicolon);
            start=str.substr(1,pos-2);

            end=str.erase(0,pos+semicolon.length());
            replace(end.begin(),end.end(),'.',',');
            rate= stod(end,&st);
            fromEurRates[start]=rate;
            toEurRates[start]=one/rate;
        }
    }    
    
}

void CurrencyHandler::update(){
    string str= Curler::getStuff();

    vector<string> list;
    list = listify(str);
    set=1; 
    fillMap(list);
}

QStandardItemModel* CurrencyHandler::getUnits(){
    QStandardItemModel* qsim = new QStandardItemModel();
    QString st;
    for(map<std::string,double>::iterator it = toEurRates.begin(); it!= toEurRates.end(); it++){
        st = QString::fromStdString(it->first);
        qsim->appendRow(new QStandardItem(st));
        if(it->first.compare("DKK")==0){
            qsim->appendRow(new QStandardItem("EUR"));
        }
    }
    return qsim;
}
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

void CurrencyHandler::setDate(string d){
    date=d;
}
