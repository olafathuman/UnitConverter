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
using namespace std;
CurrencyHandler::CurrencyHandler(){
    path="./CurrencyRates";
    url="http://api.fixer.io/latest";
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
    ifstream myfile(path);
    if (myfile.is_open()){
        getline(myfile,st);
        myfile.close();
        return st;
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
    for(vector<string>::const_iterator it=ls.begin();it<ls.end();it++,i++){
        string str =*it;
        string semicolon = ":";
        pos=str.find(semicolon);
        start=str.substr(0,pos);
        end=str.erase(0,pos+semicolon.length());
        if(i!=0){
            rate= stod(end,&st);
            fromEurRates[start]=rate;
            toEurRates[start]=one/rate;
        }

    }
}

void CurrencyHandler::update(){
    Curler Curl = Curler();
    string str= Curl.getStuff(url);

    vector<string> list;
    list = listify(str);
    fillMap(list); 
}

QStandardItemModel* CurrencyHandler::getUnits(){
    QStandardItemModel* qsim = new QStandardItemModel();
    qsim->appendRow(new QStandardItem("EUR"));
    QString st;
    for(map<std::string,double>::iterator it = toEurRates.begin(); it!= toEurRates.end(); it++){
        st = QString::fromStdString(it->first);
        qsim->appendRow(new QStandardItem(st));
    }
    return qsim;
}
