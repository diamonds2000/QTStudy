#include "drawview.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPalette>

DrawView::DrawView(QWidget *parent)
    : QWidget(parent)
    , m_drawing(false)
{
    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    // Set light grey background color
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::lightGray);
    setAutoFillBackground(true);
    setPalette(palette);
}

void DrawView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_currentPoints.append(event->pos());
        m_drawing = true;
    }
}

void DrawView::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_drawing) 
    {
        if (!m_currentPoints.isEmpty())
        {
            m_pointsList.append(m_currentPoints);
            m_currentPoints.clear();
        }
        
        m_drawing = false;
    }
}

void DrawView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_drawing && (event->buttons() & Qt::LeftButton)) {
        m_currentPoints.append(event->pos());
        update();
    }
}

void DrawView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    
    for (auto points : m_pointsList) 
    {
        for (int i = 1; i < points.size(); i++) 
        {
            painter.drawLine(points[i - 1], points[i]);
        }
    }

    for (int i = 1; i < m_currentPoints.size(); i++)
    {
        painter.drawLine(m_currentPoints[i - 1], m_currentPoints[i]);
    }
    
    QWidget::paintEvent(event);
}