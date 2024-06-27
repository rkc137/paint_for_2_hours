#include "scene.h"
#include "qpainter.h"

Scene::Scene()
{
    pen.setWidth(3);
    pen.setColor(Qt::black);
    rect_blue_print.setPen(pen);
    elps_blue_print.setPen(pen);
    addItem(&rect_blue_print);
    addItem(&elps_blue_print);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    start_pos = pen_pos = event->scenePos().toPoint();

    rect_blue_print.setPen(pen);
    elps_blue_print.setPen(pen);

    switch(instrument)
    {
    case instruments::pen:
    {
        break;
    }
    case instruments::rect:
    {
        rect_blue_print.setRect(start_pos.x(), start_pos.y(), 0, 0);
        rect_blue_print.show();
        break;
    }
    case instruments::elps:
    {
        elps_blue_print.setRect(start_pos.x(), start_pos.y(), 0, 0);
        elps_blue_print.show();
        break;
    }
    }
    if(!is_valid_point((pen_pos)))
        return;
    is_painting = true;
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    auto new_point = event->scenePos().toPoint();
    is_painting = false;
    elps_blue_print.hide();
    rect_blue_print.hide();
    if(!is_valid_point(new_point))
        return;
    switch(instrument)
    {
    case instruments::pen:
        break;
    case instruments::rect:
        addRect(rect_blue_print.rect(), pen);
        break;
    case instruments::elps:
        addEllipse(elps_blue_print.rect(), pen);
        break;
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!is_painting)
        return;
    auto new_point = event->scenePos().toPoint();
    if(!is_valid_point((new_point)))
        return;
    switch(instrument)
    {
    case instruments::pen:
    {
        addLine(pen_pos.x(), pen_pos.y(), new_point.x(), new_point.y(), pen);
        break;
    }
    case instruments::rect:
    {
        rect_blue_print.setRect(start_pos.x(), start_pos.y(), new_point.x() - start_pos.x(), new_point.y() - start_pos.y());
        break;
    }
    case instruments::elps:
    {
        int s = std::sqrt(std::pow(start_pos.x() - new_point.x(), 2) + std::pow(start_pos.y() - new_point.y(), 2));
        elps_blue_print.setRect(start_pos.x() - s, start_pos.y() - s, 2 * s, 2 * s);
        break;
    }
    }
    pen_pos = new_point;
}


void Scene::set_rect(QRect rect)
{
    setSceneRect(rect);
    addRect(rect, pen);
}

void Scene::set_color(QColor clr)
{
    pen.setColor(clr);
}

void Scene::set_pen_size(int s)
{
    pen.setWidth(s);
}

void Scene::save_file(QFile path)
{
    clearSelection();                                                  // Selections would also render to the file
    setSceneRect(itemsBoundingRect());                          // Re-shrink the scene to it's bounding contents
    QImage image(sceneRect().size().toSize(), QImage::Format_ARGB32);  // Create the image with the exact size of the shrunk scene
    image.fill(Qt::transparent);                                              // Start all pixels transparent
    QPainter painter(&image);
    render(&painter);
    image.save(path.fileName());
}

bool Scene::is_valid_point(QPoint point)
{
    return ((point.x() > sceneRect().x()     && point.y() > sceneRect().y()) &&
            (point.x() < sceneRect().width() && point.y() < sceneRect().height()));
}
