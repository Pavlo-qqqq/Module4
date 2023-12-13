/*#ifndef DATENOTESWINDOW_H
#define DATENOTESWINDOW_H

#include <QDialog>
#include <QTextEdit>
#include <QPushButton>
#include <QDate>

class DateNotesWindow : public QDialog {
    Q_OBJECT

public:
    explicit DateNotesWindow(const QString &notes, const QDate& date, QWidget *parent = nullptr);

private slots:
    void addNoteForDate();
    void loadNotesForDate();

private:
    QTextEdit *notesDisplay;
    QTextEdit *newNoteEdit;
    QPushButton *addNoteButton;
    QPushButton *loadNotesButton;

    QDate selectedDate;
};

#endif // DATENOTESWINDOW_H

*/
