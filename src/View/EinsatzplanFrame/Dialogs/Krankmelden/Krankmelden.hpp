#pragma once

#include <QDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

class Krankmelden : public QDialog {
	Q_OBJECT
protected:
	QPushButton* m_accept;
	QPushButton* m_decline;
	QLabel* m_text;
public:
	Krankmelden(const QString& mitarbeiterName, QWidget* parent = nullptr);
};
