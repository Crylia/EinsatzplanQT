#include "LoginWindow.hpp"

LoginWindow::LoginWindow(QWidget* parent)
	:QMainWindow(parent) {
	m_frame = new LoginFrame(this);
	setFixedSize(400, 550);
	m_frame->setFixedSize(size( ));
}
