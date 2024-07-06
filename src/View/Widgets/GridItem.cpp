# include "GridItem.hpp"

GridItem::GridItem(QString text, QWidget* parent)
	:QLabel(parent) {
	//Fix later
	//text_m = new QLabel(text,this);
	//text_m->setAlignment(Qt::AlignCenter);
	setText(text);
}

void GridItem::mousePressEvent(QMouseEvent* event) {
	if (event->button( ) == Qt::RightButton)
		emit clicked( );
	QWidget::mousePressEvent(event);
}

void GridItem::paintEvent(QPaintEvent* event) {

}
