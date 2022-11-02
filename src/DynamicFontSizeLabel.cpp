#include "DynamicFontSizeLabel.h"

#define FONT_PRECISION (0.5)

#include <QDebug>
#include <QElapsedTimer>

/*****************************************************************************/
DynamicFontSizeLabel::DynamicFontSizeLabel(QWidget* parent, Qt::WindowFlags f)
  : QLabel(parent, f)
{
    setIndent(0);
}

/*****************************************************************************/
void
DynamicFontSizeLabel::paintEvent(QPaintEvent* event)
{
    QFont newFont{ font() };
    float fontSize{ getWidgetMaximumFontSize(this, this->text()) };
    newFont.setPointSizeF(fontSize);
    setFont(newFont);

    QLabel::paintEvent(event);
}

/*****************************************************************************/
float
DynamicFontSizeLabel::getWidgetMaximumFontSize(QWidget* widget, QString text)
{
    QFont       font = widget->font();
    const QRect widgetRect = widget->contentsRect();
    const float widgetWidth = widgetRect.width();
    const float widgetHeight = widgetRect.height();

    QRectF newFontSizeRect;
    float  currentSize = font.pointSizeF();

    float step = currentSize / 2.0;

    if (step <= FONT_PRECISION)
        step = FONT_PRECISION * 4.0;

    float lastTestedSize = currentSize;

    float currentHeight = 0;
    float currentWidth = 0;
    if (text == "") {
        return currentSize;
    }

    /* Only stop when step is small enough and new size is smaller than QWidget */
    while (step > FONT_PRECISION || (currentHeight > widgetHeight) ||
           (currentWidth > widgetWidth)) {
        lastTestedSize = currentSize;

        font.setPointSizeF(currentSize);
        QFontMetricsF fm(font);

        QLabel* label = qobject_cast<QLabel*>(widget);
        if (label) {
            newFontSizeRect = fm.boundingRect(
              widgetRect, (label->wordWrap() ? Qt::TextWordWrap : 0) | label->alignment(), text);
        } else {
            newFontSizeRect = fm.boundingRect(widgetRect, 0, text);
        }

        currentHeight = newFontSizeRect.height();
        currentWidth = newFontSizeRect.width();

        if ((currentHeight > widgetHeight) || (currentWidth > widgetWidth)) {
            // qDebug() << "-- contentsRect()" << label->contentsRect() << "rect"<< label->rect() <<
            // " newFontSizeRect" << newFontSizeRect << "Tight" << text << currentSize;
            currentSize -= step;
            /* if step is small enough, keep it constant, so it converge to biggest font size */
            if (step > FONT_PRECISION) {
                step /= 2.0;
            }
            /* Do not allow negative size */
            if (currentSize <= 0) {
                break;
            }
        } else {
            // qDebug() << "++ contentsRect()" << label->contentsRect() << "rect"<< label->rect() <<
            // " newFontSizeRect" << newFontSizeRect << "Tight" << text << currentSize;
            currentSize += step;
        }
    }
    return lastTestedSize;
}

/*****************************************************************************/
void
DynamicFontSizeLabel::setTextColor(const QColor& color)
{
    if (color.isValid() && color != textColor) {
        textColor = color;
        setStyleSheet("color : " + color.name() + ";");
    }
}

/*****************************************************************************/
QColor
DynamicFontSizeLabel::getTextColor()
{
    return textColor;
}

/*****************************************************************************/
void
DynamicFontSizeLabel::setTextAndColor(const QString& text, QColor color)
{
    setTextColor(color);
    setText(text);
}

/*****************************************************************************/
QSize
DynamicFontSizeLabel::minimumSizeHint() const
{
    return QWidget::minimumSizeHint();
}

/*****************************************************************************/
QSize
DynamicFontSizeLabel::sizeHint() const
{
    return QWidget::sizeHint();
}
