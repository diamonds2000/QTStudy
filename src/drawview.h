#ifndef DRAWVIEW_H
#define DRAWVIEW_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPoint>
#include <QVector>

class DrawView : public QWidget
{
    Q_OBJECT

public:
    explicit DrawView(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QPoint> m_points;
    bool m_drawing;
};

#endif // DRAWVIEW_H