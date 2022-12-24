#pragma once

#include "graphicsscene.hpp"
#include "commandlinetextedit.hpp"

#include <QMainWindow>

// class DiagramScene;

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
class QDockWidget;
class QWidget;
class QVBoxLayout;
class QTextEdit;
class QPushButton;
class QPlainTextEdit;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void updateZoomFactor(double);
    void deleteItem();
    void pointerGroupClicked(int id);
    void itemInserted(DiagramItem *item);
    void textInserted(QGraphicsTextItem *item);
    void currentFontChanged(const QFont &font);
    void fontSizeChanged(const QString &size);
    void sceneScaleChanged(const QString &scale);
    void textColorChanged();
    void itemColorChanged();
    void lineColorChanged();
    void textButtonTriggered();
    void fillButtonTriggered();
    void lineButtonTriggered();
    void handleFontChange();
    void itemSelected(QGraphicsItem *item);
    void about();
    void showHideLog();
    void parseCommandLine(const QString& command);
    void exportPDF();

private:
    void createToolBox();
    void createActions();
    void createMenus();
    void createToolbars();
    void createDocks();
    QMenu *createColorMenu(const char *slot, QColor defaultColor);
    QIcon createColorToolButtonIcon(const QString &image, QColor color);
    QIcon createColorIcon(QColor color);

private:
    double zoom_factor_;
    double zoom_step_;

private:
    GraphicsScene *scene;
    QGraphicsView *view;

    QAction *exitAction;
    QAction *exportPDFAction;
    QAction *addAction;
    QAction *deleteAction;

    QAction *toFrontAction;
    QAction *sendBackAction;
    QAction *aboutAction;

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *aboutMenu;

    QToolBar *textToolBar;
    QToolBar *editToolBar;
    QToolBar *colorToolBar;
    QToolBar *pointerToolbar;

    QComboBox *sceneScaleCombo;
    QComboBox *itemColorCombo;
    QComboBox *textColorCombo;
    QComboBox *fontSizeCombo;
    QFontComboBox *fontCombo;

    QButtonGroup *buttonGroup;
    QButtonGroup *pointerTypeGroup;
    QButtonGroup *backgroundButtonGroup;
    QToolButton *fontColorToolButton;
    QToolButton *fillColorToolButton;
    QToolButton *lineColorToolButton;
    QAction *boldAction;
    QAction *underlineAction;
    QAction *italicAction;
    QAction *textAction;
    QAction *fillAction;
    QAction *lineAction;

private:
    QDockWidget *rightDock;
    QDockWidget *bottomLogDock;
    QWidget* logWidget;
    QVBoxLayout* logLayout;
    QPlainTextEdit* logTextEdit;
    CommandLineTextEdit* cli;
    QPushButton* logButton;
    bool logIsHidden;
};

