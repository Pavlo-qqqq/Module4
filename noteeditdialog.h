/*#ifndef NOTEEDITDIALOG_H
#define NOTEEDITDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

class NoteEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NoteEditDialog(QWidget *parent = nullptr);
    ~NoteEditDialog();

    QString getTitle() const;
    QString getContent() const;

    void setTitle(const QString &title);
    void setContent(const QString &content);

private:
    QLineEdit *titleLineEdit;
    QTextEdit *contentTextEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUI();
};

#endif // NOTEEDITDIALOG_H
*/
