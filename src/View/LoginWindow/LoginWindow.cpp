#include "LoginWindow.hpp"

LoginWindow::LoginWindow(QWidget* parent)
:QMainWindow(parent)
{
    frame_m = new LoginFrame(this);
    setFixedSize(400,550);
    frame_m->setFixedSize(size());
}