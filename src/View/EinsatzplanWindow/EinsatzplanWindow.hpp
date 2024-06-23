# pragma once
# include <QMainWindow>
# include "../EinsatzplanFrame/EinsatzplanFrame.hpp"

class EinsatzplanWindow : public QMainWindow{
    Q_OBJECT
private:
    EinsatzplanFrame* frame_m;


public:
    EinsatzplanWindow(QWidget* parent = nullptr, std::string id, bool admin);
};