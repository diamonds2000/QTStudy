#include "drawview.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>

DrawView::DrawView(QWidget *parent)
    : QWidget(parent)
    , m_drawing(false)
{
    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void DrawView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_points.append(event->pos());
        m_drawing = true;
    }
}

void DrawView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_drawing && (event->buttons() & Qt::LeftButton)) {
        m_points.append(event->pos());
        update();
    }
}

void DrawView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    
    for (int i = 1; i < m_points.size(); i++) {
        painter.drawLine(m_points[i-1], m_points[i]);
    }
    
    QWidget::paintEvent(event);
}