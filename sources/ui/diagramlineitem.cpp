#include "diagramlineitem.hpp"

DiagramLineItem::DiagramLineItem(QPointF left, QPointF right, QString name, QGraphicsItem* parent)
    : QGraphicsLineItem(QLineF(left, right))
    , name_(name)
{
    setFlag(ItemIsMovable, true);
    setFlag(ItemIsSelectable, true);
}

DiagramLineItem::DiagramLineItem(QLineF li, QString name, QGraphicsItem* parent)
    : QGraphicsLineItem(QLineF(li))
    , name_(name)
{
    setFlag(ItemIsMovable, true);
    setFlag(ItemIsSelectable, true);
    
}

void DiagramLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(QPen(Qt::red, 3));
    painter->setBrush(Qt::green); //TODO add colour setting mechanism
    QGraphicsLineItem::paint(painter, option, widget);
}

QRectF DiagramLineItem::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QString DiagramLineItem::name() const
{
    return name_;
}
