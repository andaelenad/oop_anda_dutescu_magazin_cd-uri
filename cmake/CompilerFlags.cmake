include(cmake/CustomStdlibAndSanitizers.cmake)

function(set_compiler_flags)
    set(multiValueArgs TARGET_NAMES)
    set(oneValueArgs RUN_SANITIZERS)
    cmake_parse_arguments(PARSE_ARGV 0 ARG "" "${oneValueArgs}" "${multiValueArgs}")

    # Valoare default pentru RUN_SANITIZERS
    if(NOT DEFINED ARG_RUN_SANITIZERS)
        set(ARG_RUN_SANITIZERS TRUE)
    endif()

    foreach (TARGET_NAME IN LISTS ARG_TARGET_NAMES)

        # Asigură-te că targetul există
        if (NOT TARGET ${TARGET_NAME})
            message(WARNING "set_compiler_flags: Target '${TARGET_NAME}' nu există. Omit.")
            continue()
        endif()

        # --- GitHub Actions define ---
        if(GITHUB_ACTIONS)
            message("NOTE: GITHUB_ACTIONS definit")
            target_compile_definitions(${TARGET_NAME} PRIVATE GITHUB_ACTIONS)
        endif()

        # --- Warning as errors ---
        if(PROJECT_WARNINGS_AS_ERRORS)
            set_property(TARGET ${TARGET_NAME} PROPERTY COMPILE_WARNING_AS_ERROR ON)
        endif()

        # --- Flaguri de compilare ---
        message("Compiler: ${CMAKE_CXX_COMPILER_ID} version ${CMAKE_CXX_COMPILER_VERSION}")

        if(MSVC)
            target_compile_options(${TARGET_NAME} PRIVATE
                    /W4 /permissive-
                    /wd4244 /wd4267 /wd4996
                    /external:anglebrackets /external:W0
                    /utf-8 /MP
            )
        else()
            target_compile_options(${TARGET_NAME} PRIVATE
                    -Wall -Wextra -pedantic
            )
        endif()

        # --- Sanitizers ---
        if("${ARG_RUN_SANITIZERS}" STREQUAL "TRUE")
            set_custom_stdlib_and_sanitizers(${TARGET_NAME} true)
        endif()

    endforeach ()
endfunction()
