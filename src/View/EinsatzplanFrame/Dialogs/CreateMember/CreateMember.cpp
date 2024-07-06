#include "CreateMember.hpp"

CreateMemDialog::CreateMemDialog(QWidget* parent)
	:QDialog(parent) {
	setWindowTitle("Mitarbeiter Hinzufügen");
	setFixedSize(300, 400);
	setObjectName("CreateMemDialog");
	setStyleSheet(R"(
		#CreateMemDialog{
			background-color: #212121;
			border: none;
		}
	)");

	m_name = new QLineEdit(this);
	m_name->setPlaceholderText("Name");
	m_name->setFixedSize(220, 40);
	m_name->setObjectName("name");
	m_name->setStyleSheet(R"(
		#name{
			color: #DADADA;
			font-size: 16px;
			background-color: #313131;
			border-radius: 10px;
			padding: 5px;
			border: 2px solid #414141;
		}
	)");
	m_name->show( );


	m_email = new QLineEdit(this);
	m_email->setPlaceholderText("Email");
	m_email->setFixedSize(220, 40);
	m_email->setObjectName("email");
	m_email->setStyleSheet(R"(
		#email{
			color: #DADADA;
			font-size: 16px;
			background-color: #313131;
			border-radius: 10px;
			padding: 5px;
			border: 2px solid #414141;
		}
	)");
	m_email->show( );

	m_password = new QLineEdit(this);
	m_password->setPlaceholderText("Passwort");
	m_password->setEchoMode(QLineEdit::Password);
	m_password->setFixedSize(220, 40);
	m_password->setObjectName("password");
	m_password->setStyleSheet(R"(
		#password{
			color: #DADADA;
			font-size: 16px;
			background-color: #313131;
			border-radius: 10px;
			padding: 5px;
			border: 2px solid #414141;
		}
	)");
	m_password->show( );

	m_admin = new QCheckBox("Admin", this);
	m_admin->setFixedSize(220, 40);
	m_admin->setObjectName("admin");
	m_admin->setStyleSheet(R"(
		#admin{
			color: #DADADA;
			font-size: 20px;
			border: none;
		}
	)");
	m_admin->show( );

	QVBoxLayout* layout = new QVBoxLayout(this);

	layout->setContentsMargins(30, 30, 30, 30);

	layout->addWidget(m_name, 1, Qt::AlignCenter);
	layout->addWidget(m_email, 1, Qt::AlignCenter);
	layout->addWidget(m_password, 1, Qt::AlignCenter);
	layout->addWidget(m_admin, 1, Qt::AlignCenter);

	QHBoxLayout* buttonLayout = new QHBoxLayout( );

	m_okButton = new QPushButton("OK", this);
	m_okButton->setFixedSize(110, 40);
	m_okButton->setObjectName("okButton");
	m_okButton->setStyleSheet(R"(
		#okButton{
			color: #212121;
			font-size: 16px;
			font-weight: bold;
			background-color: #53EC87;
			border-radius: 10px;
		}
	)");

	m_cancelButton = new QPushButton("Abbrechen", this);
	m_cancelButton->setFixedSize(110, 40);
	m_cancelButton->setObjectName("cancelButton");
	m_cancelButton->setStyleSheet(R"(
		#cancelButton{
			color: #212121;
			font-size: 16px;
			font-weight: bold;
			background-color: #FF5555;
			border-radius: 10px;
		}
	)");

	buttonLayout->addWidget(m_okButton, 1, Qt::AlignCenter);
	buttonLayout->addWidget(m_cancelButton, 1, Qt::AlignCenter);

	layout->addLayout(buttonLayout);

	connect(m_okButton, &QPushButton::clicked, this, &QDialog::accept);
	connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QString	CreateMemDialog::getName( ) const {
	return m_name->text( );
}

QString CreateMemDialog::getEmail( ) const {
	return m_email->text( );
}

QString CreateMemDialog::getPassword( ) const {
	return m_password->text( );
}

bool CreateMemDialog::isAdmin( ) const {
	return m_admin->isChecked( );
}
