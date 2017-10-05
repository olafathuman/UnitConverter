#include "dialog.h"
#include <string>
#include <sstream>
#include <QString>

//In this file I implement the Dialog class.

//The constructor sets the Ui defined in ui_dialog_ui.h in a standard QDialog.
Dialog::Dialog(){
    setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint);
    setVisible(true);
}
//Function called if we have a file available. It changes the text on the label
//to tell the user when the data available is from.
void Dialog::setDate(std::string date){
    std::ostringstream st;

    st << "Current currency rate data is from " << date << ". Do you wish to fetch latest data? (Requires Internet Connection)";
    label->setText(QString::fromStdString(st.str()));


}
