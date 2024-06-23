# pragma once
# include <QFrame>
# include <QWidget>
# include <QPushButton>
# include <QInputDialog>
# include <QLabel>
# include <QVBoxLayout>
# include <QMessageBox>
# include "../../Controller/LoginFrameController/LoginFrameController.hpp"

class LoginFrame : public QFrame{
    Q_OBJECT
protected:
    QLabel* header_m;
    QLineEdit* id_m;
    QLineEdit* password_m;
    QPushButton* loginButton_m; 

    void loginButtonClicked();

public:
    LoginFrame(QWidget* parent = nullptr);
};