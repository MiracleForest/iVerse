add_rules("mode.debug", "mode.release", "mode.releasedbg")

add_repositories("MiF-repo https://github.com/MiracleForest/xmake-repo.git")

add_requires("iFamily master")

target("iVerseTest")
    set_kind("binary")
    add_files("iVerse/tests/**.cpp")
    add_headerfiles(
        "iVerse/include/**.h"
    )
    add_includedirs(
        "iVerse/include"
    )
    add_cxxflags(
        "/utf-8",
        "/permissive-",
        "/EHa",
        "/W4",
        "/w44265",
        "/w44289",
        "/w44296",
        "/w45263",
        "/w44738",
        "/w45204"
    )
    add_defines(
        "_CRT_SECURE_NO_WARNINGS",
        "_ENABLE_CONSTEXPR_MUTEX_CONSTRUCTOR",
        "NOMINMAX",
        "UNICODE",
        "WIN32_LEAN_AND_MEAN"
    )
    add_packages(
        "iFamily"
    )
    set_languages("c++20")
target_end()