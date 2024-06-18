# include <QApplication>
# include "View/LoginWindow/LoginWindow.hpp"

int main(int argc, char* argv[]){
    QApplication app(argc,argv);
    LoginWindow* loginWindow = new LoginWindow();
    loginWindow->show();
    return app.exec();
}