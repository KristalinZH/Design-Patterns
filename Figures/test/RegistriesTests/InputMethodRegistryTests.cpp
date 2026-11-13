#include <memory>
#include <string>
#include <stdexcept>
#include "InputMethod.hpp"
#include "FigureFactory.hpp"
#include "catch2/catch_all.hpp"
#include "InputMethodRegistry.hpp"

// Тестова имплементация на InputMethod.
namespace {
    class TestInputMethod : public InputMethod {
    public:
        explicit TestInputMethod(const std::string& input)
            : input(input) {}

        std::string get_method_name() const override {
            return "Test";
        }

        std::unique_ptr<FigureFactory> create_factory() const override {
            return nullptr;
        }

        const std::string& get_input() const {
            return input;
        }

    private:
        std::string input;
    };
}

TEST_CASE("InputMethodRegistry is a Singleton", "[input method registry]") {
    InputMethodRegistry& first = InputMethodRegistry::instance();
    InputMethodRegistry& second = InputMethodRegistry::instance();

    REQUIRE(&first == &second);
}

TEST_CASE("InputMethodRegistry registers and creates methods", "[input method registry]") {
    InputMethodRegistry& registry = InputMethodRegistry::instance();

    SECTION("Registers and creates a method") {
        registry.register_method(
            "test_register_create",
            [](const std::string& input) {
                return std::make_unique<TestInputMethod>(input);
            }
        );

        auto method = registry.create("test_register_create some parameters");

        REQUIRE(method != nullptr);
        REQUIRE(method->get_method_name() == "Test");
    }

    SECTION("Passes the complete input string to the creator") {
        const std::string expected_input =
            "test_complete_input some parameters";

        registry.register_method(
            "test_complete_input",
            [](const std::string& input) {
                return std::make_unique<TestInputMethod>(input);
            }
        );

        auto method = registry.create(expected_input);

        auto* test_method = dynamic_cast<TestInputMethod*>(method.get());

        REQUIRE(test_method != nullptr);
        REQUIRE(test_method->get_input() == expected_input);
    }
}

TEST_CASE("InputMethodRegistry rejects invalid registrations", "[input method registry]") {
    InputMethodRegistry& registry = InputMethodRegistry::instance();

    SECTION("Rejects an empty method name") {
        REQUIRE_THROWS_AS(
            registry.register_method(
                "",
                [](const std::string&) {
                    return std::make_unique<TestInputMethod>("test");
                }
            ),
            std::invalid_argument
        );
    }

    SECTION("Rejects an empty creator") {
        REQUIRE_THROWS_AS(
            registry.register_method("test_empty_creator", nullptr),
            std::invalid_argument
        );
    }

    SECTION("Rejects duplicate method names") {
        registry.register_method(
            "test_duplicate_method",
            [](const std::string& input) {
                return std::make_unique<TestInputMethod>(input);
            }
        );

        REQUIRE_THROWS_AS(
            registry.register_method(
                "test_duplicate_method",
                [](const std::string& input) {
                    return std::make_unique<TestInputMethod>(input);
                }
            ),
            std::invalid_argument
        );
    }
}

TEST_CASE("InputMethodRegistry rejects invalid input", "[input method registry]") {
    InputMethodRegistry& registry = InputMethodRegistry::instance();

    SECTION("Rejects empty input") {
        REQUIRE_THROWS_AS(
            registry.create(""),
            std::invalid_argument
        );
    }

    SECTION("Rejects input containing only whitespace") {
        REQUIRE_THROWS_AS(
            registry.create("   \t  "),
            std::invalid_argument
        );
    }

    SECTION("Rejects unknown method names") {
        REQUIRE_THROWS_AS(
            registry.create("unknown_method"),
            std::invalid_argument
        );
    }
}
