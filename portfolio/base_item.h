#pragma once
#include <QGraphicsItem>

class ControlPointItem : public QObject,public QGraphicsEllipseItem
{
	Q_OBJECT
public:
	ControlPointItem(QGraphicsItem* parent = nullptr);
	ControlPointItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent = nullptr);
	~ControlPointItem();
signals:
	void sigPointTranslate();
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
};

class RoundItem :public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT
public:
	RoundItem(QGraphicsItem* parent = nullptr);
	~RoundItem();
	void InitManipulator();
	void setManipualtorVisible(bool visible);
private slots:
	void slotSetScale();
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

private:
	std::vector<ControlPointItem*> manipulator_;
};

class RectItem :public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public :
	RectItem(QGraphicsItem* parent = nullptr);
	~RectItem();
	void InitManipulator();
	void setManipualtorVisible(bool visible);
private slots:
	void slotSetScale();
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

private:
	std::vector<ControlPointItem*> manipulator_;
};

