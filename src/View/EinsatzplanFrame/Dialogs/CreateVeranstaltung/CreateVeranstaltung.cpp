#include "CreateVeranstaltung.hpp"

CreateVerDialog::CreateVerDialog(QWidget* parent)
	: QDialog(parent) {
	setWindowTitle("Veranstaltung Hinzufügen");
	setFixedSize(300, 400);
	setObjectName("createMemDialog");
	setStyleSheet(R"(
		#createMemDialog{
			background-color: #212121;
			border: none;
		}
	)");

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setContentsMargins(30, 30, 30, 30);

	m_name = new QLineEdit(this);
	m_name->setPlaceholderText("Veranstaltungskürzel");
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
	layout->addWidget(m_name, 1, Qt::AlignCenter);

	m_raum = new QLineEdit(this);
	m_raum->setPlaceholderText("Raum");
	m_raum->setFixedSize(220, 40);
	m_raum->setObjectName("raum");
	m_raum->setStyleSheet(R"(
		#raum{
			color: #DADADA;
			font-size: 16px;
			background-color: #313131;
			border-radius: 10px;
			padding: 5px;
			border: 2px solid #414141;
		}
	)");
	layout->addWidget(m_raum, 1, Qt::AlignCenter);

	m_campus = new QComboBox(this);
	m_campus->addItem("Campus A");
	m_campus->addItem("Campus B");
	m_campus->setFixedSize(220, 40);
	m_campus->setObjectName("campus");
	m_campus->setStyleSheet(R"(
		#campus{
			color: #DADADA;
			font-size: 16px;
			background-color: #313131;
			border-radius: 10px;
			padding: 5px;
		}
		#campus::Item{
			color: #DADADA;
			background-color: #313131;
		}
	)");
	layout->addWidget(m_campus, 1, Qt::AlignCenter);

	m_time = new QComboBox(this);
	m_time->addItem("2h");
	m_time->addItem("4h");
	m_time->setFixedSize(220, 40);
	m_time->setObjectName("time");
	m_time->setStyleSheet(R"(
		#time{
			color: #DADADA;
			font-size: 16px;
			background-color: #313131;
			border-radius: 10px;
			padding: 5px;
		}
		#time::Item{
			color: #DADADA;
			background-color: #313131;
		}
	)");
	layout->addWidget(m_time, 1, Qt::AlignCenter);

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

	layout->addLayout(buttonLayout, 1);

	connect(m_okButton, &QPushButton::clicked, this, &QDialog::accept);
	connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QString CreateVerDialog::getName( ) const {
	return m_name->text( );
}

QString CreateVerDialog::getRaum( ) const {
	return m_raum->text( );
}

QString CreateVerDialog::getCampus( ) const {
	return m_campus->currentText( );
}

QString CreateVerDialog::getTime( ) const {
	return m_time->currentText( );
}
