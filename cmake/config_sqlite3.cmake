include(FetchContent)

function(config_sqlite3 TARGET_NAME)

    FetchContent_Declare(
        sqlite3
        URL https://www.sqlite.org/2025/sqlite-src-3490100.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )

    FetchContent_MakeAvailable(sqlite3)

    target_link_libraries(${TARGET_NAME} PRIVATE sqlite3)
    target_include_directories(${TARGET_NAME} PRIVATE ${sqlite3_SOURCE_DIR})
endfunction()