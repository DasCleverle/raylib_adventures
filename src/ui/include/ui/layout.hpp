#pragma once

namespace ui {
    class Panel;

    class Layout {

    public:
        virtual ~Layout() = default;
        virtual void recalc(ui::Panel& panel) const = 0;
    };
}  // namespace ui
