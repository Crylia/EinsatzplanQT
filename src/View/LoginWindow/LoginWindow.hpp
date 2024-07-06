# pragma once

#include <QMainWindow>

#include "../LoginFrame/LoginFrame.hpp"

class LoginWindow : public QMainWindow {
    Q_OBJECT
private:
    LoginFrame* m_frame;

public:
    LoginWindow(QWidget* parent = nullptr);
};
