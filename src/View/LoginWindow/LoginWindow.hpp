# pragma once
#include <QMainWindow>
#include "../LoginFrame/LoginFrame.hpp"

class LoginWindow : public QMainWindow{
    Q_OBJECT
private:
    LoginFrame* frame_m;


public:
    LoginWindow(QWidget* parent = nullptr);
};