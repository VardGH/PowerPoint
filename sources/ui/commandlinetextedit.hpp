#pragma once

#include <QtWidgets>
#include <QTextEdit>
#include <QKeyEvent>

class CommandLineTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    CommandLineTextEdit(const QString &text="", QWidget *parent = nullptr);

signals:
    void textRearyToParsed(const QString & text);

protected:
    virtual void keyPressEvent(QKeyEvent *e) override;
};