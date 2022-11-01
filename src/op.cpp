/**
 * @file grid.cpp
 * @brief Implementation of \a grid.h
 * @author lhm
 */

// Project's headers
#include "op.h"
#include "cell.h"

/*****************************************************************************/
Op::Op(size_t from, size_t to, Cell* cell) noexcept
  : from{ from }
  , to{ to }
  , cell{ cell }
{}

/*****************************************************************************/
Op
Op::reverse() noexcept
{
    Op ret;
    ret.cell = cell;
    ret.from = to;
    ret.to = from;
    return ret;
}

/*****************************************************************************/
void
Op::apply() const noexcept
{
    if (nullptr != cell)
        cell->set(to);
}
