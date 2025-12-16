#ifndef TRIANGLATION_H
#define TRIANGULATION_H 


#include <QVector>
#include <QList>
#include <QVector2D>


class Triangle
{
public:
    Triangle() = default;
    Triangle(qsizetype p1, qsizetype p2, qsizetype p3, const QVector2D* points);
    ~Triangle() = default;

    QVector2D calculateCircle();

    void getCircumCircle(QVector2D& center, double& radius);

    qsizetype p1;
    qsizetype p2;
    qsizetype p3;
    QVector2D* m_points;

    QVector2D circumcenter;
    double radius;
};

class Trianglation
{
public:
    Trianglation(const QVector<QVector2D>& points);
    ~Trianglation();

    void stepForward();

    void getTrianglePoints(QVector<QVector2D>& points);
    void getCircumCirclePoints(QVector<QVector2D>& centers, QVector<double>& radii);

private:
    void addTriangle(qsizetype p1, qsizetype p2, qsizetype p3);
    void generateSuperTriangles();
    void deleteSuperTriangles();

private:
    qsizetype m_currentPointIndex = 0;
    QVector<QVector2D> m_points;
    QList<Triangle> m_triangles;
};


#endif// TRIANGULATION_H