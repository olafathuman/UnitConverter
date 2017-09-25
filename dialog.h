#ifndef DIALOG_H
#define  DIALOG_H
#include "ui_dialog_ui.h"
#include <QDialog>

class Dialog:public QDialog,public Ui_Dialog{
    
    public:
        Dialog();
        void setDate(std::string date);


};

#endif
