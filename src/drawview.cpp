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
        QVector<QVector2D> trianglePoints;
        m_trianglation->getTrianglePoints(trianglePoints);

        painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        for (int i = 0; i + 2 < trianglePoints.size(); i += 3)
        {
            QPoint pt1(static_cast<int>(trianglePoints[i + 0].x() + 0.5), static_cast<int>(trianglePoints[i + 0].y() + 0.5));
            QPoint pt2(static_cast<int>(trianglePoints[i + 1].x() + 0.5), static_cast<int>(trianglePoints[i + 1].y() + 0.5));
            QPoint pt3(static_cast<int>(trianglePoints[i + 2].x() + 0.5), static_cast<int>(trianglePoints[i + 2].y() + 0.5));
            painter.drawLine(pt1, pt2);
            painter.drawLine(pt2, pt3);
            painter.drawLine(pt3, pt1);

            painter.drawEllipse(pt1, 2, 2);
        }

        // draw circumcircles
        QVector<QVector2D> centers;
        QVector<double> radii;
        m_trianglation->getCircumCirclePoints(centers, radii);
        painter.setPen(QPen(Qt::red, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
        for (int i = 0; i < centers.size(); ++i)
        {
            QPoint center(static_cast<int>(centers[i].x() + 0.5), static_cast<int>(centers[i].y() + 0.5));
            int radius = static_cast<int>(radii[i] + 0.5);
            painter.drawEllipse(center, radius, radius);
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
        QVector<QVector2D> points2D;
        points2D.reserve(m_Points.size());
        for (const QPoint& pt : m_Points)
        {
            points2D.append(QVector2D(pt));
        }

        m_trianglation = new Trianglation(points2D);
    }

    m_trianglation->stepForward();
    
    update();
}