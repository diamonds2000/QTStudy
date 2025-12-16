#include "trianglation.h"
#include <QMap>
#include <QPair>

Triangle::Triangle(qsizetype p1, qsizetype p2, qsizetype p3, const QVector2D* points)
    : p1(p1), p2(p2), p3(p3), m_points(const_cast<QVector2D*>(points))
{
}

QVector2D Triangle::calculateCircle()
{
    if (!m_points)
        return QVector2D();

    QVector2D p1 = m_points[this->p1];
    QVector2D p2 = m_points[this->p2];
    QVector2D p3 = m_points[this->p3];
    
    // Using the formula for circumcenter of a triangle
    double D = 2 * (p1.x() * (p2.y() - p3.y()) + p2.x() * (p3.y() - p1.y()) + p3.x() * (p1.y() - p2.y()));
    if (D == 0) {
        // Points are collinear; circumcenter is undefined
        return QVector2D();
    }

    double Ux = ((p1.x()*p1.x() + p1.y()*p1.y()) * (p2.y() - p3.y()) +
                 (p2.x()*p2.x() + p2.y()*p2.y()) * (p3.y() - p1.y()) +
                 (p3.x()*p3.x() + p3.y()*p3.y()) * (p1.y() - p2.y())) / D;

    double Uy = ((p1.x()*p1.x() + p1.y()*p1.y()) * (p3.x() - p2.x()) +
                 (p2.x()*p2.x() + p2.y()*p2.y()) * (p1.x() - p3.x()) +
                 (p3.x()*p3.x() + p3.y()*p3.y()) * (p2.x() - p1.x())) / D;

    circumcenter = QVector2D(static_cast<int>(Ux), static_cast<int>(Uy));
    radius = std::hypot(circumcenter.x() - p1.x(), circumcenter.y() - p1.y());

    return circumcenter;
}

void Triangle::getCircumCircle(QVector2D& center, double& radius)
{
    center = circumcenter;
    radius = this->radius;
}


Trianglation::Trianglation(const QVector<QVector2D>& points)
    : m_points(points)
{
}

Trianglation::~Trianglation()
{
}

void Trianglation::getTrianglePoints(QVector<QVector2D>& points)
{
    points.clear();
    points.reserve(m_triangles.size() * 3);

    for (const auto& triangle : m_triangles) 
    {
        points.push_back(m_points[triangle.p1]);
        points.push_back(m_points[triangle.p2]);
        points.push_back(m_points[triangle.p3]);
    }
}

void Trianglation::getCircumCirclePoints(QVector<QVector2D>& centers, QVector<double>& radii)
{
    centers.clear();
    radii.clear();
    centers.reserve(m_triangles.size());
    radii.reserve(m_triangles.size());

    for (const auto& triangle : m_triangles) 
    {
        centers.push_back(triangle.circumcenter);
        radii.push_back(triangle.radius);
    }
}

void Trianglation::stepForward()
{
    if (m_points.size() < 3)
        return;

    if (m_points.size() == 3)
    {
        m_triangles.clear();
        m_triangles.push_back(Triangle(0, 1, 2, m_points.data()));
        return;
    }

    if (m_triangles.isEmpty())
    {
        generateSuperTriangles();
        return;
    }

    // finished
    if (m_currentPointIndex >= m_points.size() - 4)  // the last 4 points are super triangle points
    {
        deleteSuperTriangles();
        return;
    }

    QVector2D pt = m_points[m_currentPointIndex];

    QVector<qsizetype> badTriangleIndices;
    badTriangleIndices.reserve(m_triangles.size());

    for (qsizetype i = 0; i < m_triangles.size(); i++)
    {
        QVector2D center;
        double radius;
        m_triangles[i].getCircumCircle(center, radius);

        if ((pt.x() - center.x()) * (pt.x() - center.x()) + (pt.y() - center.y()) * (pt.y() - center.y()) < radius * radius)
        {
            badTriangleIndices.push_back(i);
        }
    }

    QMap<QPair<qsizetype, qsizetype>, int> edgeCountMap;

    for (qsizetype index : badTriangleIndices)
    {
        const Triangle& triangle = m_triangles[index];
        QPair<qsizetype, qsizetype> edges[3] = {
            qMakePair(std::min(triangle.p1, triangle.p2), std::max(triangle.p1, triangle.p2)),
            qMakePair(std::min(triangle.p2, triangle.p3), std::max(triangle.p2, triangle.p3)),
            qMakePair(std::min(triangle.p3, triangle.p1), std::max(triangle.p3, triangle.p1))
        };

        for (const auto& edge : edges)
        {
            edgeCountMap[edge] += 1;
        }
    }

    for (qsizetype i = badTriangleIndices.size() - 1; i >= 0; i--)
    {
        m_triangles.removeAt(badTriangleIndices[i]);
    }

    for (auto edge = edgeCountMap.begin(); edge != edgeCountMap.end(); ++edge)
    {
        if (edge.value() == 1)
        {
            addTriangle(edge.key().first, edge.key().second, m_currentPointIndex);
        }
    }

    m_currentPointIndex++;
}

void Trianglation::addTriangle(qsizetype p1, qsizetype p2, qsizetype p3)
{
    Triangle triangle(p1, p2, p3, m_points.data());
    triangle.calculateCircle();
    m_triangles.push_back(triangle);
}

void Trianglation::generateSuperTriangles()
{
    if (m_points.size() < 3)
        return;

    QVector2D min(__DBL_MAX__, __DBL_MAX__);
    QVector2D max(-__DBL_MAX__, -__DBL_MAX__);
    for (qsizetype i = 0; i < m_points.size(); i++)
    {
        if (m_points[i].x() < min.x())
            min.setX(m_points[i].x());
        if (m_points[i].y() < min.y())
            min.setY(m_points[i].y());
        if (m_points[i].x() > max.x())
            max.setX(m_points[i].x());
        if (m_points[i].y() > max.y())
            max.setY(m_points[i].y());
    }

    min -= QVector2D(30.0, 30.0);
    max += QVector2D(30.0, 30.0);

    QVector2D p1 = QVector2D(min.x(), min.y());  //left-top
    QVector2D p2 = QVector2D(max.x(), min.y());  //right-top
    QVector2D p3 = QVector2D(max.x(), max.y() + 30);  //right-bottom, +30 to avoid cocircular
    QVector2D p4 = QVector2D(min.x(), max.y());  //left-bottom

    qsizetype baseIndex = m_points.size();

    m_points.push_back(p1);
    m_points.push_back(p2);
    m_points.push_back(p3);
    m_points.push_back(p4);

    addTriangle(baseIndex + 0, baseIndex + 1, baseIndex + 3);
    addTriangle(baseIndex + 1, baseIndex + 3, baseIndex + 2);
}

void Trianglation::deleteSuperTriangles()
{
    if (m_points.size() < 4)
        return;

    qsizetype baseIndex = m_points.size() - 4;

    for (qsizetype i = m_triangles.size() - 1; i >= 0; i--)
    {
        const Triangle& triangle = m_triangles[i];
        if (triangle.p1 >= baseIndex || triangle.p2 >= baseIndex || triangle.p3 >= baseIndex)
        {
            m_triangles.removeAt(i);
        }
    }

    m_points.removeLast();
    m_points.removeLast();
    m_points.removeLast();
    m_points.removeLast();
}
