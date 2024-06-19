# pragma once
# include <QFrame>
# include <QWidget>
# include <QPushButton>
# include <QInputDialog>
# include <QLabel>

class LoginFrame : public QFrame{
    Q_OBJECT
private:
    QLabel* header_m;
    QLineEdit* id_m;
    QLineEdit* password_m;
    QPushButton* loginButton_m; 

public:
    LoginFrame(QWidget* parent = nullptr);
};