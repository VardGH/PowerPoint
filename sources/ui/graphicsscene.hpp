#pragma once


#include "diagramitem.hpp"
#include "diagramtextitem.hpp"
#include <commands/common.hpp>

#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPair>
#include <QColor>
#include <QMouseEvent>
#include <QApplication>
#include <QUuid>
#include <QFont>

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene(QMenu *itemMenu, QObject* parent = 0);
    virtual ~GraphicsScene() = default;

public:
    enum Mode { InsertItem, InsertLine, InsertText, MoveItem };
    QFont font() const { return myFont; }
    QColor textColor() const { return myTextColor; }
    QColor itemColor() const { return myItemColor; }
    QColor lineColor() const { return myLineColor; }
    void setLineColor(const QColor &color);
    void setTextColor(const QColor &color);
    void setItemColor(const QColor &color);
    void setFont(const QFont &font);

private:
    void createDiagramItem(commands::shape_type_t type, std::vector<std::pair<float, float>> points);

public slots:
    void setMode(Mode mode);
    void setItemType(DiagramItem::DiagramType type);
    void setItemType(commands::shape_type_t type);
    void editorLostFocus(DiagramTextItem *item);
    void clearAll();

signals:
    void zoomChanged(double);
    void itemInserted(DiagramItem *item);
    void textInserted(QGraphicsTextItem *item);
    void itemSelected(QGraphicsItem *item);

private:
    bool isItemChange(int type);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent);

private:
    DiagramItem::DiagramType myItemType;
    commands::shape_type_t myShapeType;
    QGraphicsLineItem *line;
    DiagramTextItem *textItem;
    QMenu *myItemMenu;

    Mode myMode;
    QFont myFont;
    QColor myTextColor;
    QColor myItemColor;
    QColor myLineColor;

private:
    unsigned tab_widget_;
};