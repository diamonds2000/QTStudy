#include "trianglation.h"


QPoint Triangle::calculateCircle()
{
    // Using the formula for circumcenter of a triangle
    double D = 2 * (p1.x() * (p2.y() - p3.y()) + p2.x() * (p3.y() - p1.y()) + p3.x() * (p1.y() - p2.y()));
    if (D == 0) {
        // Points are collinear; circumcenter is undefined
        return QPoint();
    }

    double Ux = ((p1.x()*p1.x() + p1.y()*p1.y()) * (p2.y() - p3.y()) +
                 (p2.x()*p2.x() + p2.y()*p2.y()) * (p3.y() - p1.y()) +
                 (p3.x()*p3.x() + p3.y()*p3.y()) * (p1.y() - p2.y())) / D;

    double Uy = ((p1.x()*p1.x() + p1.y()*p1.y()) * (p3.x() - p2.x()) +
                 (p2.x()*p2.x() + p2.y()*p2.y()) * (p1.x() - p3.x()) +
                 (p3.x()*p3.x() + p3.y()*p3.y()) * (p2.x() - p1.x())) / D;

    circumcenter = QPoint(static_cast<int>(Ux), static_cast<int>(Uy));
    radius = std::hypot(circumcenter.x() - p1.x(), circumcenter.y() - p1.y());

    return circumcenter;
}


Trianglation::Trianglation(const QVector<QPoint>& points)
    : m_points(points)
{
}

Trianglation::~Trianglation()
{
}

void Trianglation::getTrianglePoints(QVector<QPoint>& points)
{
    points.clear();
    points.reserve(m_triangles.size() * 3);

    for (const auto& triangle : m_triangles) 
    {
        points.push_back(triangle.p1);
        points.push_back(triangle.p2);
        points.push_back(triangle.p3);
    }
}

void Trianglation::stepForward()
{
    if (m_points.size() < 3)
        return;

    for (qsizetype i = 0; i < m_points.size(); i ++)
    {
        if (i + 2 >= m_points.size())
            break;
        
        Triangle triangle(
            m_points[i + 0],
            m_points[i + 1],
            m_points[i + 2]
        );

        m_triangles.push_back(triangle);
    }
}

