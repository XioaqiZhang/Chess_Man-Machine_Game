#include "MainWindow.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Xiangqi - Qt5");

    // Central layout: board + side panel
    m_container = new QWidget(this);
    auto* hLayout = new QHBoxLayout(m_container);
    hLayout->setContentsMargins(8, 8, 8, 8);
    hLayout->setSpacing(12);

    m_board = new BoardWidget(&m_state, m_container);
    hLayout->addWidget(m_board, /*stretch*/ 1);

    m_sidePanel = new QWidget(m_container);
    auto* vLayout = new QVBoxLayout(m_sidePanel);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(8);

    m_statusLabel = new QLabel(tr("Ready"), m_sidePanel);
    m_statusLabel->setWordWrap(true);

    m_startBtn = new QPushButton(tr("Start"), m_sidePanel);
    m_resetBtn = new QPushButton(tr("Reset"), m_sidePanel);

    vLayout->addWidget(m_statusLabel);
    vLayout->addSpacing(8);
    vLayout->addWidget(m_startBtn);
    vLayout->addWidget(m_resetBtn);
    vLayout->addStretch(1);

    hLayout->addWidget(m_sidePanel);

    setCentralWidget(m_container);
    connect(m_board, &BoardWidget::playerMoved, this, &MainWindow::onPlayerMoved);

    auto gameMenu = menuBar()->addMenu(tr("Game"));
    auto startAct = gameMenu->addAction(tr("Start"));
    auto resetAct = gameMenu->addAction(tr("Reset"));
    connect(startAct, &QAction::triggered, this, &MainWindow::onStart);
    connect(resetAct, &QAction::triggered, this, &MainWindow::onReset);
    connect(m_startBtn, &QPushButton::clicked, this, &MainWindow::onStart);
    connect(m_resetBtn, &QPushButton::clicked, this, &MainWindow::onReset);

    statusBar()->showMessage("Click Start to begin");
    m_statusLabel->setText(tr("Click Start to begin"));
}

void MainWindow::onPlayerMoved() {
    if (!m_state.started()) return;
    // Player (red) just moved; now it's black's turn, show thinking status
    statusBar()->showMessage("Black thinking…");
    m_statusLabel->setText(tr("Black thinking…"));
    m_board->setEnabled(false);

    // If game already ended by this move, announce and stop
    {
        int result = m_state.checkGameOver();
        if (result != 0) {
            m_board->update();
            m_state.stop();
            QString text = result > 0 ? tr("Red wins!") : tr("Black wins!");
            statusBar()->showMessage(text);
            m_statusLabel->setText(text);
            QMessageBox::information(this, tr("Game Over"), text);
            m_board->setEnabled(false);
            return;
        }
    }

    // Let AI respond for the other side after the UI has a chance to update
    QTimer::singleShot(0, this, [this]() {
        m_state.aiMove();
        m_board->update();
        m_board->setEnabled(true);

        // After AI moves, back to red
        int result = m_state.checkGameOver();
        if (result != 0) {
            m_state.stop();
            QString text = result > 0 ? tr("Red wins!") : tr("Black wins!");
            statusBar()->showMessage(text);
            m_statusLabel->setText(text);
            QMessageBox::information(this, tr("Game Over"), text);
            m_board->setEnabled(false);
            return;
        }

        auto msg = m_state.redTurn() ? tr("Red to move") : tr("Black to move");
        statusBar()->showMessage(msg);
        m_statusLabel->setText(msg);
    });
}

void MainWindow::onStart() {
    m_state.reset();
    m_state.start();
    m_board->update();
    statusBar()->showMessage("Red to move");
    m_statusLabel->setText(tr("Red to move"));
}

void MainWindow::onReset() {
    m_state.reset();
    m_state.stop();
    m_board->update();
    statusBar()->showMessage("Click Start to begin");
    m_statusLabel->setText(tr("Click Start to begin"));
}
