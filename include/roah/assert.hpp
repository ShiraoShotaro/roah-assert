#ifndef ROAH_SERV_ASSERTION_HPP
#define ROAH_SERV_ASSERTION_HPP

#include <cstdint>
#include <source_location>
#include <stdexcept>
#include <string_view>

namespace roah::serv {

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief assert の代わりに使用される Exception.
///
/// 通常デバッグ時では, アサーションには assert が使用されるが,
/// リリース版時にあえてアサーションを有効にしたい場合に, assert の代わりにこの例外が送出されます.
///
class AssertionError : public std::logic_error
{
public:
    // ========================================================================================= //
    /// @name Constructor / Destructor
    // ========================================================================================= //
    /// @{

    /// @brief Constructor.
    ///
    /// ROAH_ASSERTION マクロから呼び出されることを想定しています.
    explicit AssertionError(const std::string_view expr, const std::source_location & source_location);

    /// @brief Copy constructor.
    AssertionError(const AssertionError &);

    /// @brief Move constructor.
    AssertionError(AssertionError &&) noexcept;

    /// @brief Destructor.
    ~AssertionError() noexcept;

    /// @brief Copy assignment operator.
    AssertionError &
    operator=(const AssertionError &);

    /// @brief Move assignment operator.
    AssertionError &
    operator=(AssertionError &&) noexcept;

    /// @}
    // ========================================================================================= //
    /// @name Getter
    // ========================================================================================= //
    /// @{

    /// @brief true になるべき検査条件を取得します.
    std::string_view
    getExpr() const noexcept;

    /// @brief エラー箇所のソースファイル名を取得します.
    const char *
    getFilename() const noexcept;

    /// @brief エラー箇所の行数を取得します.
    std::uint_least32_t
    getLine() const noexcept;

    /// @brief エラー箇所の関数名を取得します.
    const char *
    getFunctionName() const noexcept;

    /// @brief エラー箇所について source_location オブジェクトを取得します.
    const std::source_location &
    getSourceLocation() const noexcept;

    /// @}
    // ========================================================================================= //
    /// @name Utilities
    // ========================================================================================= //
    /// @{

    /// @brief Assertion Message をログへ書き出す.
    ///
    /// spdlog を隠ぺいするため static 関数を設けた.
    static void
    printMessage(const std::string_view expr, const std::source_location & source_location);

    /// @brief Assertion Message を, 追加メッセージとともにログへ書き出す.
    ///
    /// spdlog を隠ぺいするため static 関数を設けた.
    static void
    printMessage(const std::string_view       expr,
                 const std::source_location & source_location,
                 const std::string_view       message);

    /// @}

private:
    std::string_view     expr_;
    std::source_location source_location_;
};

}  // namespace roah::serv

// --- Assertion Macros ---
#ifdef ROAH_DEBUG
#    include <cassert>
#    define ROAH_ASSERTION(expr)                                                            \
        if (!(expr)) [[unlikely]]                                                           \
        {                                                                                   \
            ::pastel::AssertionError::printMessage(#expr, std::source_location::current()); \
            assert(false && #expr);                                                         \
        }
#    define ROAH_ASSERTION_C(expr)                                                          \
        if constexpr (!(expr))                                                              \
        {                                                                                   \
            ::pastel::AssertionError::printMessage(#expr, std::source_location::current()); \
            assert(false && #expr);                                                         \
        }
#else
#    define ROAH_ASSERTION(expr)
#    define ROAH_ASSERTION_C(expr)
#endif

// --- Not Implemented Macro ---
#ifdef ROAH_DEBUG
#    define ROAH_NOT_IMPLEMENTED()                                                                  \
        ::pastel::AssertionError::printMessage("NOT IMPLEMENTED", std::source_location::current()); \
        assert(false && "NOT IMPLEMENTED")
#else
#    define ROAH_NOT_IMPLEMENTED() \
        ::pastel::AssertionError::printMessage("NOT IMPLEMENTED", std::source_location::current())
#endif

// --- Coding Error Macros ---
#define ROAH_CODING_ERROR(expr)                                                      \
    if (!(expr)) [[unlikely]]                                                        \
    {                                                                                \
        ::pastel::CodingError::printMessage(#expr, std::source_location::current()); \
        throw ::pastel::CodingError{ #expr, std::source_location::current() };       \
    }
#define ROAH_CODING_ERROR_C(expr)                                                    \
    if constexpr (!(expr))                                                           \
    {                                                                                \
        ::pastel::CodingError::printMessage(#expr, std::source_location::current()); \
        throw ::pastel::CodingError{ #expr, std::source_location::current() };       \
    }
#define ROAH_CODING_ERROR_M(expr, msg)                                                    \
    if (!(expr)) [[unlikely]]                                                             \
    {                                                                                     \
        ::pastel::CodingError::printMessage(#expr, std::source_location::current(), msg); \
        throw ::pastel::CodingError{ #expr, std::source_location::current() };            \
    }
#define ROAH_CODING_ERROR_M_C(expr, msg)                                                  \
    if constexpr (!(expr))                                                                \
    {                                                                                     \
        ::pastel::CodingError::printMessage(#expr, std::source_location::current(), msg); \
        throw ::pastel::CodingError{ #expr, std::source_location::current() };            \
    }

#endif
