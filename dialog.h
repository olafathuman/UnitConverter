#ifndef DIALOG_H
#define  DIALOG_H
#include "ui_dialog_ui.h"
#include <QDialog>

//Class definition for the dialog class.
class Dialog:public QDialog,public Ui_Dialog{
    
    public:
        Dialog();
        void setDate(std::string date);


};

#endif
