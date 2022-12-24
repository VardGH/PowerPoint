#pragma once

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QStaticText>
#include <QObject>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <QLineF>
//class graphicsScene;

class DiagramLineItem :public QGraphicsLineItem
{
public:
    enum { Type = UserType + 4 };
    DiagramLineItem(QPointF left, QPointF right, QString name = "", QGraphicsItem* parent = nullptr);
    DiagramLineItem(QLineF li, QString name = "", QGraphicsItem* parent = nullptr);
    virtual ~DiagramLineItem() = default;

    QString name() const;
    int type() const override { return Type; }
    void setColor(const QColor &color) { myColor = color; }
    // @brief QGraphicsItem specific functions
protected:
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
    QColor myColor;
    QString name_;
};