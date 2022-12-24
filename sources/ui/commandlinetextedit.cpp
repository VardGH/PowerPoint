#include "commandlinetextedit.hpp"

CommandLineTextEdit::CommandLineTextEdit(const QString &text, QWidget *parent)
    : QTextEdit(text, parent)
{
}

void CommandLineTextEdit::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Return) {
        QString ret = toPlainText();
        emit textRearyToParsed(ret);
        clear();
        setPlainText("");
        update();
    } else {
        QTextEdit::keyPressEvent(e);
    }
}