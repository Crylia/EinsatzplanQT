# include <QApplication>
# include "View/EinsatzplanWindow/EinsatzplanWindow.hpp"

int main(int argc,char* argv[]){
    QApplication app(argc,argv);
    EinsatzplanWindow* einsatzplanWindow = new EinsatzplanWindow();
    einsatzplanWindow->show();
    return app.exec();
}