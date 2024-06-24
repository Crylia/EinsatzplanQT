# include "LoginFrame.hpp"

LoginFrame::LoginFrame(QWidget* parent)
    :QFrame(parent) {
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
    header_m->setObjectName("Header");
    header_m->setStyleSheet(R"(
    #Header{
        color: #93F8FF;
        font-size: 36px;
        font-weight: bold;
        border: none;
    }
    )");
    header_m->show( );


    id_m = new QLineEdit(this);
    id_m->setPlaceholderText("ID...");
    id_m->setObjectName("ID");
    id_m->setFixedSize(300, 40);
    id_m->setStyleSheet(R"(
    #ID{
        color: #DADADA;
        font-size: 16px;
        background-color: #313131;
        border-radius: 10px;
        padding: 5px;
        border: 2px solid #414141;
    }
    )");
    id_m->show( );


    password_m = new QLineEdit(this);
    password_m->setPlaceholderText("Passwort...");
    password_m->setObjectName("Password");
    password_m->setEchoMode(QLineEdit::Password);
    password_m->setFixedSize(300, 40);
    password_m->setStyleSheet(R"(
    #Password{
        color: #DADADA;
        font-size: 16px;
        background-color: #313131;
        border-radius: 10px;
        padding: 5px;
        border: 2px solid #414141;
    }
    )");
    password_m->show( );

    loginButton_m = new QPushButton("Login", this);
    loginButton_m->setObjectName("loginButton");
    loginButton_m->setFixedSize(QSize(150, 50));
    loginButton_m->setStyleSheet(R"(
    #loginButton{
        color: #212121;
        font-size: 24px;
        font-weight: bold;
        background-color: #53EC87;
        border-radius: 10px;
    }
    #loginButton:pressed {
        background-color: #43DC77;
    }
    )");
    loginButton_m->show( );

    //create layout
    QVBoxLayout* layout = new QVBoxLayout( );

    //layout->setContentsMargins(50, 20, 50, 20);
    layout->addWidget(header_m, 3, Qt::AlignCenter);
    layout->addWidget(id_m, 1, Qt::AlignCenter);
    layout->addWidget(password_m, 1, Qt::AlignCenter);
    layout->addWidget(loginButton_m, 3, Qt::AlignCenter);

    //add Layout to LoginFrame
    setLayout(layout);

    //connect loginButton with function
    connect(loginButton_m, &QPushButton::clicked, this, &LoginFrame::loginButtonClicked);
}

//try Login if Button clicked
void LoginFrame::loginButtonClicked( ) {
    QString id = id_m->text( );
    QString password = password_m->text( );

    //check if Contents Valid
    if (id.isEmpty( ) || password.isEmpty( )) {
        QMessageBox::warning(this, "Error", "Bitte füllen Sie sowohl die ID als auch das Passwort aus.");
    } else {
        LoginFrameController* controller = new LoginFrameController( );
        if (!controller->tryLogin(id, password)) {
            QMessageBox::warning(this, "Error", "ID und Passwort stimmen nicht überein!");
        } else {
            ((QWidget*)(this->parent( )))->hide( );
            //TODO: Create new window
        }
    }
}

LoginFrame::~LoginFrame( ) {
    header_m->~QLabel( );
    id_m->~QLineEdit( );
    password_m->~QLineEdit( );
    loginButton_m->~QPushButton( );
    parent_m->~QMainWindow( );
}
