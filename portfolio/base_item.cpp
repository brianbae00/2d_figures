#include "base_item.h"

#include <QBrush>
#include <QGraphicsSceneMouseEvent>

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
}

void RoundItem::InitManipulator()
{
	manipulator_.push_back(new QGraphicsEllipseItem(boundingRect().topLeft().x()-4, boundingRect().topLeft().y()-4, 8, 8 ,this));
	manipulator_.push_back(new QGraphicsEllipseItem(boundingRect().topRight().x() - 4, boundingRect().topRight().y() - 4, 8, 8, this));
	manipulator_.push_back(new QGraphicsEllipseItem(boundingRect().bottomLeft().x() - 4, boundingRect().bottomLeft().y() - 4, 8, 8, this));
	manipulator_.push_back(new QGraphicsEllipseItem(boundingRect().bottomRight().x() - 4, boundingRect().bottomRight().y() - 4, 8, 8, this));

	for (auto it : manipulator_)
	{
		it->setBrush(QBrush(Qt::blue));
		it->setVisible(true);
	}
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
}

void RoundItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsEllipseItem::mouseMoveEvent(event);
	setPos(event->scenePos().x()-20 , event->scenePos().y() - 20);
}

void RoundItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	QGraphicsEllipseItem::hoverEnterEvent(event);
}

void RoundItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	QGraphicsEllipseItem::hoverLeaveEvent(event);
}
