/**
 * @file cell.cpp
 * @brief Implementation of \a cell.h
 * @author lhm
 */

// Project's headers
#include "cell.h"
#include "op.h"

// External headers

/*****************************************************************************/
Cell::Cell(const size_t x, const size_t y, QWidget* parent) noexcept
  : QWidget(parent)
  , _x{ x }
  , _y{ y }
{}

/*****************************************************************************/
