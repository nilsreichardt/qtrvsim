#include "latch.h"

using namespace coreview;

//////////////////////
#define WIDTH 10
#define PENW 1
//////////////////////

Latch::Latch(machine::QtMipsMachine *machine, qreal height) : QGraphicsObject(nullptr) {
    this->height = height;

    wedge_animation = new QPropertyAnimation(this, "wedge_clr");
    wedge_animation->setDuration(100);
    wedge_animation->setStartValue(QColor(0, 0, 0));
    wedge_animation->setEndValue(QColor(255, 255, 255));
    wedge_clr = QColor(255, 255, 255);

    connect(machine, SIGNAL(tick()), this, SLOT(tick()));
}

QRectF Latch::boundingRect() const {
    return QRectF(-PENW / 2, -PENW / 2, WIDTH + PENW, height + PENW);
}

void Latch::paint(QPainter *painter, const QStyleOptionGraphicsItem *option __attribute__((unused)), QWidget *widget __attribute__((unused))) {
    painter->drawRect(0, 0, WIDTH, height);
    // Now tick rectangle
    const QPointF tickPolygon[] = {
        QPointF(0, 0),
        QPointF(WIDTH, 0),
        QPointF(WIDTH/2, WIDTH/2)
    };
    painter->setBrush(QBrush(wedge_color()));
    painter->drawPolygon(tickPolygon, sizeof(tickPolygon) / sizeof(QPointF));
}

QColor Latch::wedge_color() {
    return wedge_clr;
}

void Latch::set_wedge_color(QColor &c) {
    wedge_clr = c;
    update();
}

void Latch::setPos(qreal x, qreal y) {
    QGraphicsObject::setPos(x, y);
    for (int i = 0; i < connectors.size(); i++) {
        connectors[i].in->setPos(x, y + connectors_off[i]);
        connectors[i].out->setPos(x + WIDTH, y + connectors_off[i]);
    }
}

struct Latch::ConnectorPair Latch::new_connector(qreal cy) {
    SANITY_ASSERT(cy < height, "Latch: Trying to create connector outside of latch height");
    ConnectorPair cp;
    cp.in = new Connector();
    cp.out = new Connector();
    connectors.append(cp);
    connectors_off.append(cy);
    setPos(x(), y()); // Update connectors position
    return cp;
}

void Latch::tick() {
    wedge_clr = QColor(0, 0, 0);
    wedge_animation->start();
    update();
}