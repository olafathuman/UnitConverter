#include "currency.h"
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
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
    if (myfile.is_open(){
        getline(myfile,st);
        myfile.close();
        return st;
    }
    return "ERROR";
}

 vector<string> CurrencyHandler::listify(string str){
     string token;
     vector<std::string> ls;
    size_t pos;
    while ((pos = str.find(",")) !=  string::npos) {
        token = str.substr(0, pos);
        ls.push_back(token)
        s.erase(0, pos + delimiter.length());
    }
    return ls;
}
 vector<string> CurrencyHandler::cleanList(vector<string> ls){
     vector<string> result;
     vector<string>::iterator it;
     string::iterator strIt;
     ostringgstream aux;
    size_t pos;
    int i = 1;
    for(it=ls.begin()+1;it<ls.end();it++,i++){
       for(strIt=*it.begin();strIt<*it.end();strIt++){
           if(i==2){
                pos=*strIt.find(":");
                *strIt.erase(0,pos+":".length());
            }
            if(isalnum(*strIt) || *strIt==":"){
                aux << *strIt;
            }
       }
    result.push_back(aux.str());
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
    string::size_type = st;
    for(it=ls.begin();it<ls.end();it++,i++){
        pos=*it.find(":");
        start=*it.substr(0,pos);
        end=*it.erase(0,pos+":".length());
        if(i!=0){
            rate= stod(end,&sz);
            fromEurRates[start]=rate;
            toEurRates[start]=one/rate;
        }

    }
}

void CurrencyHandler::update(){
    string str= curler::get(url);
    vector<std::string> list;
    list = listify(str);
    fillMap(list); 
}


