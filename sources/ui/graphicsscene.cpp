#include <commands/common.hpp>
#include "graphicsscene.hpp"
#include "diagramlineitem.hpp"
#include "diagramtextitem.hpp"
#include "diagramtextitem.hpp"

#include <QTextCursor>
#include <QGraphicsSceneMouseEvent>

#include <iostream>

GraphicsScene::GraphicsScene(QMenu *itemMenu, QObject* parent)
    : QGraphicsScene(parent)
    , tab_widget_(0)
    , myMode(InsertText)
{
    myItemMenu = itemMenu;
    setBackgroundBrush(Qt::Dense7Pattern);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug() << "GraphicsScene::mousePressEvent";
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    qDebug() << "GraphicsScene::mousePressEvent 2";
    DiagramItem *item;
//    myMode = InsertItem;
    switch (myMode) {
    case InsertItem:
        item = new DiagramItem(myItemType, myItemMenu);
        item->setBrush(myItemColor);
        addItem(item);
        item->setPos(mouseEvent->scenePos());
        emit itemInserted(item);
        break;
    case InsertLine:
        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                    mouseEvent->scenePos()));
        line->setPen(QPen(myLineColor, 2));
        addItem(line);
        break;
    case InsertText:
        textItem = new DiagramTextItem();
        textItem->setFont(myFont);
        textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
        textItem->setZValue(1000.0);
        connect(textItem, SIGNAL(lostFocus(DiagramTextItem*)),
                this, SLOT(editorLostFocus(DiagramTextItem*)));
        connect(textItem, SIGNAL(selectedChange(QGraphicsItem*)),
                this, SIGNAL(itemSelected(QGraphicsItem*)));
        addItem(textItem);
        textItem->setDefaultTextColor(myTextColor);
        textItem->setPos(mouseEvent->scenePos());
        emit textInserted(textItem);
    default:
        break;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void GraphicsScene::editorLostFocus(DiagramTextItem *item)
{
    QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor(cursor);

    if (item->toPlainText().isEmpty()) {
        removeItem(item);
        item->deleteLater();
    }
}

void GraphicsScene::setItemType(DiagramItem::DiagramType type)
{
    myItemType = type;
}

void GraphicsScene::setItemType(commands::shape_type_t type)
{
    myShapeType = type;
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (line != 0 && myMode == InsertLine) {
        auto first = line->line().p1();
        auto second = line->line().p2();

        removeItem(line);
        delete line;
        DiagramLineItem *lineItem = new DiagramLineItem(first, second);
        lineItem->setColor(myLineColor);
        lineItem->setPen(QPen(myLineColor, 1));
        addItem(lineItem);
        // lineItem->updatePosition();
    }
    line = nullptr;
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (myMode == InsertLine && line != 0) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    } else if (myMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void GraphicsScene::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)
{
    if( Qt::ControlModifier == wheelEvent->modifiers() && wheelEvent->orientation() == Qt::Vertical ) {
        emit zoomChanged( wheelEvent->delta() );
    }
    update();
    QGraphicsScene::wheelEvent(wheelEvent);
}

void GraphicsScene::setLineColor(const QColor &color)
{
    myLineColor = color;
    if (isItemChange(DiagramLineItem::Type)) {
        DiagramLineItem *item = qgraphicsitem_cast<DiagramLineItem *>(selectedItems().first());
        item->setColor(myLineColor);
        update();
    }
}

bool GraphicsScene::isItemChange(int type)
{
    foreach (QGraphicsItem *item, selectedItems()) {
        if (item->type() == type)
            return true;
    }
    return false;
}

void GraphicsScene::setItemColor(const QColor &color)
{
    myItemColor = color;
    if (isItemChange(DiagramItem::Type)) {
        DiagramItem *item = qgraphicsitem_cast<DiagramItem *>(selectedItems().first());
        item->setBrush(myItemColor);
    }
}

void GraphicsScene::setTextColor(const QColor &color)
{
    myTextColor = color;
    if (isItemChange(DiagramTextItem::Type)) {
        DiagramTextItem *item = qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
        item->setDefaultTextColor(myTextColor);
    }
}

void GraphicsScene::setFont(const QFont &font)
{
    myFont = font;
    if (isItemChange(DiagramTextItem::Type)) {
        QGraphicsTextItem *item = qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
        //At this point the selection can change so the first selected item might not be a DiagramTextItem
        if (item) {
            item->setFont(myFont);
        }
    }
}

void GraphicsScene::clearAll()
{
    clear();
    update();
}

void GraphicsScene::setMode(Mode mode)
{
    myMode = mode;
}

void GraphicsScene::createDiagramItem(commands::shape_type_t type, std::vector<std::pair<float, float>> points)
{
    switch (type)
    {
    case commands::shape_type_t::LINE:
    case commands::shape_type_t::ARROW: {
        myMode = InsertLine;
        qDebug() << "createDiagramItem implement later";
        // line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
        // line->setPen(QPen(myLineColor, 2));
        // addItem(line);
        break;
    }
    case commands::shape_type_t::TEXT: {
        myMode = InsertText;
        textItem = new DiagramTextItem();
        textItem->setFont(myFont);
        textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
        textItem->setZValue(1000.0);
        connect(textItem, SIGNAL(lostFocus(DiagramTextItem*)),
                this, SLOT(editorLostFocus(DiagramTextItem*)));
        connect(textItem, SIGNAL(selectedChange(QGraphicsItem*)),
                this, SIGNAL(itemSelected(QGraphicsItem*)));
        addItem(textItem);
        textItem->setDefaultTextColor(myTextColor);
        // textItem->setPos(mouseEvent->scenePos());
        emit textInserted(textItem);
    }
    default:
        DiagramItem* item = new DiagramItem(myItemType, myItemMenu);
        item->setBrush(myItemColor);
        addItem(item);
        // item->setPos(mouseEvent->scenePos());
        emit itemInserted(item);
        break;
    }
}
