#ifndef DRAWVIEW_H
#define DRAWVIEW_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPoint>
#include <QVector>
#include <QList>

class Trianglation;

class DrawView : public QWidget
{
    Q_OBJECT

public:
    explicit DrawView(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

public slots:
    void reset();
    void stepForward();

private:
    QVector<QPoint> m_Points;

    Trianglation *m_trianglation = nullptr;
};

#endif // DRAWVIEW_H