#ifndef CELL_H
#define CELL_H

#include <QWidget>

#include "op.h"

class Cell : public QWidget
{
    Q_OBJECT
    friend class Grid;

public:
    Cell(const size_t x, const size_t y, QWidget* parent = nullptr) noexcept;
    virtual ~Cell() noexcept = default;

    void   set(const size_t& val) noexcept { _val = val; }
    size_t get(void) const noexcept { return _val; }

signals:
    void changed(Op);

private:
    const size_t _x, _y;
    size_t       _val{ 0 };
};

#endif // CELL_H
