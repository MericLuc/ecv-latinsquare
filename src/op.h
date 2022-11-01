#ifndef OP_H
#define OP_H

#include <cstddef>

class Cell;

class Op
{
public:
    Op(size_t from = 0, size_t to = 0, Cell* cell = nullptr) noexcept;

    /*!
     * \brief reverse Create a reverse operation
     * \param op
     */
    Op reverse() noexcept;

    void apply() const noexcept;

private:
    size_t from, to; /*< Previous value (before operation) and after */
    Cell*  cell;
};

#endif // OP_H
