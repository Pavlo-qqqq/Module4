#include "note.h"
#include <QVBoxLayout>

Note::Note(const QString& text, QWidget* parent) : QWidget(parent) {
    setupUI();
    setContent(text);
    setMinimumSize(75, 300);
}

void Note::setupUI() {
    contentTextEdit = new QPlainTextEdit(this);
    contentTextEdit->setReadOnly(true);

    editButton = new QPushButton("Edit", this);
    deleteButton = new QPushButton("Delete", this);
    showButton = new QPushButton("Show", this);//
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(contentTextEdit);
    layout->addWidget(editButton);
    layout->addWidget(deleteButton);
    layout->addWidget(showButton);//

    connect(editButton, &QPushButton::clicked, this, &Note::editRequested);
    connect(deleteButton, &QPushButton::clicked, this, &Note::deleteRequested);
    connect(showButton, &QPushButton::clicked, this, &Note::showRequested);//
}

QString Note::getContent() const {
    return contentTextEdit->toPlainText();
}

void Note::setContent(const QString& content) {
    contentTextEdit->setPlainText(content);
}
