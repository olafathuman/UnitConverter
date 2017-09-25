#include "dialog.h"
#include <string>
#include <sstream>
#include <QString>
Dialog::Dialog(){
    setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint);
    setVisible(true);
}

void Dialog::setDate(std::string date){
    std::ostringstream st;

    st << "Current currency rate data is from " << date << ". Do you wish to fetch latest data? (Requires Internet Connection)";
    label->setText(QString::fromStdString(st.str()));


}
