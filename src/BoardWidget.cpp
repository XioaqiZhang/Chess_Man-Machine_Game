#include "BoardWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <algorithm>

static QColor pieceColor(BYTE id) {
    if (IsRed(id)) return QColor(200, 0, 0);
    if (IsBlack(id)) return QColor(20, 20, 20);
    return QColor(0, 0, 0);
}

static QString pieceText(BYTE id) {
    switch (id) {
    case R_KING: return "帅";
    case R_CAR: return "车";
    case R_HORSE: return "马";
    case R_CANNON: return "炮";
    case R_BISHOP: return "仕";
    case R_ELEPHANT: return "相";
    case R_PAWN: return "兵";
    case B_KING: return "将";
    case B_CAR: return "車";
    case B_HORSE: return "馬";
    case B_CANNON: return "炮";
    case B_BISHOP: return "士";
    case B_ELEPHANT: return "象";
    case B_PAWN: return "卒";
    default: return "";
    }
}

BoardWidget::BoardWidget(GameState* state, QWidget* parent)
    : QWidget(parent), m_state(state) {}

void BoardWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const int cols = 9, rows = 10;
    const int margin = 20;
    int w = width() - 2*margin;
    int h = height() - 2*margin;
    int cw = w / (cols - 1);
    int ch = h / (rows - 1);

    // Draw grid
    p.translate(margin, margin);
    p.setPen(QPen(Qt::black, 2));
    for (int y = 0; y < rows; ++y) {
        p.drawLine(0, y*ch, (cols-1)*cw, y*ch);
    }
    for (int x = 0; x < cols; ++x) {
        if (x == 0 || x == cols-1) {
            p.drawLine(x*cw, 0, x*cw, (rows-1)*ch);
        } else {
            // river gap between rows 4 and 5
            p.drawLine(x*cw, 0, x*cw, 4*ch);
            p.drawLine(x*cw, 5*ch, x*cw, (rows-1)*ch);
        }
    }

    // Draw pieces
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            BYTE id = m_state->board()[y][x];
            if (id == NOTHING) continue;
            QRect r = cellRect(x, y);
            p.setBrush(Qt::white);
            p.setPen(QPen(pieceColor(id), 2));
            p.drawEllipse(r);
            p.setPen(pieceColor(id));
            p.setFont(QFont("WenQuanYi Zen Hei", int(r.height()*0.4)));
            p.drawText(r, Qt::AlignCenter, pieceText(id));
        }
    }

    // selected highlight
    if (m_selected.x() >= 0) {
        QRect r = cellRect(m_selected.x(), m_selected.y());
        p.setPen(QPen(Qt::blue, 2, Qt::DashLine));
        p.setBrush(Qt::NoBrush);
        p.drawEllipse(r.adjusted(-3, -3, 3, 3));
    }
}

QPoint BoardWidget::toCell(const QPoint& pos) const {
    const int cols = 9, rows = 10, margin = 20;
    int w = width() - 2*margin;
    int h = height() - 2*margin;
    int cw = w / (cols - 1);
    int ch = h / (rows - 1);

    QPoint p = pos - QPoint(margin, margin);
    int x = int((p.x() + cw/2) / cw);
    int y = int((p.y() + ch/2) / ch);
    if (x < 0 || x >= cols || y < 0 || y >= rows) return QPoint(-1, -1);
    return QPoint(x, y);
}

QRect BoardWidget::cellRect(int x, int y) const {
    const int cols = 9, rows = 10, margin = 20;
    int w = width() - 2*margin;
    int h = height() - 2*margin;
    int cw = w / (cols - 1);
    int ch = h / (rows - 1);
    // painter is translated by (margin, margin), so center is at (x*cw, y*ch)
    QPoint center(x*cw, y*ch);
    int r = int(std::min(cw, ch) * 0.35);
    return QRect(center.x()-r, center.y()-r, 2*r, 2*r);
}

void BoardWidget::mousePressEvent(QMouseEvent* event) {
    if (!m_state->started()) {
        return; // ignore clicks before start
    }
    // Only allow human (red) to move when it's red's turn
    if (!m_state->redTurn()) {
        return;
    }
    QPoint c = toCell(event->pos());
    if (c.x() < 0) return;

    if (m_selected.x() < 0) {
        // select a piece if any and side matches
        BYTE id = m_state->board()[c.y()][c.x()];
        if (id != NOTHING && ((m_state->redTurn() && IsRed(id)) || (!m_state->redTurn() && IsBlack(id)))) {
            m_selected = c;
            update();
        }
    } else {
        // attempt move
        if (m_state->tryMove(m_selected.x(), m_selected.y(), c.x(), c.y())) {
            m_selected = QPoint(-1, -1);
            update();
            emit playerMoved();
        } else {
            // reselect
            BYTE id = m_state->board()[c.y()][c.x()];
            if (id != NOTHING && ((m_state->redTurn() && IsRed(id)) || (!m_state->redTurn() && IsBlack(id))))
                m_selected = c;
            else
                m_selected = QPoint(-1, -1);
            update();
        }
    }
}
