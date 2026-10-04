#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPoint>
#include <QQueue>
#include <QTimer>

class RingBuffer;

class WaveView : public QWidget
{
    Q_OBJECT

public:
    explicit WaveView(QWidget *parent = nullptr);

    void setModel(RingBuffer* buffer) {
        m_PointBuffer = buffer;
    }

    void startAnimation() {
        m_timer.start(50); // Update every 50 ms
    }

    void stopAnimation() {
        m_timer.stop();
    }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    RingBuffer* m_PointBuffer = nullptr;
    QTimer m_timer;
};