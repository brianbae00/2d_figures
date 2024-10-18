#include <QPushButton>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLayout>
#include "portfolio.h"
#include "base_item.h"

portfolio::portfolio(QWidget *parent)
    : QMainWindow(parent)
{
    InitViewScene();
    Initbuttons();
    InitLayout();
}

portfolio::~portfolio()
{}

void portfolio::InitLayout()
{
    QWidget* leftWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(leftWidget);

    QGridLayout* gridLayout = new QGridLayout();
    mainLayout->addLayout(gridLayout);


    gridLayout->addWidget(circle_button_, 0, 0);
    leftWidget->setFixedSize(130, 900);
    leftWidget->move(0, 0);
}

void portfolio::Initbuttons()
{
    circle_button_ = new QPushButton();
    circle_button_->setText("O");
    circle_button_->setVisible("true");
    circle_button_->setToolTip("generate cirle");
    circle_button_->setFixedSize(50, 50);
    connect(circle_button_, &QPushButton::pressed, [=]() {graphics_view_->SetShapeType(shapetype::kEllipse); });
}

void portfolio::InitViewScene()
{
    graphics_scene_ = new QGraphicsScene(this);
    graphics_scene_->setSceneRect(this->rect());
    graphics_view_ = new customview(this);
    graphics_view_->setScene(graphics_scene_);
    graphics_view_->setFixedSize(1200,900);
    graphics_view_->setResizeAnchor(QGraphicsView::NoAnchor);
    graphics_view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphics_view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

//==========================================================

customview::customview(QWidget* parent)
    :QGraphicsView(parent) , shape_type_(shapetype::kNone)
{
}

customview::~customview()
{
}

void customview::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);
    switch (shape_type_)
    {
    case shapetype::kEllipse:
        GenerateEllipse(mapToScene(event->pos()));
        break;
    case shapetype::kNone:
        ItemSelect(event);
        break;
    }
}

void customview::GenerateEllipse(QPointF pos)
{
    RoundItem* round_item = new RoundItem();
    scene()->addItem(round_item);
    round_item->setPos(pos.x() - 20, pos.y() - 20);
    round_item->setManipualtorVisible(false);
    round_items_.push_back(round_item);
    
}

void customview::mouseMoveEvent(QMouseEvent* event)
{
    QGraphicsView::mouseMoveEvent(event);
}

void customview::mouseReleaseEvent(QMouseEvent* event)
{
    QGraphicsView::mouseReleaseEvent(event);
    if (shape_type_ == shapetype::kNone)
        target_item_ = nullptr;
    else shape_type_ = shapetype::kNone;
}

void customview::ItemSelect(QMouseEvent* event)
{
    QGraphicsItem* pressed_item = nullptr;
    pressed_item = scene()->itemAt(mapToScene(event->pos()), QTransform());
    if (pressed_item)
    {
        if (!dynamic_cast<ControlPointItem*>(pressed_item))
        {
            target_item_ = pressed_item;
            for (auto it : round_items_)
            {
                if (target_item_ != it)
                    it->setManipualtorVisible(false);
            }
        }
    }
    else
    {
        for (auto it : round_items_)
        {
            it->setManipualtorVisible(false);
        }
    }
}