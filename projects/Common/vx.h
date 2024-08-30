#pragma once

#include <any>
#include <iostream>
#include <optional>
#include <tuple>
#include <type_traits>
#include <variant>

// https://github.com/AVasK/vx/blob/main/vx.hpp

namespace vx {

    // ===== [ try_find ] =====
    namespace detail {
        template<typename X, typename... Ts>
        struct try_find_impl {};

        template<typename X, typename T, typename... Ts>
        struct try_find_impl<X, T, Ts...> {
            static constexpr std::optional<size_t> try_find(size_t index = 0) noexcept { return try_find_impl<X, Ts...>::try_find(index + 1); }
        };

        template<typename T, typename... Ts>
        struct try_find_impl<T, T, Ts...> {
            static constexpr std::optional<size_t> try_find(size_t index = 0) noexcept { return {index}; }
        };

        template<typename X>
        struct try_find_impl<X> {
            static constexpr std::optional<size_t> try_find(size_t = 0) noexcept { return {}; }
        };
    } // namespace detail

    template<typename X, typename... Ts>
    constexpr std::optional<size_t> try_find(size_t index = 0) {
        return detail::try_find_impl<X, Ts...>::try_find(index);
    }

    // =====[ at ]=====
    template<size_t I>
    struct at_t : std::in_place_index_t<I> {};
    template<size_t I>
    inline constexpr at_t<I> at;

    template<typename T, size_t I>
#if defined __cpp_concepts && __cplusplus >= __cpp_concepts
        requires requires(T object) {
            { std::get<I>(object) };
        }
#endif
    decltype(auto) operator|(T && v, at_t<I>) {
        return std::get<I>(std::forward<T>(v));
    }


    // =====[ as ]=====
    template<typename T>
    struct as_t : std::in_place_type_t<T> {};
    template<typename T>
    inline constexpr as_t<T> as;

    // generic case : as acts as a static_cast (for non-variant types)
    template<typename From, typename To>
    constexpr auto operator|(From const& value, as_t<To>) {
        return static_cast<To>(value);
    }

    // =====[ variant|as ]=====
    template<typename... Ts, typename Type>
    constexpr decltype(auto) operator|(std::variant<Ts...>& variant, as_t<Type>) {
        return std::get<Type>(variant);
    }

    template<typename... Ts, typename Type>
    constexpr decltype(auto) operator|(std::variant<Ts...> const& variant, as_t<Type>) {
        return std::get<Type>(variant);
    }

    template<typename... Ts, typename Type>
    constexpr decltype(auto) operator|(std::variant<Ts...>&& variant, as_t<Type>) {
        return std::get<Type>(std::move(variant));
    }

    // =====[ any|as ]=====
    template<typename Type>
    constexpr decltype(auto) operator|(std::any & a, as_t<Type>) {
        return std::any_cast<Type>(a);
    }

    template<typename Type>
    constexpr decltype(auto) operator|(std::any const& a, as_t<Type>) {
        return std::any_cast<Type>(a);
    }

    template<typename Type>
    constexpr decltype(auto) operator|(std::any && a, as_t<Type>) {
        return std::any_cast<Type>(std::move(a));
    }


    // =====[ is ]=====
    template<typename T>
    struct compare {};
    template<typename T>
    inline constexpr compare<T> is{};

    // =====[ variant|is ]=====
    template<typename... Ts, typename Type>
#if defined __cpp_concepts && __cplusplus >= __cpp_concepts
        requires(try_find<Type, Ts...>() | as<bool>)
#endif
    constexpr bool operator|(std::variant<Ts...> const& variant, compare<Type>) {
        return std::holds_alternative<Type>(variant);
    }

// =====[ any|is ]=====
//! constexpr just for being futureproof :)
#if defined __cpp_concepts && __cplusplus >= __cpp_concepts
    template<typename Type, typename Any>
        requires std::same_as<Any, std::any>
#else
    template<typename Type, typename Any, typename = std::enable_if_t<std::is_same_v<Any, std::any>>>
#endif
    constexpr bool operator|(Any const& a, compare<Type>) {
        return a.type() == typeid(Type);
    }


    // =====[ match ]=====
    template<typename... Fs>
    struct match : Fs... {
        using Fs::operator()...;

        // constexpr match(Fs &&... fs) : Fs{fs}... {}
    };
    template<class... Ts>
    match(Ts...) -> match<Ts...>;

    template<typename... Ts, typename... Fs>
    constexpr decltype(auto) operator|(std::variant<Ts...> const& v, match<Fs...> const& match) {
        return std::visit(match, v);
    }

    template<typename... Ts, typename... Fs>
    constexpr decltype(auto) operator|(std::variant<Ts...>& v, match<Fs...> const& match) {
        return std::visit(match, v);
    }

    // =====[ optional match ]=====
    template<typename T, typename... Fs>
#if defined __cpp_concepts && __cplusplus >= __cpp_concepts
        requires(std::is_invocable_v<match<Fs...>, T> && std::is_invocable_v<match<Fs...>>) //&& requires(match<Fs...> const& match){ {match()}; })
#endif
    constexpr decltype(auto) operator|(std::optional<T> const& o, match<Fs...> const& match) {
        if (o.has_value())
            return match(o.value());
        else
            return match();
    }

} // namespace vx
