#include "EinsatzplanWindow.hpp"

EinsatzplanWindow::EinsatzplanWindow(QWidget* parent, QString id, bool admin)
:QMainWindow(parent)
{
    frame_m = new EinsatzplanFrame(this, id, admin);
    setFixedSize(1400,800);
    frame_m->setFixedSize(size());
}