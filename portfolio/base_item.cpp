#include "base_item.h"

#include <QBrush>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

ControlPointItem::ControlPointItem(QGraphicsItem* parent)
	:QGraphicsEllipseItem(parent)
{
	setRect(0, 0, 8, 8);
	setBrush(QBrush(Qt::blue));
	setAcceptedMouseButtons(Qt::LeftButton);
	setFlag(QGraphicsItem::ItemIsSelectable);
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsFocusable);
	setAcceptHoverEvents(true);
}

ControlPointItem::ControlPointItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent)
	:QGraphicsEllipseItem(x,y,w,h,parent)
{
	setBrush(QBrush(Qt::blue));
	setAcceptedMouseButtons(Qt::LeftButton);
	setFlag(QGraphicsItem::ItemIsSelectable);
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsFocusable);
	setAcceptHoverEvents(true);
}

ControlPointItem::~ControlPointItem()
{
}

void ControlPointItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsEllipseItem::mousePressEvent(event);
}

void ControlPointItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsEllipseItem::mouseReleaseEvent(event);
}

void ControlPointItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsEllipseItem::mouseMoveEvent(event);
	emit sigPointTranslate();
}

void ControlPointItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	QGraphicsEllipseItem::hoverEnterEvent(event);
}

void ControlPointItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	QGraphicsEllipseItem::hoverLeaveEvent(event);
}

//================================================
RoundItem::RoundItem(QGraphicsItem* parent)
	:QGraphicsEllipseItem(parent)
{
	setBrush(QBrush(Qt::black));
	setRect(0, 0, 40, 40);
	InitManipulator();
	setAcceptedMouseButtons(Qt::LeftButton);
	setFlag(QGraphicsItem::ItemIsSelectable);
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsFocusable);
	setAcceptHoverEvents(true);
}

RoundItem::~RoundItem()
{
	for (auto it : manipulator_)
		delete it;
}

void RoundItem::InitManipulator()
{
	manipulator_.push_back(new ControlPointItem(boundingRect().topLeft().x()-4, boundingRect().topLeft().y()-4, 8, 8 ,this));
	manipulator_.push_back(new ControlPointItem(boundingRect().topRight().x() - 4, boundingRect().topRight().y() - 4, 8, 8, this));
	manipulator_.push_back(new ControlPointItem(boundingRect().bottomLeft().x() - 4, boundingRect().bottomLeft().y() - 4, 8, 8, this));
	manipulator_.push_back(new ControlPointItem(boundingRect().bottomRight().x() - 4, boundingRect().bottomRight().y() - 4, 8, 8, this));
	for (auto it : manipulator_)
		connect(it, &ControlPointItem::sigPointTranslate, this, &RoundItem::slotSetScale);
}

void RoundItem::slotSetScale()
{
	auto move_point = QObject::sender();
	if (move_point == manipulator_[0] || move_point == manipulator_[3])
	{
		manipulator_[1]->setPos(manipulator_[3]->pos().x(), manipulator_[0]->pos().y());
		manipulator_[2]->setPos(manipulator_[0]->pos().x(), manipulator_[3]->pos().y());
	}
	else
	{
		manipulator_[0]->setPos(manipulator_[2]->pos().x(), manipulator_[1]->pos().y());
		manipulator_[3]->setPos(manipulator_[1]->pos().x(), manipulator_[2]->pos().y());
	}

	QRectF bSceneBoundingBox = manipulator_[0]->mapToParent(manipulator_[0]->boundingRect()).boundingRect();
	QRectF cSceneBoundingBox = manipulator_[3]->mapToParent(manipulator_[3]->boundingRect()).boundingRect();
	qreal minX = std::min(bSceneBoundingBox.left(), cSceneBoundingBox.left());
	qreal minY = std::min(bSceneBoundingBox.top(), cSceneBoundingBox.top());
	qreal maxX = std::max(bSceneBoundingBox.right(), cSceneBoundingBox.right());
	qreal maxY = std::max(bSceneBoundingBox.bottom(), cSceneBoundingBox.bottom());

	QRectF newRect(minX, minY, maxX - minX, maxY - minY);
	setRect(newRect);

}

void RoundItem::setManipualtorVisible(bool visible)
{
	for (auto it : manipulator_)
		it->setVisible(visible);
}

void RoundItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsEllipseItem::mousePressEvent(event);
	setManipualtorVisible(true);
}

void RoundItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsEllipseItem::mouseReleaseEvent(event);
	setBrush(QBrush(Qt::black));
}

void RoundItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsEllipseItem::mouseMoveEvent(event);
	//setPos(event->scenePos().x()-20 , event->scenePos().y() - 20);
}

void RoundItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	QGraphicsEllipseItem::hoverEnterEvent(event);
}

void RoundItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	QGraphicsEllipseItem::hoverLeaveEvent(event);
}

//================================================
RectItem::RectItem(QGraphicsItem* parent)
	:QGraphicsRectItem(parent)
{
	setBrush(QBrush(Qt::black));
	setRect(0, 0, 40, 40);
	InitManipulator();
	setAcceptedMouseButtons(Qt::LeftButton);
	setFlag(QGraphicsItem::ItemIsSelectable);
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsFocusable);
	setAcceptHoverEvents(true);
}

RectItem::~RectItem()
{
	for (auto it : manipulator_)
		delete it;
}

void RectItem::InitManipulator()
{
	manipulator_.push_back(new ControlPointItem(boundingRect().topLeft().x() - 4, boundingRect().topLeft().y() - 4, 8, 8, this));
	manipulator_.push_back(new ControlPointItem(boundingRect().topRight().x() - 4, boundingRect().topRight().y() - 4, 8, 8, this));
	manipulator_.push_back(new ControlPointItem(boundingRect().bottomLeft().x() - 4, boundingRect().bottomLeft().y() - 4, 8, 8, this));
	manipulator_.push_back(new ControlPointItem(boundingRect().bottomRight().x() - 4, boundingRect().bottomRight().y() - 4, 8, 8, this));
	for (auto it : manipulator_)
		connect(it, &ControlPointItem::sigPointTranslate, this, &RectItem::slotSetScale);
}

void RectItem::slotSetScale()
{
	auto move_point = QObject::sender();
	if (move_point == manipulator_[0] || move_point == manipulator_[3])
	{
		manipulator_[1]->setPos(manipulator_[3]->pos().x(), manipulator_[0]->pos().y());
		manipulator_[2]->setPos(manipulator_[0]->pos().x(), manipulator_[3]->pos().y());
	}
	else
	{
		manipulator_[0]->setPos(manipulator_[2]->pos().x(), manipulator_[1]->pos().y());
		manipulator_[3]->setPos(manipulator_[1]->pos().x(), manipulator_[2]->pos().y());
	}

	QRectF bSceneBoundingBox = manipulator_[0]->mapToParent(manipulator_[0]->boundingRect()).boundingRect();
	QRectF cSceneBoundingBox = manipulator_[3]->mapToParent(manipulator_[3]->boundingRect()).boundingRect();
	qreal minX = std::min(bSceneBoundingBox.left(), cSceneBoundingBox.left())+4;
	qreal minY = std::min(bSceneBoundingBox.top(), cSceneBoundingBox.top()) + 4;
	qreal maxX = std::max(bSceneBoundingBox.right(), cSceneBoundingBox.right()) - 4;
	qreal maxY = std::max(bSceneBoundingBox.bottom(), cSceneBoundingBox.bottom()) - 4;

	QRectF newRect(minX, minY, maxX - minX, maxY - minY);
	setRect(newRect);

}

void RectItem::setManipualtorVisible(bool visible)
{
	for (auto it : manipulator_)
		it->setVisible(visible);
}

void RectItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsRectItem::mousePressEvent(event);
	setManipualtorVisible(true);
}

void RectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsRectItem::mouseReleaseEvent(event);
	setBrush(QBrush(Qt::black));
}

void RectItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsRectItem::mouseMoveEvent(event);
	//setPos(event->scenePos().x()-20 , event->scenePos().y() - 20);
}

void RectItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	QGraphicsRectItem::hoverEnterEvent(event);
}

void RectItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	QGraphicsRectItem::hoverLeaveEvent(event);
}
