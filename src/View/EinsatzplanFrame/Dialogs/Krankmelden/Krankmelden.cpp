#include "Krankmelden.hpp"

Krankmelden::Krankmelden(const QString& mitarbeiterName, QWidget* parent) :
	QDialog(parent),
	m_text(new QLabel(QString::fromStdString(mitarbeiterName.toStdString( ) + " krankmelden?"))) {
	setWindowTitle("Mitarbeiter Krankmelden?");
	setFixedSize(350, 150);
	setObjectName("Krankmelden");
	setStyleSheet(R"(
		#Krankmelden{
			background-color: #212121;
			border: none;
		}
	)");

	m_accept = new QPushButton("Ja", this);
	m_accept->setFixedSize(110, 40);
	m_accept->setObjectName("acceptButton");
	m_accept->setStyleSheet(R"(
		#acceptButton{
			color: #212121;
			font-size: 16px;
			font-weight: bold;
			background-color: #A5D6A7;
			border-radius: 10px;
		}
	)");
	m_decline = new QPushButton("Nein", this);
	m_decline->setFixedSize(110, 40);
	m_decline->setObjectName("declineButton");
	m_decline->setStyleSheet(R"(
		#declineButton{
			color: #212121;
			font-size: 16px;
			font-weight: bold;
			background-color: #EF9A9A;
			border-radius: 10px;
		}
	)");

	m_text->setObjectName("mitarbeiterName");
	m_text->setStyleSheet(R"(
		#mitarbeiterName{
			background-color: none;
			border:none;
			color: #D8D8D8;
			font-size:18px;
		}
	)");

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(m_text, 0, Qt::AlignCenter);

	QHBoxLayout* layout = new QHBoxLayout( );
	mainLayout->addLayout(layout, 1);

	layout->addWidget(m_accept, 1, Qt::AlignCenter);
	layout->addWidget(m_decline, 1, Qt::AlignCenter);

	connect(m_accept, &QPushButton::clicked, this, &QDialog::accept);
	connect(m_decline, &QPushButton::clicked, this, &QDialog::reject);
}
