#pragma once

#include "layout.hpp"
#include "panel.hpp"

namespace ui {
    class RowLayout final : public Layout {
    private:
        std::size_t m_row_count;

    public:
        RowLayout(std::size_t row_count)
            : m_row_count{row_count} {}

        void recalc(ui::Panel& panel) const override;
    };
}  // namespace ui
