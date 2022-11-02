#ifndef SRC_DYNAMICFONTSIZELABEL_H
#define SRC_DYNAMICFONTSIZELABEL_H

#include <QColor>
#include <QLabel>

class DynamicFontSizeLabel : public QLabel
{
    Q_OBJECT

public:
    explicit DynamicFontSizeLabel(QWidget* parent = NULL, Qt::WindowFlags f = Qt::WindowFlags());
    virtual ~DynamicFontSizeLabel() = default;

    static float getWidgetMaximumFontSize(QWidget* widget, QString text);

    void   setTextColor(const QColor&);
    QColor getTextColor();

    void setTextAndColor(const QString& text, QColor color = QColor::Invalid);

protected:
    QColor textColor;

protected:
    void paintEvent(QPaintEvent* event);

public:
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
};

#endif // SRC_DYNAMICFONTSIZELABEL_H
