#ifndef CALENDARWINDOW_H
#define CALENDARWINDOW_H

#include <QDialog>
#include <QCalendarWidget>

class CalendarWindow : public QDialog {
    Q_OBJECT

public:
    explicit CalendarWindow(QWidget *parent = nullptr);

signals:
    void dateSelected(const QDate& date);

private slots:
    void dateClicked(const QDate &date);

private:
    QCalendarWidget *calendarWidget;
};


#endif // CALENDARWINDOW_H
