#ifndef CELL_H
#define CELL_H

#include <QWidget>

#include "op.h"

class DynamicFontSizeLabel;
class QLabel;

class Cell : public QWidget
{
    Q_OBJECT
    friend class Grid;

public:
    Cell(const size_t x,
         const size_t y,
         const size_t max_val = 9,
         QWidget*     parent = nullptr) noexcept;
    virtual ~Cell() noexcept = default;

    void   set(const size_t& val) noexcept;
    size_t get(void) const noexcept { return _val; }

signals:
    void changed(Op);
    void hovered(bool);

protected:
    void enterEvent(QEvent*) override;
    void leaveEvent(QEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override;

    void updateVal(size_t) noexcept;

protected:
    class Marker
    {
        // Create the marker to show when the cell is hovered
        // It should also allow to click on a value to set
    };

private:
    const size_t _x, _y;
    size_t       _val{ 0 }, _max_val;

    // TODO - Add a Widget to show when hovered

    // UI related members
    QLabel*               _bg{ nullptr };
    DynamicFontSizeLabel* _lb{ nullptr };
};

#endif // CELL_H
