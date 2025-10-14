#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BoardWidget.h"
#include "GameState.h"

class QPushButton;
class QLabel;
class QWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void onPlayerMoved();
    void onStart();
    void onReset();

private:
    GameState m_state;
    BoardWidget* m_board{nullptr};
    QWidget* m_container{nullptr};
    QWidget* m_sidePanel{nullptr};
    QPushButton* m_startBtn{nullptr};
    QPushButton* m_resetBtn{nullptr};
    QLabel* m_statusLabel{nullptr};
};

#endif // MAINWINDOW_H
