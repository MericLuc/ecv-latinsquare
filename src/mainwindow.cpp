/**
 * @file mainwindow.cpp
 * @brief Implementation of \a mainwindow.h
 * @author lhm
 */

#include "grid.h"

// Project's headers
#include "./ui_mainwindow.h"
#include "mainwindow.h"

// External headers
#include <ecv.hpp>

// Standard headers
#include <chrono>
#include <random>

// Qt headers
#include <QDebug>
#include <QGraphicsDropShadowEffect>

static auto                               _sols{ ecv::LatinSquares::generate({ "0" })->solve() };
static std::unique_ptr<ecv::LatinSquares> _model{ nullptr };

/*****************************************************************************/
void
setupButton(QPushButton* pb, const QString& name = "setupButton", const QString& text = "")
{
    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect;
    shadow_effect->setOffset(1, 1);
    shadow_effect->setColor(Qt::gray);
    shadow_effect->setBlurRadius(2);

    if (!text.isEmpty())
        pb->setText(text);
    pb->setObjectName(name);
    pb->setGraphicsEffect(shadow_effect);
}

/*****************************************************************************/
/*!
 * @brief Very basic stopwatch to measure ellapsed time since it has been created
 */
template<class Clock = std::chrono::high_resolution_clock, class Unit = std::chrono::milliseconds>
class stopwatch
{
public:
    explicit stopwatch() noexcept
      : _start{ Clock::now() }
    {}

    Unit elapsed() const noexcept
    {
        return std::chrono::duration_cast<Unit>(Clock::now() - _start);
    }

private:
    typedef std::chrono::time_point<Clock> TimePt;
    const TimePt                           _start;
};

/*****************************************************************************/
MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (auto& button : { ui->new_pb, ui->solve_pb, ui->undo_cb, ui->redo_cb, ui->res_pb })
        setupButton(button);
    setStyleSheet("QPushButton#setupButton{background-color:#ffffff;color:#5F5F5F;}"
                  "QPushButton#setupButton:hover{background-color:#daffb3;}"
                  "QPushButton#setupButton:pressed{background-color:#5cb300;}"
                  "QPushButton#setupButton:!enabled{background-color:rgb(200, 200, 200);}");

    for (auto& button : { ui->undo_cb, ui->redo_cb })
        button->setStyleSheet(
          QString("border-top-right-radius:%1px;border-bottom-right-radius:%1px;").arg(3));

    // Connect to grid changes
    connect(ui->square_w, &Grid::changed, [this]() {
        if (ui->res_gb->isEnabled()) {
            ui->res_gb->setDisabled(true);
            ui->res_label->clear();
        }
    });

    // Connect buttons with Grid
    connect(ui->undo_cb, SIGNAL(clicked()), ui->square_w, SLOT(undo()));
    connect(ui->redo_cb, SIGNAL(clicked()), ui->square_w, SLOT(redo()));
    connect(ui->size_cb, &QComboBox::currentTextChanged, [this]() {
        ui->square_w->resize(ui->size_cb->currentIndex() + 2);
    });
    connect(ui->new_pb, &QPushButton::clicked, [this]() { ui->square_w->clear(); });
    connect(ui->res_pb, &QPushButton::clicked, [this]() {
        if (nullptr == _model || std::empty(_sols))
            return;

        static std::random_device dev;
        static std::mt19937       rng{ dev() };

        std::uniform_int_distribution<std::mt19937::result_type> dist{ 1, std::size(_sols) - 1 };

        ui->square_w->fromData(_model->apply(_sols[dist(rng)]));
    });
    connect(ui->solve_pb, &QPushButton::clicked, [this]() {
        // TODO
        // Disable UI / Show wheel / Allow to cancel

        // Perform the ecv resolution
        _sols.clear();
        _model.reset(nullptr);
        _model = ecv::LatinSquares::generate(ui->square_w->data());
        if (nullptr == _model)
            return;

        stopwatch watch;
        _sols = _model->solve(ui->all_cb->isChecked());

        if (auto solsNb{ std::size(_sols) }; solsNb > 0) {
            ui->res_pb->setEnabled(solsNb > 1);
            ui->res_gb->setEnabled(true);
            ui->res_label->setText(QString("Found %1 solutions (%2 ms)")
                                     .arg(std::size(_sols))
                                     .arg(watch.elapsed().count()));
            ui->square_w->fromData(_model->apply(_sols[0]));
        } else {
            ui->res_label->setText("No solution");
        }
    });
}

/*****************************************************************************/
MainWindow::~MainWindow()
{
    delete ui;
}
