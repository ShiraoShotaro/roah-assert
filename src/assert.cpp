#include "roah/assert.hpp"

#include <cstdint>
#include <format>
#include <iostream>
#include <source_location>
#include <stdexcept>
#include <string_view>

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// AssertionError class implementation
//
///////////////////////////////////////////////////////////////////////////////////////////////////
roah::serv::AssertionError::AssertionError(const std::string_view expr, const std::source_location & source_location)
    : std::logic_error{ std::format("AssertionError. {} - {}#{} {}()",
                                    expr,
                                    source_location.file_name(),
                                    source_location.line(),
                                    source_location.function_name()) }
    , expr_{ expr }
    , source_location_{ source_location }
{}

roah::serv::AssertionError::AssertionError(const AssertionError &) = default;

roah::serv::AssertionError::AssertionError(AssertionError &&) noexcept = default;

roah::serv::AssertionError::~AssertionError() noexcept = default;

roah::serv::AssertionError &
roah::serv::AssertionError::operator=(const AssertionError &)
    = default;

roah::serv::AssertionError &
roah::serv::AssertionError::operator=(AssertionError &&) noexcept
    = default;

std::string_view
roah::serv::AssertionError::getExpr() const noexcept
{
    return this->expr_;
}

const char *
roah::serv::AssertionError::getFilename() const noexcept
{
    return this->source_location_.file_name();
}

std::uint_least32_t
roah::serv::AssertionError::getLine() const noexcept
{
    return this->source_location_.line();
}

const char *
roah::serv::AssertionError::getFunctionName() const noexcept
{
    return this->source_location_.function_name();
}

const std::source_location &
roah::serv::AssertionError::getSourceLocation() const noexcept
{
    return this->source_location_;
}

void
roah::serv::AssertionError::printMessage(const std::string_view expr, const std::source_location & source_location)
{
    AssertionError::printMessage(expr, source_location, "");
}

void
roah::serv::AssertionError::printMessage(const std::string_view       expr,
                                         const std::source_location & source_location,
                                         const std::string_view       message)
{
    std::cerr << std::format("Assertion Fault. {} - {}#{} {}\n",
                             expr,
                             source_location.file_name(),
                             source_location.line(),
                             source_location.function_name())
              << std::endl;
    if (!message.empty())
    {
        std::cerr << std::format("-- Message: {}\n", message);
    }
}
