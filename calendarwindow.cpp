#include "calendarwindow.h"
#include <QVBoxLayout>

CalendarWindow::CalendarWindow(QWidget *parent) : QDialog(parent) {
    calendarWidget = new QCalendarWidget(this);
    setWindowTitle("Calendar");
    setFixedSize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(calendarWidget);

    connect(calendarWidget, &QCalendarWidget::clicked, this, &CalendarWindow::dateClicked);
}

void CalendarWindow::dateClicked(const QDate &date) {
        emit dateSelected(date);
}

