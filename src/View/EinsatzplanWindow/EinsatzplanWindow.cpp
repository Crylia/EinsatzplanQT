#include "EinsatzplanWindow.hpp"

EinsatzplanWindow::EinsatzplanWindow(QWidget* parent, bool admin)
:QMainWindow(parent)
{
    frame_m = new EinsatzplanFrame(this, admin);
    setFixedSize(400,550);
    frame_m->setFixedSize(size());
}