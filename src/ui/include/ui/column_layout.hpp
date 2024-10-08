#pragma once

#include "layout.hpp"
#include "panel.hpp"

namespace ui {
    class ColumnLayout final : public Layout {
    private:
        std::size_t m_column_count;

    public:
        ColumnLayout(std::size_t column_count)
            : m_column_count{column_count} {}

        void recalc(ui::Panel& panel) const override;
    };
}  // namespace ui
