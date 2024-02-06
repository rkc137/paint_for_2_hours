#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QBrush>
#include <QPen>

#include <cmath>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene();
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void set_rect(QRect rect);
    void set_color(QColor clr);
    void set_pen_size(int s);

    enum class instruments{
        pen,
        rect,
        elps
    } instrument = instruments::pen;
private:
    QPen pen;
    QPoint pen_pos = {0, 0};
    QPoint max_point = {0, 0}, min_point = {0, 0};
    bool is_painting = false;

    QPoint start_pos;
    QGraphicsRectItem rect_blue_print;
    QGraphicsEllipseItem elps_blue_print;


    bool is_valid_point(QPoint point);
};

#endif // SCENE_H
