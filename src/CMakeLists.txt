set(current_target blank_slate)

add_executable(
    ${current_target} 
    main.cpp
)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${current_target} PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

if( ENABLE_ALL_REASONABLE_WARNINGS )
    MESSAGE("Additional Warnings Enabled")
    target_enable_warnings(${current_target})
endif()

if( ENABLE_WARNINGS_AS_ERRORS )
    MESSAGE("Warnings as Errors")
    target_warnings_as_errors(${current_target})
endif()

if( ENABLE_SANITIZERS )
    MESSAGE("Sanitizers Enabled")
    target_enable_sanitizers(${current_target})
endif()

if( ENABLE_STATIC_ANALYSIS )
    MESSAGE("Static Analysis Enabled")
    target_enable_static_analysis(${current_target})
endif()
