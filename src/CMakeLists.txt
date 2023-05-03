set(current_target starter_window)

set(SOURCE_FILES)
set(STARTER_WINDOW_SRC
    main.cpp
    window.h
)
source_group("" FILES ${STARTER_WINDOW_SRC})

if(MSVC)
set(PLATFORM_SRC
    platform/win32_window.cpp
)
else()
set(PLATFORM_SRC
    platform/null_window.cpp
)
endif()
source_group(platform FILES ${PLATFORM_SRC})

list(APPEND SOURCE_FILES ${PLATFORM_SRC})
list(APPEND SOURCE_FILES ${STARTER_WINDOW_SRC})

add_executable(
    ${current_target}
    ${SOURCE_FILES}
)

if( ENABLE_ALL_REASONABLE_WARNINGS )
    MESSAGE("-- Additional Warnings Enabled")
    target_enable_warnings(${current_target})
endif()

if( ENABLE_WARNINGS_AS_ERRORS )
    MESSAGE("-- Warnings as Errors")
    target_warnings_as_errors(${current_target})
endif()

if( ENABLE_SANITIZERS )
    MESSAGE("-- Sanitizers Enabled")
    target_enable_sanitizers(${current_target})
endif()

if( ENABLE_STATIC_ANALYSIS )
    MESSAGE("-- Static Analysis Enabled")
    target_enable_static_analysis(${current_target})
endif()
