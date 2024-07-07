#pragma once

#include <QFrame>
#include <QWidget>
#include <QPushButton>
#include <QInputDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QMainWindow>

#include "../../Controller/LoginFrameController/LoginFrameController.hpp"
#include "../../View/EinsatzplanWindow/EinsatzplanWindow.hpp"

class LoginFrame : public QFrame {
	Q_OBJECT
protected:
	QMainWindow* m_parent;
	QLabel* m_header;
	QLineEdit* m_id;
	QLineEdit* m_password;
	QPushButton* m_loginButton;

	void loginButtonClicked( );

public:
	LoginFrame(QWidget* parent = nullptr);
	~LoginFrame( );
};
