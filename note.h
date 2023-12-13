#ifndef NOTE_H
#define NOTE_H

#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>

class Note : public QWidget {
    Q_OBJECT

public:
    explicit Note(const QString& text = "", QWidget* parent = nullptr);

    QString getContent() const;
    void setContent(const QString& content);

signals:
    void editRequested();
    void deleteRequested();
    void showRequested();

private:
    QPlainTextEdit* contentTextEdit;
    QPushButton* editButton;
    QPushButton* deleteButton;
    QPushButton* showButton;

    void setupUI();
};

#endif // NOTE_H
