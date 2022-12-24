
#include "diagramitem.hpp"

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>

DiagramItem::DiagramItem(DiagramType diagramType, QMenu *contextMenu,
             QGraphicsItem *parent)
    : QGraphicsPolygonItem(parent)
{
    myDiagramType = diagramType;
    myContextMenu = contextMenu;

    QPainterPath path;
//    myDiagramType = Step;
    switch (myDiagramType) {
        case StartEnd:
            path.moveTo(200, 50);
            path.arcTo(150, 0, 50, 50, 0, 90);
            path.arcTo(50, 0, 50, 50, 90, 90);
            path.arcTo(50, 50, 50, 50, 180, 90);
            path.arcTo(150, 50, 50, 50, 270, 90);
            path.lineTo(200, 25);
            myPolygon = path.toFillPolygon();
            break;
        case Conditional:
            myPolygon << QPointF(-100, 0) << QPointF(0, 100)
                      << QPointF(100, 0) << QPointF(0, -100)
                      << QPointF(-100, 0);
            break;
        case Step:
            myPolygon << QPointF(-100, -100) << QPointF(100, -100)
                      << QPointF(100, 100) << QPointF(-100, 100)
                      << QPointF(-100, -100);
            break;
        default:
            myPolygon << QPointF(-120, -80) << QPointF(-70, 80)
                      << QPointF(120, 80) << QPointF(70, -80)
                      << QPointF(-120, -80);
            break;
    }
    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}


DiagramItem::DiagramItem(commands::shape_type_t type, std::vector<std::pair<float, float>> points, QMenu *contextMenu,
             QGraphicsItem *parent)
    : QGraphicsPolygonItem(parent)
{
    myShapeType = type;
    myContextMenu = contextMenu;
    QPainterPath path;
    switch (myShapeType) {
    case commands::shape_type_t::TEXT:
        ASSERT_MESSAGE(false, "NEED TO CALL DiagramTextItem Constructor");
    case commands::shape_type_t::LINE:
        ASSERT_MESSAGE(false, "NEED TO CALL DiagramLineItem Constructor");
    case commands::shape_type_t::ARROW:
        ASSERT_MESSAGE(false, "NEED TO CALL DiagramLineItem Constructor");
    case commands::shape_type_t::SQUARE:
    case commands::shape_type_t::RECTANGLE:
    case commands::shape_type_t::TRIANGLE:
    case commands::shape_type_t::CIRCLE:
    case commands::shape_type_t::ELIPSE:
    case commands::shape_type_t::PARALLOGRAM:
    case commands::shape_type_t::POINT: {
        for (const auto item : points) {
            myPolygon << QPointF(item.first, item.second);
        }
    }
    case commands::shape_type_t::UNKNOWN:
        ASSERT_MESSAGE(false, "UNKNOWN ARGUMENT IS NOT ALLOWED");
    }
}


QPixmap DiagramItem::image() const
{
    QPixmap pixmap(250, 250);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8));
    painter.translate(125, 125);
    painter.drawPolyline(myPolygon);

    return pixmap;
}

void DiagramItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}

QVariant DiagramItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    // if (change == QGraphicsItem::ItemPositionChange) {
    //     foreach (Arrow *arrow, arrows) {
    //         arrow->updatePosition();
    //     }
    // }

    return value;
}
