#pragma once

namespace ui {
    enum class MouseCursor {
        Default,       // Default pointer shape
        Arrow,         // Arrow shape
        IBeam,         // Text writing cursor shape
        Crosshair,     // Cross shape
        PointingHand,  // Pointing hand cursor
        ResizeEW,      // Horizontal resize/move arrow shape
        ResizeNS,      // Vertical resize/move arrow shape
        ResizeNWSE,    // Top-left to bottom-right diagonal resize/move arrow shape
        ResizeNESW,    // Top-right to bottom-left diagonal resize/move arrow shape
        ResizeAll,     // Omnidirectional resize/move cursor shape
        NotAllowed     // Operation-not-allowed shape
    };

    class Mouse {
    public:
        static void set_cursor(MouseCursor cursor);

        static MouseCursor current_cursor();
    };
}  // namespace ui
