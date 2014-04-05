#ifndef CLOCKRENDER_H
#define CLOCKRENDER_H

#include <QWidget>

class ClockRender : public QWidget
{
    Q_OBJECT
public:
    explicit ClockRender(QWidget *parent = 0);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;


protected:
    void paintEvent(QPaintEvent *event);

private :
    void printlog(QString str);
    int angle;

signals:

public slots:
    void renderClock();

};

#endif // CLOCKRENDER_H
