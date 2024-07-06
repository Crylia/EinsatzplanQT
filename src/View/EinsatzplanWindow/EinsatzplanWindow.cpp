#include "EinsatzplanWindow.hpp"

EinsatzplanWindow::EinsatzplanWindow(QWidget* parent, QString id, bool admin)
	:QMainWindow(parent) {
	m_frame = new EinsatzplanFrame(this, id, admin);
	setFixedSize(1400, 800);
	m_frame->setFixedSize(size( ));
}
