#include "EinsatzplanWindow.hpp"

EinsatzplanWindow::EinsatzplanWindow(QWidget* parent, std::string id, bool admin)
:QMainWindow(parent)
{
    frame_m = new EinsatzplanFrame(this, id, admin);
    setFixedSize(400,550);
    frame_m->setFixedSize(size());
}