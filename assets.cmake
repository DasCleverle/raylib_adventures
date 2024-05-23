macro(copy_assets target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${PROJECT_SOURCE_DIR}/assets/fonts "$<PATH:GET_PARENT_PATH,$<TARGET_FILE:${target}>>/assets/fonts"
        DEPENDS ${target}
    )
endmacro()



