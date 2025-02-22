cmake_minimum_required(VERSION 2.8)

project(litehtml CXX)

add_subdirectory(src/gumbo)

set(SOURCE_LITEHTML
    src/background.cpp
    src/box.cpp
    src/context.cpp
    src/css_length.cpp
    src/css_selector.cpp
    src/document.cpp
    src/el_anchor.cpp
    src/el_base.cpp
    src/el_before_after.cpp
    src/el_body.cpp
    src/el_break.cpp
    src/el_cdata.cpp
    src/el_comment.cpp
    src/el_div.cpp
    src/element.cpp
    src/el_font.cpp
    src/el_image.cpp
    src/el_link.cpp
    src/el_para.cpp
    src/el_script.cpp
    src/el_space.cpp
    src/el_style.cpp
    src/el_table.cpp
    src/el_td.cpp
    src/el_text.cpp
    src/el_title.cpp
    src/el_tr.cpp
    src/html.cpp
    src/html_tag.cpp
    src/iterators.cpp
    src/media_query.cpp
    src/style.cpp
    src/stylesheet.cpp
    src/table.cpp
    src/utf8_strings.cpp
    src/web_color.cpp
)

set(HEADER_LITEHTML
    include/litehtml.h
    src/attributes.h
    src/background.h
    src/borders.h
    src/box.h
    src/context.h
    src/css_length.h
    src/css_margins.h
    src/css_offsets.h
    src/css_position.h
    src/css_selector.h
    src/document.h
    src/el_anchor.h
    src/el_base.h
    src/el_before_after.h
    src/el_body.h
    src/el_break.h
    src/el_cdata.h
    src/el_comment.h
    src/el_div.h
    src/el_font.h
    src/el_image.h
    src/el_link.h
    src/el_para.h
    src/el_script.h
    src/el_space.h
    src/el_style.h
    src/el_table.h
    src/el_td.h
    src/el_text.h
    src/el_title.h
    src/el_tr.h
    src/element.h
    src/html.h
    src/html_tag.h
    src/iterators.h
    src/media_query.h
    src/os_types.h
    src/style.h
    src/stylesheet.h
    src/table.h
    src/types.h
    src/utf8_strings.h
    src/web_color.h
)

add_library(${PROJECT_NAME} ${SOURCE_LITEHTML})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
    C_STANDARD 99
    PUBLIC_HEADER "${HEADER_LITEHTML}"
)

# Export litehtml includes.
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

# Gumbo
target_link_libraries(${PROJECT_NAME} PUBLIC gumbo)

# install and export
install(TARGETS ${PROJECT_NAME}
    EXPORT litehtmlTargets
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include/litehtml
)
install(FILES cmake/litehtmlConfig.cmake DESTINATION lib/cmake/litehtml)
install(EXPORT litehtmlTargets FILE litehtmlTargets.cmake DESTINATION lib/cmake/litehtml)

