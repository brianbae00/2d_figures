#pragma once
#include <QGraphicsItem>

class RoundItem : public QGraphicsEllipseItem
{
public:
	RoundItem(QGraphicsItem* parent = nullptr);
	~RoundItem();
	void InitManipulator();
	void setManipualtorVisible(bool visible);
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

private:
	std::vector<QGraphicsEllipseItem*> manipulator_;
};

class RectItem : public QGraphicsRectItem
{

};

