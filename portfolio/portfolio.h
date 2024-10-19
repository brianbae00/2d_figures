#pragma once
#include <QtWidgets>
#include "ui_portfolio.h"

class QPushButton;
class QGraphicsItem;
class QGraphicsView;
class QGraphicsScene;
class RoundItem;
class RectItem;

enum class shapetype
{
    kNone,
    kEllipse,
    kRectangle
};

class customview : public QGraphicsView
{
    Q_OBJECT
public:
    customview(QWidget* parent = nullptr);
    ~customview();
    void SetShapeType(shapetype type) { shape_type_ = type; }
    void GenerateEllipse(QPointF pos);
    void GenerateRectangle(QPointF pos);
    void ItemSelect(QMouseEvent* event);
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
private:
    shapetype shape_type_;
    std::vector<RoundItem*> round_items_;
    std::vector<RectItem*> rect_items_;
    QGraphicsItem* target_item_ = nullptr;
};

class portfolio : public QMainWindow
{
    Q_OBJECT

public:
    portfolio(QWidget *parent = nullptr);
    ~portfolio();
private:
    void InitLayout();
    void Initbuttons();
    void InitViewScene();

private:
    //Ui::portfolioClass ui;
    QPushButton* circle_button_ = nullptr;
    customview* graphics_view_ = nullptr;
    QGraphicsScene* graphics_scene_ = nullptr;
    QPushButton* rect_button_ = nullptr;
};
