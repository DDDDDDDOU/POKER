#include "Console.h"
#include <QKeyEvent>
#include <QTextLine>
#include <QTextCursor>
#include <WordListWidget.h>
#include <lexicon.h>
#include <BoggleWindow.h>
Console::Console(QWidget *parent) : QTextEdit(parent)
{
    this->setMouseTracking(true);
}

void Console::clear()
{
    this->clear();
}

void Console::write(QString msg)
{
    this->append(msg);
}

void Console::keyPressEvent(QKeyEvent *event)
{

    if (this->textCursor().hasSelection())
        return;
    if (event->key() == Qt::Key_Return) {
        QTextCursor cursor = this->textCursor();
        cursor.movePosition(QTextCursor::End);
        cursor.select(QTextCursor::LineUnderCursor);
        QString lastLine = cursor.selectedText();
        line = lastLine;
        emit newLineWritten(lastLine);

    }
    QTextEdit::keyPressEvent(event);
}
