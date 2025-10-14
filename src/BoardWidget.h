#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include "GameState.h"

class BoardWidget : public QWidget {
    Q_OBJECT
public:
    explicit BoardWidget(GameState* state, QWidget* parent = nullptr);

    QSize sizeHint() const override { return QSize(540, 600); }

signals:
    void playerMoved();

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    QPoint toCell(const QPoint& pos) const;
    QRect cellRect(int x, int y) const;

    GameState* m_state;
    QPoint m_selected{-1, -1};
};

#endif // BOARDWIDGET_H
