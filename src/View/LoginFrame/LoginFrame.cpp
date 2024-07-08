#include "LoginFrame.hpp"

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
	m_header = new QLabel("Einsatzplan", this);
	m_header->setFrameStyle(QFrame::Box);
	m_header->setObjectName("Header");
	m_header->setStyleSheet(R"(
    #Header{
      color: #93F8FF;
      font-size: 36px;
      font-weight: bold;
      border: none;
    }
  )");
	m_header->show( );

	m_id = new QLineEdit(this);
	m_id->setPlaceholderText("ID...");
	m_id->setObjectName("ID");
	m_id->setFixedSize(300, 40);
	m_id->setStyleSheet(R"(
    #ID{
      color: #DADADA;
      font-size: 16px;
      background-color: #313131;
      border-radius: 10px;
      padding: 5px;
      border: 2px solid #414141;
    }
  )");
	m_id->show( );

	m_password = new QLineEdit(this);
	m_password->setPlaceholderText("Passwort...");
	m_password->setObjectName("Password");
	m_password->setEchoMode(QLineEdit::Password);
	m_password->setFixedSize(300, 40);
	m_password->setStyleSheet(R"(
    #Password{
      color: #DADADA;
      font-size: 16px;
      background-color: #313131;
      border-radius: 10px;
      padding: 5px;
      border: 2px solid #414141;
    }
  )");
	m_password->show( );

	m_loginButton = new QPushButton("Login", this);
	m_loginButton->setObjectName("loginButton");
	m_loginButton->setFixedSize(QSize(150, 50));
	m_loginButton->setStyleSheet(R"(
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
	m_loginButton->show( );

	//create layout
	QVBoxLayout* layout = new QVBoxLayout( );

	//layout->setContentsMargins(50, 20, 50, 20);
	layout->addWidget(m_header, 3, Qt::AlignCenter);
	layout->addWidget(m_id, 1, Qt::AlignCenter);
	layout->addWidget(m_password, 1, Qt::AlignCenter);
	layout->addWidget(m_loginButton, 3, Qt::AlignCenter);

	//add Layout to LoginFrame
	setLayout(layout);

	//connect loginButton with function
	connect(m_loginButton, &QPushButton::clicked, this, &LoginFrame::loginButtonClicked);
}

//try Login if Button clicked
void LoginFrame::loginButtonClicked( ) {
	QString id = m_id->text( );
	QString password = m_password->text( );

	//check if Contents Valid
	if (id.isEmpty( ) || password.isEmpty( )) {
		QMessageBox::warning(this, "Error", "Bitte füllen Sie sowohl die ID als auch das Passwort aus.");
	} else {
		LoginFrameController* controller = new LoginFrameController( );
		int res = controller->tryLogin(id, password);
		if (res == -1) {
			QMessageBox::warning(this, "Error", "ID und Passwort stimmen nicht überein!");
		} else {
			((QWidget*)(this->parent( )))->hide( );
			EinsatzplanWindow* win = new EinsatzplanWindow(nullptr, id, res);
			win->show( );
			return;
		}
	}
}

LoginFrame::~LoginFrame( ) {
	m_header->~QLabel( );
	m_id->~QLineEdit( );
	m_password->~QLineEdit( );
	m_loginButton->~QPushButton( );
	m_parent->~QMainWindow( );
}
