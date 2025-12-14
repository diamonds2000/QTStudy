#ifndef TRIANGLATION_H
#define TRIANGULATION_H 

#include <QPoint>
#include <QVector>
#include <QList>


class Triangle
{
public:
    Triangle() = default;
    Triangle(QPoint p1, QPoint p2, QPoint p3)
    {
        this->p1 = p1;
        this->p2 = p2;
        this->p3 = p3;
    }
    ~Triangle() = default;

    QPoint calculateCircle();

    QPoint p1;
    QPoint p2;
    QPoint p3;

    QPoint circumcenter;
    double radius;
};

class Trianglation
{
public:
    Trianglation(const QVector<QPoint>& points);
    ~Trianglation();

    void stepForward();

    void getTrianglePoints(QVector<QPoint>& points);

private:
    QVector<QPoint> m_points;
    QList<Triangle> m_triangles;
};


#endif// TRIANGULATION_H