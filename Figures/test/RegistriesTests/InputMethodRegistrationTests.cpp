#include <memory>
#include <string>
#include <fstream>
#include <stdexcept>
#include "FileMethod.hpp"
#include "STDINMethod.hpp"
#include "RandomMethod.hpp"
#include "catch2/catch_all.hpp"
#include "InputMethodRegistry.hpp"
#include "InputMethodRegistration.hpp"

TEST_CASE("Builtin input methods are registered", "[input method registration]") {
    ensure_builtin_input_methods_registered();

    InputMethodRegistry& registry = InputMethodRegistry::instance();

    SECTION("Creates RandomMethod") {
        auto method = registry.create("Random");

        REQUIRE(method != nullptr);
        REQUIRE(method->get_method_name() == "Random");
        REQUIRE(dynamic_cast<RandomMethod*>(method.get()) != nullptr);
    }

    SECTION("Creates STDINMethod") {
        auto method = registry.create("STDIN");

        REQUIRE(method != nullptr);
        REQUIRE(method->get_method_name() == "STDIN");
        REQUIRE(dynamic_cast<STDINMethod*>(method.get()) != nullptr);
    }

    SECTION("Creates FileMethod") {
        const std::string filename = "input_method_registration_test.txt";

        {
            std::ofstream file(filename);
            REQUIRE(file.is_open());
            file << "circle 5\n";
        }

        auto method = registry.create("File " + filename);

        REQUIRE(method != nullptr);
        REQUIRE(method->get_method_name() == "File");
        REQUIRE(dynamic_cast<FileMethod*>(method.get()) != nullptr);

        std::remove(filename.c_str());
    }
}

TEST_CASE("Builtin input method registration is idempotent", "[input method registration]") {
    REQUIRE_NOTHROW(ensure_builtin_input_methods_registered());
    REQUIRE_NOTHROW(ensure_builtin_input_methods_registered());

    InputMethodRegistry& registry = InputMethodRegistry::instance();

    REQUIRE(registry.create("Random") != nullptr);
    REQUIRE(registry.create("STDIN") != nullptr);
}