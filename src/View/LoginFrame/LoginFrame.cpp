# include "LoginFrame.hpp"

LoginFrame::LoginFrame(QWidget* parent)
:QFrame(parent)
{
    //configure LoginFrame
    setObjectName("LoginFrame");
    setStyleSheet(R"(
    #LoginFrame{
     background-color: #212121;
     border: none;
    }    
    )");
    setFrameStyle(QFrame::Box);

    
    //create QWidgets and add LoginFrame as parent
    header_m = new QLabel("Einsatzplan", this);
    header_m->setFrameStyle(QFrame::Box);
    header_m->setAlignment(Qt::AlignCenter);
    header_m->setObjectName("Header");
    header_m->setStyleSheet(R"(
    #Header{
        color: #93F8FF;
        font-size: 36px;
        font-weight: bold;
        border: none;
    }
    )");
    header_m->show();
    

    id_m = new QLineEdit( this);
    id_m->setPlaceholderText("ID...");
    id_m->setObjectName("ID");
    id_m->setStyleSheet(R"(
    #ID{
        color: #333333;
        font-size: 25px;
        font-weight: bold;
        background-color: #444444;
        border-radius: 10px;
        padding: 5px;
    }
    )");
    id_m->show();


    password_m = new QLineEdit(this);
    password_m->setPlaceholderText("Passwort...");
    password_m->setObjectName("Password");
    password_m->setStyleSheet(R"(
    #Password{
        color: #333333;
        font-size: 25px;
        font-weight: bold;
        background-color: #444444;
        border-radius: 10px;
        padding: 5px;
    }
    )");
    password_m->show();

    loginButton_m = new QPushButton("Login",this);
    loginButton_m->setObjectName("loginButton");
    loginButton_m->setStyleSheet(R"(
    #loginButton{
        color: #212121;
        font-size: 30px;
        font-weight: bold;
        background-color: #00C800;
        border-radius: 10px;
    }
    #loginButton:pressed {
        background-color: #00A800;
    }
    )");
    loginButton_m->show();

    
    //create layout
    QVBoxLayout*  layout = new QVBoxLayout();

    layout->setContentsMargins(50, 20, 50, 20);

    layout->addStretch(1);
    layout->addWidget(header_m);
    header_m->setAlignment(Qt::AlignHCenter);
    layout->addStretch(2);
    layout->addWidget(id_m);
    id_m->setAlignment(Qt::AlignHCenter);
    layout->addStretch(1);
    layout->addWidget(password_m);
    password_m->setAlignment(Qt::AlignHCenter);
    layout->addStretch(2);
    layout->addWidget(loginButton_m);
    layout->addStretch(1);

    //add Layout to LoginFrame
    setLayout(layout);

    //connect loginButton with function
    connect(loginButton_m, &QPushButton::clicked, this, &LoginFrame::loginButtonClicked);
}

    //try Login if Button clicked
void LoginFrame::loginButtonClicked(){
    QString id = id_m->text();
    QString password = password_m->text();

    //check if Contents Valid
    if (id.isEmpty() || password.isEmpty()){
        QMessageBox::warning(this, "Fehler", "Bitte füllen Sie sowohl die ID als auch das Passwort aus.");
    }
    else {
        LoginFrameController* controller = new LoginFrameController();
        bool valid = controller->tryLogin(id.toStdString(), password.toStdString());
    }

}