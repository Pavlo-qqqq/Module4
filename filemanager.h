/*#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QStringList>

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr);

    QStringList loadNotes(); // Метод для завантаження нотаток з файлу
    void saveNotes(const QStringList &notesData); // Метод для збереження нотаток у файл

private:
    QString m_filePath; // Шлях до файлу, де зберігаються нотатки
};

#endif // FILEMANAGER_H
*/
