#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QStandardPaths>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_newGameButton_clicked();
    void on_checkButton_clicked();
    void on_gameMenuButton_clicked();
    void on_recordsMenuButton_clicked();

private:
    Ui::MainWindow *ui;
    QStringList wordList;
    QString currentWord;
    int attemptsLeft;
    int totalScore;
    bool gameActive;
    QMap<int, int> scoreTable; // Таблица баллов

    void loadWordList();
    void startNewGame();
    void endGame();
    void checkGuess(const QString &guess);
    void updateLog(const QString &message);
    void saveScore(int score);
    void loadRecords();
    void updateRecordsDisplay();
    QString maskWord(const QString &word, const QString &guess);
    QString getScoresFilePath();
    void ensureScoresFileExists();
    void initializeScoreTable();
};
#endif // MAINWINDOW_H
