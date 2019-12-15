//
// Created by stuhlmeier on 11/22/19.
//

#ifndef LIBMUSUBI_UTIL_COMMON_H
#define LIBMUSUBI_UTIL_COMMON_H

#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>
#include <typeinfo>

#define LIBMUSUBI_DELCP(t) t(t const &other) = delete; t &operator=(t const &other) = delete;

#define LIBMUSUBI_PIMPL struct impl; ::musubi::pimpl_t<impl> pImpl;

namespace musubi {
    using namespace std::literals;

    using int8 = std::int_fast8_t;
    using int16 = std::int_fast16_t;
    using int32 = std::int_fast32_t;
    using int64 = std::int_fast64_t;

    using uint8 = std::uint_fast8_t;
    using uint16 = std::uint_fast16_t;
    using uint32 = std::uint_fast32_t;
    using uint64 = std::uint_fast64_t;

    template<typename T>
    constexpr T pi{3.141592653589793238462643383279502884L};

    template<typename Impl>
    using pimpl_t = std::unique_ptr<Impl>;

    constexpr std::string::size_type SCOPE_LENGTH = 16u;

    constexpr const char DEFAULT_SCOPE[] = "root";
    constexpr const char LOG_PREFIX[] = "musubi";
    constexpr const char LOG_PREFIX_INFO[] = "info    ";
    constexpr const char LOG_PREFIX_WARN[] = "warning:";
    constexpr const char LOG_PREFIX_ERROR[] = "ERROR!  ";

    inline std::ostream &log_base(std::ostream &stream, std::string_view &scope, const char *const &prefix) {
        return stream << LOG_PREFIX << '@'
                      << std::left << std::setw(SCOPE_LENGTH) << scope << std::resetiosflags(std::ios::adjustfield)
                      << ' ' << prefix << ' ';
    }

    inline std::ostream &log_i(std::string_view scope = DEFAULT_SCOPE) {
        return log_base(std::cout, scope, LOG_PREFIX_INFO);
    }

    inline std::ostream &log_w(std::string_view scope = DEFAULT_SCOPE) {
        return log_base(std::cerr, scope, LOG_PREFIX_WARN);
    }

    inline std::ostream &log_e(std::string_view scope = DEFAULT_SCOPE) {
        return log_base(std::cerr, scope, LOG_PREFIX_ERROR);
    }

    template<typename To, typename From>
    To numeric_cast(From from) {
        using limits = std::numeric_limits<To>;

        if (from <= limits::max()) return static_cast<To>(from);
        else if (from >= limits::min()) return static_cast<To>(from - limits::min()) + limits::min();
        else {
            throw std::domain_error(
                    std::string(typeid(From).name()) + " value "s + std::to_string(from)
                    + " is out of range of target type "s + typeid(To).name()
            );
        }
    }
}

#endif //LIBMUSUBI_UTIL_COMMON_H
