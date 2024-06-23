# pragma once
# include <QMainWindow>
# include "../EinsatzplanFrame/EinsatzplanFrame.hpp"

class LoginWindow : public QMainWindow{
    Q_OBJECT
private:
    EinsatzplanFrame* frame_m;


public:
    EinsatzplanWindow(QWidget* parent = nullptr);
};