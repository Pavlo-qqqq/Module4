#include "mainwindow.h"
#include "note.h"
#include "calendarwindow.h"
#include <QResizeEvent>
#include <QMessageBox>
#include <QInputDialog>
#include <QDialogButtonBox>
#include <QApplication>
#include <QFileDialog>
#include <QStandardPaths>
#include <QScrollArea>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), notesList(), addNoteButton(new QPushButton("Add Note")),
    loadFromFileButton(new QPushButton("Load from File")), saveToFileButton(new QPushButton("Save to File")),
    calendarWindow(new CalendarWindow(this)), openCalendarButton(new QPushButton("Open Calendar")) {

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QScrollArea *scrollArea = new QScrollArea(centralWidget);
    QWidget *scrollWidget = new QWidget();
    notesLayout = new QGridLayout(scrollWidget);
    scrollWidget->setLayout(notesLayout);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollWidget);

    mainLayout->addWidget(scrollArea);

    mainLayout->addWidget(addNoteButton);
    mainLayout->addWidget(loadFromFileButton);
    mainLayout->addWidget(saveToFileButton);
    mainLayout->addWidget(openCalendarButton);

    connect(openCalendarButton, &QPushButton::clicked, this, [=]() { calendarWindow->show(); });
    connect(calendarWindow, &CalendarWindow::dateSelected, this, &MainWindow::handleDateSelection);

    connect(addNoteButton, &QPushButton::clicked, this, &MainWindow::addNote);
    connect(loadFromFileButton, &QPushButton::clicked, this, [=]() { loadFromFile(QString()); });
    connect(saveToFileButton, &QPushButton::clicked, this, [=]() { saveToFile(QString()); });

    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString filePath = documentsPath + "/notes.txt";

    QFile file(filePath);
    if (!file.exists()) {
        file.open(QIODevice::WriteOnly);
        file.close();
    }
    loadFromFile(QString(filePath));

    QPushButton *showAllNotesButton = new QPushButton("Show All Notes", this);
    mainLayout->addWidget(showAllNotesButton);
    connect(showAllNotesButton, &QPushButton::clicked, [=]() {
        for (Note* note : notesList) {
            note->setVisible(true);
        }
        std::sort(notesList.begin(), notesList.end(), compareNotesByDate);
        refreshNotesDisplay();
    });

}

MainWindow::~MainWindow() {
    for (Note *note : notesList) {
        delete note;
    }
    notesList.clear();

    delete notesLayout;
    delete addNoteButton;
    delete loadFromFileButton;
    delete saveToFileButton;
}

void MainWindow::addNote() {
    if (!calendarWindow->isVisible()) {
        setSelectedDate(QDate());
        QString date = selectedDate.toString("dd.MM.yyyy");
        Note* newNote = new Note(date + "\n");
        createNoteWidget(newNote);
        notesList.append(newNote);
        std::sort(notesList.begin(), notesList.end(), compareNotesByDate);
        refreshNotesDisplay();
    }
    else{
        QString date = selectedDate.toString("dd.MM.yyyy");
        Note* newNote = new Note(date + "\n");
        createNoteWidget(newNote);
        notesList.append(newNote);
        std::sort(notesList.begin(), notesList.end(), compareNotesByDate);
        arrangeWidgetsInGridLayout();
    }
}

void MainWindow::editNote() {
    Note *note = qobject_cast<Note*>(sender());
    if (note) {
        bool ok;
        QInputDialog dialog;
        dialog.setInputMode(QInputDialog::TextInput);
        dialog.setLabelText("Edit your note:");
        dialog.setTextValue(note->getContent());
        dialog.setTextValue(note->getContent());
        dialog.setOption(QInputDialog::UsePlainTextEditForTextInput);

        if (dialog.exec() == QInputDialog::Accepted) {
            QString newText = dialog.textValue();
            if (!newText.isEmpty()) {
                note->setContent(newText);
            }
        }
    }
    std::sort(notesList.begin(), notesList.end(), compareNotesByDate);
    refreshNotesDisplay();
}

void MainWindow::deleteNote() {
    Note *note = qobject_cast<Note *>(sender());
    if (note) {
        notesList.removeOne(note);
        notesLayout->removeWidget(note);
        note->deleteLater();
        arrangeWidgetsInGridLayout();
    }
}

void MainWindow::showNote() {
    Note *note = qobject_cast<Note*>(sender());

    QString content = note->getContent();

    QDialog *dialog = new QDialog();
    QVBoxLayout *dialogLayout = new QVBoxLayout(dialog);
    QTextEdit *contentTextEdit = new QTextEdit(dialog);
    contentTextEdit->setText(content);
    contentTextEdit->setReadOnly(true);
    dialogLayout->addWidget(contentTextEdit);

    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowStaysOnTopHint | Qt::WindowMinimizeButtonHint);

    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void MainWindow::loadFromFile(const QString& PathToFile) {
    QString filePath = PathToFile;
    if (filePath.isEmpty()) {
        filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt)"));
        if (filePath.isEmpty()) {
            return;
        }
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);

    bool shouldCreateNewNote = true;

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line == ".") {
            shouldCreateNewNote = true;
            continue;
        }

        if (shouldCreateNewNote) {
            Note *newNote = new Note(line);
            notesList.append(newNote);
            createNoteWidget(newNote);
            shouldCreateNewNote = false;
        } else {
            Note *currentNote = notesList.last();
            currentNote->setContent(currentNote->getContent() + "\n" + line);
        }
    }
    std::sort(notesList.begin(), notesList.end(), compareNotesByDate);
    refreshNotesDisplay();
    file.close();
}

void MainWindow::saveToFile(const QString& PathToFile) {
    QString filePath = PathToFile;
    if (filePath.isEmpty()) {
        filePath = QFileDialog::getSaveFileName(this, tr("Save Text File"), "", tr("Text Files (*.txt)"));
        if (filePath.isEmpty()) {
            return;
        }
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open the file for writing";
        return;
    }

    QTextStream out(&file);
    for (Note *note : notesList) {
        out << note->getContent() << "\n" << "." << "\n";
    }

    file.close();
}

void MainWindow::openCalendar() {
    CalendarWindow *calendarWindow = new CalendarWindow(this);
    calendarWindow->show();
}

void MainWindow::handleDateSelection(const QDate& date) {
    setSelectedDate(date);

    QList<Note*> notesToShow;
    for (Note* note : notesList) {
        QString noteDate = note->getContent().split("\n").first();
        QDateTime dateTime = QDateTime::fromString(noteDate, "dd.MM.yyyy");

        if (dateTime.date() == date) {
            notesToShow.append(note);
        }
    }

    int row = 0;
    int col = 0;
    for (Note* note : notesList) {
        if (notesToShow.contains(note)) {
            notesLayout->addWidget(note, row, col);
            note->setVisible(true);
            ++col;
            if (col == 5) {
                col = 0;
                ++row;
            }
        } else {
            notesLayout->removeWidget(note);
            note->setVisible(false);
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    arrangeWidgetsInGridLayout();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString filePath = documentsPath + "/notes.txt";
    saveToFile(QString(filePath));
    event->accept();
}

void MainWindow::createNoteWidget(Note *note) {
    connect(note, &Note::editRequested, this, &MainWindow::editNote);
    connect(note, &Note::deleteRequested, this, &MainWindow::deleteNote);
    connect(note, &Note::showRequested, this, &MainWindow::showNote);

    int row = notesLayout->count() / 5;
    int col = notesLayout->count() % 5;

    notesLayout->addWidget(note, row, col);
}

void MainWindow::setSelectedDate(const QDate& date) {
    selectedDate = date;
}

bool MainWindow::compareNotesByDate(Note *a, Note *b) {
    QString dateA = a->getContent().split("\n").first();
    QString dateB = b->getContent().split("\n").first();

    if (dateA.isEmpty() && dateB.isEmpty()) {
        return false;
    } else if (dateA.isEmpty()) {
        return true;
    } else if (dateB.isEmpty()) {
        return false;
    }

    QDateTime dateTimeA = QDateTime::fromString(dateA, "dd.MM.yyyy");
    QDateTime dateTimeB = QDateTime::fromString(dateB, "dd.MM.yyyy");

    return dateTimeA < dateTimeB;
}

void MainWindow::refreshNotesDisplay() {
    int row = 0;
    int col = 0;
    for (Note *note : notesList) {
        notesLayout->addWidget(note, row, col);
        col++;
        if (col == 5) {
            col = 0;
            row++;
        }
    }
}

void MainWindow::arrangeWidgetsInGridLayout() {
    int columnCount = 5;
    int row = 0;
    int col = 0;

    for (int i = 0; i < notesList.size(); ++i) {
        if (notesList[i]->isVisible()) {
            notesLayout->addWidget(notesList[i], row, col);
            ++col;
            if (col == columnCount) {
                col = 0;
                ++row;
            }
        }
    }
}

