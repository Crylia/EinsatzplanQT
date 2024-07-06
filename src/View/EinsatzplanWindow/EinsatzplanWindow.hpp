# pragma once
# include <QMainWindow>
# include "../EinsatzplanFrame/EinsatzplanFrame.hpp"

class EinsatzplanWindow : public QMainWindow {
	Q_OBJECT
private:
	EinsatzplanFrame* m_frame;

public:
	EinsatzplanWindow(QWidget* parent = nullptr, QString id = "0000000", bool admin = true);
};
