/*#include "noteeditdialog.h"
#include <QVBoxLayout>
#include <QLabel>

NoteEditDialog::NoteEditDialog(QWidget *parent) : QDialog(parent)
{
    setupUI();
}

NoteEditDialog::~NoteEditDialog()
{
    // Destructor
}

void NoteEditDialog::setupUI()
{
    titleLineEdit = new QLineEdit(this);
    contentTextEdit = new QTextEdit(this);
    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Title:", this));
    layout->addWidget(titleLineEdit);
    layout->addWidget(new QLabel("Content:", this));
    layout->addWidget(contentTextEdit);
    layout->addWidget(okButton);
    layout->addWidget(cancelButton);

    connect(okButton, &QPushButton::clicked, this, &NoteEditDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &NoteEditDialog::reject);
}

QString NoteEditDialog::getTitle() const
{
    return titleLineEdit->text();
}

QString NoteEditDialog::getContent() const
{
    return contentTextEdit->toPlainText();
}

void NoteEditDialog::setTitle(const QString &title)
{
    titleLineEdit->setText(title);
}

void NoteEditDialog::setContent(const QString &content)
{
    contentTextEdit->setPlainText(content);
}
*/
