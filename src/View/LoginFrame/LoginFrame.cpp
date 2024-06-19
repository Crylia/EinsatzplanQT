# include "LoginFrame.hpp"

LoginFrame::LoginFrame(QWidget* parent)
:QFrame(parent)
{
    header_m = new QLabel("Login", this);
    header_m->setFrameStyle(QFrame::Box);
    header_m->setGeometry(100,100,200,50);
    header_m->show();
    
    id_m = new QLineEdit("ID...", this);
    id_m->setGeometry(100,200,200,50);
    id_m->show();

    password_m = new QLineEdit("Passwort...",this);
    password_m->setGeometry(100,300,200,50);
    password_m->show();

    loginButton_m = new QPushButton("Login",this);
    loginButton_m->setGeometry(100,400,200,50);
    loginButton_m->show();

    setFrameStyle(QFrame::Box | QFrame::Plain);
    setLineWidth(5);
    
}