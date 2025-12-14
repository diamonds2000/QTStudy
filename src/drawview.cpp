#include "drawview.h"
#include "trianglation.h"

#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPalette>

DrawView::DrawView(QWidget *parent)
    : QWidget(parent)
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
    if (event->button() == Qt::LeftButton) 
    {
        m_Points.append(event->pos());
    }
}

void DrawView::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    update();
}

void DrawView::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
}

void DrawView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    
    for (const QPoint& point : m_Points) 
    {
        painter.drawPoint(point);
    }

    if (m_trianglation)
    {
        QVector<QPoint> trianglePoints;
        m_trianglation->getTrianglePoints(trianglePoints);

        painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        for (int i = 0; i + 2 < trianglePoints.size(); i += 3)
        {
            painter.drawLine(trianglePoints[i + 0], trianglePoints[i + 1]);
            painter.drawLine(trianglePoints[i + 1], trianglePoints[i + 2]);
            painter.drawLine(trianglePoints[i + 2], trianglePoints[i + 0]);
        }
    }
    
    QWidget::paintEvent(event);
}


void DrawView::reset()
{
    m_Points.clear();
    delete m_trianglation;
    m_trianglation = nullptr;

    update();
}

void DrawView::stepForward()
{
    if (!m_trianglation)
    {
        m_trianglation = new Trianglation(m_Points);
    }

    m_trianglation->stepForward();
    
    update();
}