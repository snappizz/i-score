#include "TemporalScenarioProcessView.hpp"

#include <tools/NamedObject.hpp>

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QMenu>
#include <QDebug>

TemporalScenarioProcessView::TemporalScenarioProcessView(QGraphicsObject* parent):
	ProcessViewInterface{parent}
{
	this->setParentItem(parent);
	this->setFlags(ItemClipsChildrenToShape | ItemIsSelectable | ItemIsFocusable);

	this->setZValue(parent->zValue() + 1);
	//this->parentItem()->scene()->addItem(this);

    m_clearAction = new QAction("clear contents", this);
    connect(m_clearAction,  &QAction::triggered,
            this,           &TemporalScenarioProcessView::clearPressed);
}


QRectF TemporalScenarioProcessView::boundingRect() const
{
	auto pr = parentItem()->boundingRect();
	return {0, 0,
			pr.width()  - 2 * DEMO_PIXEL_SPACING_TEST,
			pr.height() - 2 * DEMO_PIXEL_SPACING_TEST};
}


void TemporalScenarioProcessView::paint(QPainter* painter,
								const QStyleOptionGraphicsItem* option,
								QWidget* widget)
{
	painter->drawText(boundingRect(), "Scenario");

	if(isSelected())
	{
		painter->setPen(Qt::blue);
	}

	painter->drawRect(boundingRect());

	if(m_lock)
	{
		painter->setBrush({Qt::red, Qt::DiagCrossPattern});
		painter->drawRect(boundingRect());
	}
}


void TemporalScenarioProcessView::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsObject::mousePressEvent(event);

	if(event->modifiers() == Qt::ControlModifier)
	{
		emit scenarioPressedWithControl(event->pos());
	}
	else
	{
		emit scenarioPressed();
	}
}

void TemporalScenarioProcessView::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsObject::mouseMoveEvent(event);
}

void TemporalScenarioProcessView::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsObject::mouseReleaseEvent(event);
	if(event->modifiers() == Qt::ControlModifier)
	{
        emit scenarioReleased(event->pos(), mapToScene(event->pos()));
    }
}

void TemporalScenarioProcessView::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu contextMenu{};
    contextMenu.clear();
    contextMenu.addAction(m_clearAction);
    contextMenu.exec(event->screenPos());
}

void TemporalScenarioProcessView::keyPressEvent(QKeyEvent* event)
{
	if(event->key() == Qt::Key_Delete)
	{
		emit deletePressed();
	}
}


