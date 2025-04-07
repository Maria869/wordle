#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>
#include <QDebug>
#include <QRegularExpression>
#include <QRandomGenerator>
#include <QStandardPaths>
#include <QDir>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Инициализация
    gameActive = false;
    totalScore = 0;
    attemptsLeft = 0;

    // Загрузка списка слов
    loadWordList();

    // Настройка интерфейса
    ui->inputField->setEnabled(false);
    ui->checkButton->setEnabled(false);
    ui->recordsMenuButton->setChecked(false);
    ui->gameMenuButton->setChecked(true);
    ui->stackedWidget->setCurrentIndex(0);

    // Инициализация системы рекордов
    ensureScoresFileExists();
    loadRecords();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getScoresFilePath()
{
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString scoresPath = documentsPath + "/WordleGame";

    // Создаем папку, если не существует
    QDir dir;
    if (!dir.exists(scoresPath)) {
        dir.mkpath(scoresPath);
    }

    return scoresPath + "/scores.txt";
}

void MainWindow::ensureScoresFileExists()
{
    QString filePath = getScoresFilePath();
    if (!QFile::exists(filePath)) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly)) {
            file.close();
            qDebug() << "Created new scores file:" << filePath;
        } else {
            qDebug() << "Failed to create scores file:" << file.errorString();
        }
    }
}

void MainWindow::loadWordList()
{
    wordList << "барс" << "рука" << "лось" << "нога" << "перо"
            << "море" << "зима";
}

void MainWindow::startNewGame()
{
    if (wordList.isEmpty()) {
        updateLog("Ошибка: список слов пуст!");
        return;
    }

    currentWord = wordList.at(QRandomGenerator::global()->bounded(wordList.size()));
    attemptsLeft = 5;
    gameActive = true;

    ui->inputField->setEnabled(true);
    ui->checkButton->setEnabled(true);
    ui->inputField->clear();
    ui->inputField->setFocus();

    updateLog("Загаданное слово: ****");
    updateLog("У вас 5 попыток. Введите слово:");
}

void MainWindow::endGame()
{
    gameActive = false;
    ui->inputField->setEnabled(false);
    ui->checkButton->setEnabled(false);
}

void MainWindow::checkGuess(const QString &guess)
{
    if (!gameActive) return;

    QString cleanGuess = guess.toLower().trimmed();

    if (cleanGuess.length() != 4) {
        updateLog("Слово должно быть длиной 4 буквы!");
        return;
    }

    QRegularExpression re("^[а-яё]+$");
    if (!re.match(cleanGuess).hasMatch()) {
        updateLog("Пожалуйста, используйте только русские буквы!");
        return;
    }

    attemptsLeft--;
    updateLog("Вы ввели: " + cleanGuess);

    if (cleanGuess == currentWord) {
        int score = 0;
        switch (5 - attemptsLeft) {
        case 1: score = 5; break;
        case 2: score = 4; break;
        case 3: score = 3; break;
        case 4: score = 2; break;
        case 5: score = 1; break;
        }

        totalScore += score;
        updateLog(QString("Вы отгадали слово и заработали %1 баллов. Желаете продолжить? (y/n)").arg(score));
        saveScore(totalScore);
        endGame();
    } else if (attemptsLeft <= 0) {
        updateLog(QString("Попытки закончились, игра окончена. Загаданное слово: %1. Ваш счет: %2 баллов").arg(currentWord).arg(totalScore));
        saveScore(totalScore);
        endGame();
    } else {
        QString matchedLetters;
        QString wordPattern = maskWord(currentWord, cleanGuess);

        for (int i = 0; i < cleanGuess.length(); ++i) {
            if (currentWord.contains(cleanGuess.at(i))) {
                if (!matchedLetters.contains(cleanGuess.at(i))) {
                    matchedLetters.append(cleanGuess.at(i)).append(", ");
                }
            }
        }

        if (!matchedLetters.isEmpty()) {
            matchedLetters.chop(2);
            updateLog("Отгаданные буквы: " + matchedLetters);
        } else {
            updateLog("Отгаданные буквы: -");
        }

        updateLog("Слово: " + wordPattern);
        updateLog(QString("Осталось попыток: %1").arg(attemptsLeft));
    }

    ui->inputField->clear();
}

void MainWindow::updateLog(const QString &message)
{
    ui->gameLog->append(message);
}

void MainWindow::saveScore(int score)
{
    if (score <= 0) return;

    QString filePath = getScoresFilePath();
    QFile file(filePath);

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")
            << " - " << score << " баллов\n";
        file.close();

        // Обновляем список рекордов после сохранения
        QTimer::singleShot(0, this, &MainWindow::loadRecords);
    } else {
        qDebug() << "Ошибка сохранения рекорда:" << file.errorString();
        updateLog("Ошибка сохранения результата!");
    }
}

void MainWindow::loadRecords()
{
    ui->recordsList->clear();
    QString filePath = getScoresFilePath();

    QFile file(filePath);
    if (!file.exists()) {
        ui->recordsList->addItem("Рекорды пока отсутствуют");
        return;
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QStringList records;

        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty()) {
                records.prepend(line); // Новые записи добавляем в начало
            }
        }
        file.close();

        if (records.isEmpty()) {
            ui->recordsList->addItem("Рекорды пока отсутствуют");
        } else {
            ui->recordsList->addItems(records);
        }
    } else {
        ui->recordsList->addItem("Ошибка загрузки рекордов");
        qDebug() << "Ошибка загрузки рекордов:" << file.errorString();
    }
}

QString MainWindow::maskWord(const QString &word, const QString &guess)
{
    QString result;
    for (int i = 0; i < word.length(); ++i) {
        if (i < guess.length() && word.at(i) == guess.at(i)) {
            result += word.at(i);
        } else {
            result += "_";
        }
        result += " ";
    }
    return result.trimmed();
}

void MainWindow::on_newGameButton_clicked()
{
    if (gameActive) {
        updateLog(QString("Игра прервана. Ваш счет: %1 баллов").arg(totalScore));
        saveScore(totalScore);
    }

    totalScore = 0;
    ui->gameLog->clear();
    startNewGame();
}

void MainWindow::on_checkButton_clicked()
{
    QString guess = ui->inputField->text();
    if (guess.isEmpty()) return;

    checkGuess(guess);
}

void MainWindow::on_gameMenuButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->gamePage);
    ui->gameMenuButton->setChecked(true);
    ui->recordsMenuButton->setChecked(false);
}

void MainWindow::on_recordsMenuButton_clicked()
{
    // Всегда обновляем список при открытии вкладки
    loadRecords();
    ui->stackedWidget->setCurrentWidget(ui->recordsPage);
    ui->recordsMenuButton->setChecked(true);
    ui->gameMenuButton->setChecked(false);
}
