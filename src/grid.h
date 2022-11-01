#ifndef GRID_H
#define GRID_H

#include <QWidget>

#include <stack>

#include "op.h"

class Cell;

/*!
 * \brief The Grid class exposes a N x N Grid (LatinSquare)
 */
class Grid : public QWidget
{
    Q_OBJECT

public:
    typedef std::deque<Op>  Hist;
    static constexpr size_t max_hist_size{ 100 };

public:
    explicit Grid(QWidget* parent = nullptr) noexcept;
    virtual ~Grid() noexcept = default;

    /*!
     * \brief data Get the string representation of the grid
     */
    std::vector<std::string> data() const noexcept;

signals:
    /*!
     * \brief changed emitted when the grid changes
     */
    void changed();

public slots:

    [[maybe_unused]] bool resize(const size_t& size) noexcept;
    [[maybe_unused]] bool undo(void) noexcept;
    [[maybe_unused]] bool redo(void) noexcept;

    void clear(void) noexcept;

private slots:
    void onCellChanged(Op);

private:
    std::vector<Cell*> _cells;         /*!< Cells of the Grid */
    Hist               _done, _undone; /*!< History for undo/redo operations */
    size_t             _size{ 5 };
};

#endif // GRID_H
