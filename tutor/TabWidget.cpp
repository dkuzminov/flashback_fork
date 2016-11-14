#include "TabWidget.h"

#include <QtGui>
#include <QtWidgets>
#include "GuiPalette.h"

TabWidget::TabWidget(const QString &id, const QString &task, const QString &description, bool isLight, QWidget *parent)
    : QWidget(parent),
      m_id(id),
      m_task(task),
      m_description(description)
{
    setupUi(this);
    setAutoFillBackground(true);
    setGeometry(0, 0, 300, 71);
    QPalette _palette = GuiPalette::Get().GetPalette();
    m_brush = isLight ? _palette.light() : _palette.midlight();
    QPalette p = palette();
    p.setBrush(QPalette::Active, QPalette::Background, m_brush);
    setPalette(p);

    m_taskLabel->setText(m_task);
    m_descriptionLabel->setText(m_description);
}

void TabWidget::setHighlighted(bool enabled)
{
    QPalette _palette = GuiPalette::Get().GetPalette();
    QColor color = _palette.base().color();

    QPalette p = palette();
    p.setColor(backgroundRole(), enabled? color: m_brush.color());
    setPalette(p);
}

void TabWidget::selectedChanged(int state)
{
    emit spotSelected(m_id, state);
}

bool TabWidget::event(QEvent *event)
{
    QInputEvent* input = dynamic_cast<QInputEvent*>(event);
    if (input) {
        switch (input->type()) {
        case QEvent::MouseButtonPress:
            emit clicked();
        }
    }
    return false;
}
