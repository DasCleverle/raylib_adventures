from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMakeToolchain

class RaylibAdventuresRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"
    build_policy = "missing"

    def requirements(self):
        self.requires("raylib/5.0")
        self.requires("tl-expected/1.1.0")
        self.requires("tl-optional/1.1.0")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.cache_variables["CMAKE_EXPORT_COMPILE_COMMANDS"] = True
        tc.generate()

    def layout(self):
        cmake_layout(self)

