add_executable(app
    main.cpp
    application.cpp
    application.hpp
    font_type.hpp
)

target_link_libraries(app
    PRIVATE
    game
    gfx
    ui
)

copy_assets(app)
