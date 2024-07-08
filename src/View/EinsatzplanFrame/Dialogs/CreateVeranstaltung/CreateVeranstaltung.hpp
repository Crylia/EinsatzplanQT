#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>

class CreateVerDialog : public QDialog {
	Q_OBJECT
protected:
	QLineEdit* m_name;
	QLineEdit* m_raum;

	QComboBox* m_campus;
	QComboBox* m_time;

	QPushButton* m_okButton;
	QPushButton* m_cancelButton;

public:
	CreateVerDialog(QWidget* parent = nullptr);

	QString getName( ) const;
	QString getRaum( ) const;
	QString getCampus( ) const;
	QString getTime( ) const;
};
