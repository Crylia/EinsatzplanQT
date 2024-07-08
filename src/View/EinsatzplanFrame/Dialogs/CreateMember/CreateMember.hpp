#pragma once

#include <QDialog>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>

class CreateMemDialog : public QDialog {
	Q_OBJECT
protected:
	QLineEdit* m_name;
	QLineEdit* m_email;
	QLineEdit* m_password;
	QCheckBox* m_admin;
	QPushButton* m_okButton;
	QPushButton* m_cancelButton;

public:
	CreateMemDialog(QWidget* parent = nullptr);

	QString getName( ) const;
	QString getEmail( ) const;
	QString getPassword( ) const;
	bool isAdmin( ) const;
};
