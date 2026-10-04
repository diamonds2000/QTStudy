#include "waveview.h"
#include "ringbuffer.h"

#define MAX_POINTS 500



WaveView::WaveView(QWidget *parent)
    : QWidget(parent)
{
    connect(&m_timer, &QTimer::timeout, this, [this]() {

        update(); // Trigger a repaint
    });
}


void WaveView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::black);

    const double x_offset = 5; // Start drawing a bit inside the widget
    const double midY = rect().height() / 2.0;

    // draw axis
    painter.drawLine(x_offset, midY, rect().width() - x_offset, midY);
    painter.drawLine(x_offset, 10, x_offset, rect().height() - 10);

    // draw grad
    painter.setPen(Qt::lightGray);
    for (int i = 1; i <= 9; ++i) {
        if (i == 5) continue; // Skip the middle line since it's already drawn
        int y = 10 + i * (rect().height() - 20) / 10;
        painter.drawLine(x_offset, y, rect().width() - x_offset, y);
    }

    for (int i = 1; i <= 10; ++i) {
        int x = x_offset + i * (rect().width() - 2 * x_offset) / 10;
        painter.drawLine(x, 10, x, rect().height() - 10);
    }

    painter.setPen(Qt::green);

    if (!m_PointBuffer || m_PointBuffer->isEmpty())
        return;

    int width = rect().width() - 2 * x_offset;

    try {
        double buffer[MAX_POINTS];
        size_t copiedSize = m_PointBuffer->copyLast(buffer, MAX_POINTS);
        if (copiedSize == 0) {
            return;
        }
        QPoint lastPoint(x_offset, buffer[0] / 100.0 * (rect().height() - 100) + 50);
        for (int i = 1; i < copiedSize; ++i) {
            double value = buffer[i] / 100.0 * (rect().height() - 100) + 50;
            QPoint point(i * (width / MAX_POINTS) + x_offset, value);
            painter.drawLine(lastPoint, point);
            lastPoint = point;
        }
    }
    catch (const std::runtime_error& e) {
    }
}