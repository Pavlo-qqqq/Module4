#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QList>
#include "note.h"
#include "calendarwindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addNote();
    void editNote();
    void deleteNote();
    void showNote();

    void loadFromFile(const QString&);
    void saveToFile(const QString&);
    void openCalendar();
    void handleDateSelection(const QDate& date);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    void createNoteWidget(Note *note);
    void setSelectedDate(const QDate& date);
    static bool compareNotesByDate(Note *a, Note *b);
    void refreshNotesDisplay();
    void arrangeWidgetsInGridLayout();

    QGridLayout *notesLayout;
    QList<Note *> notesList;
    QPushButton *addNoteButton;
    QPushButton *loadFromFileButton;
    QPushButton *saveToFileButton;
    QPushButton *openCalendarButton;
    CalendarWindow *calendarWindow;
    QDate selectedDate;
};


#endif // MAINWINDOW_H
