add_executable(app
    main.cpp)

target_link_libraries(app
    PRIVATE
    game
    gfx
)

copy_assets(app)
