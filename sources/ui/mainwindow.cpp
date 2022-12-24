
#include "mainwindow.h"
#include "diagramtextitem.hpp"
#include <common/parser.hpp>
#include <common/writer.hpp>

#include <QDockWidget>
#include <QtWidgets>
#include <QPainter>
// #include <QPrinter>
#include <QPlainTextEdit>

const int InsertTextButton = 10;

MainWindow::MainWindow()
    : zoom_factor_(1), zoom_step_(1.1), logIsHidden(true)
{
    createActions();
    createToolBox();
    createMenus();

    scene = new GraphicsScene(itemMenu, this);
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));
    connect(scene, SIGNAL(zoomChanged(double)),
            this, SLOT(updateZoomFactor(double)));
    connect(scene, SIGNAL(itemInserted(DiagramItem *)),
            this, SLOT(itemInserted(DiagramItem *)));
    connect(scene, SIGNAL(textInserted(QGraphicsTextItem *)),
            this, SLOT(textInserted(QGraphicsTextItem *)));
    connect(scene, SIGNAL(itemSelected(QGraphicsItem *)),
            this, SLOT(itemSelected(QGraphicsItem *)));
    createToolbars();

    QHBoxLayout *layout = new QHBoxLayout;
    view = new QGraphicsView(scene);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    createDocks();
    setWindowTitle(tr("Power Point"));
    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::createDocks()
{
    rightDock = new QDockWidget(tr("Propereties"));
    rightDock->setAllowedAreas(Qt::RightDockWidgetArea);
    rightDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    rightDock->setMinimumWidth(150);
    addDockWidget(Qt::RightDockWidgetArea, rightDock);

    bottomLogDock = new QDockWidget(tr("Log"));
    bottomLogDock->setAllowedAreas(Qt::BottomDockWidgetArea);
    bottomLogDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    logWidget = new QWidget(this);
    logLayout = new QVBoxLayout;
    logTextEdit = new QPlainTextEdit("log file");
    logTextEdit->setReadOnly(true);
    logLayout->addWidget(logTextEdit);
    cli = new CommandLineTextEdit();
    cli->setMaximumHeight(30);
    logLayout->addWidget(cli);
    connect(cli, SIGNAL(textRearyToParsed(QString)), logTextEdit, SLOT(appendPlainText(QString)));
    connect(cli, SIGNAL(textRearyToParsed(QString)), this, SLOT(parseCommandLine(QString)));
    logWidget->setLayout(logLayout);
    bottomLogDock->setWidget(logWidget);
    bottomLogDock->setHidden(true);
    addDockWidget(Qt::BottomDockWidgetArea, bottomLogDock);
}

void MainWindow::updateZoomFactor(double zoom)
{
    if (zoom > 0 && zoom_factor_ < 20)
    {
        zoom_factor_ += zoom_step_;
        view->scale(zoom_step_, zoom_step_);
        scene->update();
    }
    else if (zoom < 0 && zoom_factor_ > -12)
    {
        zoom_factor_ -= zoom_step_;
        view->scale(1.0 / zoom_step_, 1.0 / zoom_step_);
        scene->update();
    }
    scene->update();
}

void MainWindow::deleteItem()
{
    foreach (QGraphicsItem *item, scene->selectedItems())
    {
        scene->removeItem(item);
        delete item;
    }
}

void MainWindow::pointerGroupClicked(int)
{
    scene->setMode(GraphicsScene::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow::itemInserted(DiagramItem *item)
{
    pointerTypeGroup->button(int(GraphicsScene::MoveItem))->setChecked(true);
    scene->setMode(GraphicsScene::Mode(pointerTypeGroup->checkedId()));
    // buttonGroup->button(int(item->diagramType()))->setChecked(false);
}

void MainWindow::textInserted(QGraphicsTextItem *)
{
    // buttonGroup->button(InsertTextButton)->setChecked(false);
    scene->setMode(GraphicsScene::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow::currentFontChanged(const QFont &)
{
    handleFontChange();
}

void MainWindow::fontSizeChanged(const QString &)
{
    handleFontChange();
}

void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

void MainWindow::textColorChanged()
{
    textAction = qobject_cast<QAction *>(sender());
    fontColorToolButton->setIcon(createColorToolButtonIcon(
        ":/images/textpointer.png",
        qvariant_cast<QColor>(textAction->data())));
    textButtonTriggered();
}

void MainWindow::itemColorChanged()
{
    fillAction = qobject_cast<QAction *>(sender());
    fillColorToolButton->setIcon(createColorToolButtonIcon(
        ":/images/floodfill.png",
        qvariant_cast<QColor>(fillAction->data())));
    fillButtonTriggered();
}

void MainWindow::lineColorChanged()
{
    lineAction = qobject_cast<QAction *>(sender());
    lineColorToolButton->setIcon(createColorToolButtonIcon(
        ":/images/linecolor.png",
        qvariant_cast<QColor>(lineAction->data())));
    lineButtonTriggered();
}

void MainWindow::textButtonTriggered()
{
    scene->setTextColor(qvariant_cast<QColor>(textAction->data()));
}

void MainWindow::fillButtonTriggered()
{
    scene->setItemColor(qvariant_cast<QColor>(fillAction->data()));
}

void MainWindow::lineButtonTriggered()
{
    scene->setLineColor(qvariant_cast<QColor>(lineAction->data()));
}

void MainWindow::handleFontChange()
{
    QFont font = fontCombo->currentFont();
    font.setPointSize(fontSizeCombo->currentText().toInt());
    font.setWeight(boldAction->isChecked() ? QFont::Bold : QFont::Normal);
    font.setItalic(italicAction->isChecked());
    font.setUnderline(underlineAction->isChecked());

    scene->setFont(font);
}

void MainWindow::itemSelected(QGraphicsItem *item)
{
    DiagramTextItem *textItem = qgraphicsitem_cast<DiagramTextItem *>(item);

    QFont font = textItem->font();
    fontCombo->setCurrentFont(font);
    fontSizeCombo->setEditText(QString().setNum(font.pointSize()));
    boldAction->setChecked(font.weight() == QFont::Bold);
    italicAction->setChecked(font.italic());
    underlineAction->setChecked(font.underline());
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Power Point"),
                       tr("The <b>Power Point</b> is a slide creation application"));
}

void MainWindow::createToolBox()
{
    QGridLayout *layout = new QGridLayout;

    QToolButton *textButton = new QToolButton;
    textButton->setCheckable(true);
    textButton->setIcon(QIcon(QPixmap(":/images/textpointer.png")));
    textButton->setIconSize(QSize(50, 50));
    QGridLayout *textLayout = new QGridLayout;
    textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
    textLayout->addWidget(new QLabel(tr("Text")), 1, 0, Qt::AlignCenter);
    QWidget *textWidget = new QWidget;
    textWidget->setLayout(textLayout);
    layout->addWidget(textWidget, 1, 1);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);
}

void MainWindow::createActions()
{
    deleteAction = new QAction(QIcon(":/images/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit Scenediagram example"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    exportPDFAction = new QAction(tr("ExportPDF"), this);
    exportPDFAction->setStatusTip(tr("Export Scene as PDF"));
    connect(exportPDFAction, SIGNAL(triggered()), this, SLOT(exportPDF()));

    boldAction = new QAction(tr("Bold"), this);
    boldAction->setCheckable(true);
    QPixmap pixmap(":/images/bold.png");
    boldAction->setIcon(QIcon(pixmap));
    boldAction->setShortcut(tr("Ctrl+B"));
    connect(boldAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    italicAction = new QAction(QIcon(":/images/italic.png"), tr("Italic"), this);
    italicAction->setCheckable(true);
    italicAction->setShortcut(tr("Ctrl+I"));
    connect(italicAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    underlineAction = new QAction(QIcon(":/images/underline.png"), tr("Underline"), this);
    underlineAction->setCheckable(true);
    underlineAction->setShortcut(tr("Ctrl+U"));
    connect(underlineAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("F1"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);
    fileMenu->addAction(exportPDFAction);

    itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}

void MainWindow::createToolbars()
{
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);

    fontCombo = new QFontComboBox();
    connect(fontCombo, SIGNAL(currentFontChanged(QFont)),
            this, SLOT(currentFontChanged(QFont)));

    fontSizeCombo = new QComboBox;
    fontSizeCombo->setEditable(true);
    for (int i = 8; i < 30; i = i + 2)
        fontSizeCombo->addItem(QString().setNum(i));
    QIntValidator *validator = new QIntValidator(2, 64, this);
    fontSizeCombo->setValidator(validator);
    connect(fontSizeCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(fontSizeChanged(QString)));

    fontColorToolButton = new QToolButton;
    fontColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fontColorToolButton->setMenu(createColorMenu(SLOT(textColorChanged()), Qt::black));
    textAction = fontColorToolButton->menu()->defaultAction();
    fontColorToolButton->setIcon(createColorToolButtonIcon(":/images/textpointer.png", Qt::black));
    fontColorToolButton->setAutoFillBackground(true);
    connect(fontColorToolButton, SIGNAL(clicked()),
            this, SLOT(textButtonTriggered()));

    fillColorToolButton = new QToolButton;
    fillColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fillColorToolButton->setMenu(createColorMenu(SLOT(itemColorChanged()), Qt::white));
    fillAction = fillColorToolButton->menu()->defaultAction();
    fillColorToolButton->setIcon(createColorToolButtonIcon(
        ":/images/floodfill.png", Qt::white));
    connect(fillColorToolButton, SIGNAL(clicked()),
            this, SLOT(fillButtonTriggered()));

    lineColorToolButton = new QToolButton;
    lineColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    lineColorToolButton->setMenu(createColorMenu(SLOT(lineColorChanged()), Qt::black));
    lineAction = lineColorToolButton->menu()->defaultAction();
    lineColorToolButton->setIcon(createColorToolButtonIcon(
        ":/images/linecolor.png", Qt::black));
    connect(lineColorToolButton, SIGNAL(clicked()),
            this, SLOT(lineButtonTriggered()));

    textToolBar = addToolBar(tr("Font"));
    textToolBar->addWidget(fontCombo);
    textToolBar->addWidget(fontSizeCombo);
    textToolBar->addAction(boldAction);
    textToolBar->addAction(italicAction);
    textToolBar->addAction(underlineAction);

    colorToolBar = addToolBar(tr("Color"));
    colorToolBar->addWidget(fontColorToolButton);
    colorToolBar->addWidget(fillColorToolButton);
    colorToolBar->addWidget(lineColorToolButton);

    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/images/pointer.png"));
    QToolButton *linePointerButton = new QToolButton;
    linePointerButton->setCheckable(true);
    linePointerButton->setIcon(QIcon(":/images/linepointer.png"));

    pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, int(GraphicsScene::MoveItem));
    pointerTypeGroup->addButton(linePointerButton, int(GraphicsScene::InsertLine));
    connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(pointerGroupClicked(int)));

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(sceneScaleChanged(QString)));

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(pointerButton);
    pointerToolbar->addWidget(linePointerButton);
    pointerToolbar->addWidget(sceneScaleCombo);

    logButton = new QPushButton(tr("Log"));
    logButton->setStyleSheet("QPushButton{background-color: rgba(0 ,0 ,0 ,0%); font-weight: bold;} QPushButton:hover{background-color: lightBlue;}");
    connect(logButton, SIGNAL(clicked(bool)), this, SLOT(showHideLog()));
    statusBar()->setMaximumHeight(27);
    statusBar()->addWidget(logButton);
}

QMenu *MainWindow::createColorMenu(const char *slot, QColor defaultColor)
{
    QList<QColor> colors;
    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow;
    QStringList names;
    names << tr("black") << tr("white") << tr("red") << tr("blue")
          << tr("yellow");

    QMenu *colorMenu = new QMenu(this);
    for (int i = 0; i < colors.count(); ++i)
    {
        QAction *action = new QAction(names.at(i), this);
        action->setData(colors.at(i));
        action->setIcon(createColorIcon(colors.at(i)));
        connect(action, SIGNAL(triggered()), this, slot);
        colorMenu->addAction(action);
        if (colors.at(i) == defaultColor)
        {
            colorMenu->setDefaultAction(action);
        }
    }
    return colorMenu;
}

QIcon MainWindow::createColorToolButtonIcon(const QString &imageFile, QColor color)
{
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(imageFile);
    // Draw icon centred horizontally on button.
    QRect target(4, 0, 42, 43);
    QRect source(0, 0, 42, 43);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
}

QIcon MainWindow::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}

void MainWindow::showHideLog()
{
    logIsHidden = !logIsHidden;
    bottomLogDock->setHidden(logIsHidden);
}

void MainWindow::parseCommandLine(const QString &command)
{
    common::writer::get_instance().write_message(common::message_type::INFO, command.toStdString());
    common::parser::get_instance().parse(command.toStdString());
}

void MainWindow::exportPDF()
{
    qDebug() << "exportPDF  called";
    // QString fileName = "exported_scen.pdf";
    // // QString fileName = QFileDialog::getSaveFileName(this, "Export PDF",
    //                                                 // QString(), "*.pdf");
	// QPrinter printer(QPrinter::HighResolution);
	// printer.setPageSize(QPrinter::A4);
	// printer.setOrientation(QPrinter::Portrait);
	// printer.setOutputFormat(QPrinter::PdfFormat);
    //     printer.setOutputFileName(fileName);
 
	// QPainter p(&printer);
	// scene->render(&p);
	// p.end();
}