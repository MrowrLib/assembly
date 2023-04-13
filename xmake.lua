set_languages("c++20")
add_rules("mode.debug")
set_toolchains("msvc")

add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")

add_requires("xbyak", "zydis", "memory_util", "spdlog")

target("assembly")
    set_kind("headeronly")
    add_headerfiles("include/(**.h)")
    add_includedirs("include", {public = true})
    add_packages("zydis", "xbyak", {public = true})

target("Example")
    set_kind("binary")
    add_files("Example.cpp")
    add_deps("assembly")
    add_packages("memory_util", "spdlog")
