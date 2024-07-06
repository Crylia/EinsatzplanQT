# pragma once
# include <QLabel>
# include <QMouseEvent>
# include <QPainter>

class GridItem : public QLabel {
	Q_OBJECT
protected:
	//QLabel* text_m;

	void mousePressEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
public:
	GridItem(QString text = "", QWidget* parent = nullptr);
signals:
	void clicked( );
};
