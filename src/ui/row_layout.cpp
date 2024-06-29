#include "ui/row_layout.hpp"

#include "ui/panel.hpp"
#include "utils/math.hpp"

namespace ui {
    void RowLayout::recalc(ui::Panel& panel) const {
        auto const area_count = panel.m_widgets.size();

        if (area_count == 0) {
            return;
        }

        auto const row_count = ceil_div(area_count, m_row_count);
        auto const column_width = 1.0f / static_cast<float>(row_count);
        auto const row_height = 1.0f / static_cast<float>(m_row_count);

        auto const total_area = panel.area();
        std::size_t i = 0;

        for (std::size_t row = 0; row < row_count and i < area_count; row++) {
            for (std::size_t column = 0; column < m_row_count and i < area_count; column++) {
                auto const relative_area = RectF{
                    Vec2f{column * column_width, row * row_height},
                    Vec2f{         column_width,       row_height}
                };

                panel.m_widgets[i]->set_area(relative_area.to_absolute(total_area));
                i++;
            }
        }
    }
}  // namespace ui
