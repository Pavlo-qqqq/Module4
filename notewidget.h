/*#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include "note.h"

class NoteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NoteWidget(Note *note, QWidget *parent = nullptr);
    ~NoteWidget();

signals:
    void editRequested();
    void deleteRequested();

private:
    Note *m_note;
    QTextEdit *m_titleTextEdit;
    QPushButton *m_editButton;
    QPushButton *m_deleteButton;

    void setupUI();
};

#endif // NOTEWIDGET_H
*/
