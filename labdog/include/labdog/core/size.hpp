#ifndef LABDOG_SIZE2D_HPP
#define LABDOG_SIZE2D_HPP

#include "common.hpp"
#include <concepts>
#include <stdexcept>

namespace ld
{
    /// @brief 2次元サイズ(整数)
    struct size final
    {
    public:
        /// @brief 幅の長さを表す整数型
        using value_type = int32;
        /// @brief 要素数を表す符号なし整数型
        using size_type = size_t;

        value_type width;  //!< 横幅
        value_type height; //!< 縦幅

        /// @brief 全ての幅が0の2次元サイズを構築する
        [[nodiscard]] constexpr size() noexcept
            : width{}
            , height{} {}

        /// @brief 各幅の値から2次元サイズを構築する
        /// @param width 横幅
        /// @param height 縦幅
        [[nodiscard]] constexpr size(value_type width, value_type height) noexcept
            : width{ width }
            , height{ height } {}

        /// @brief 各幅の値から2次元サイズを構築する
        /// @param width 横幅
        /// @param height 縦幅
        template <std::integral Width, std::integral Height>
        [[nodiscard]] constexpr size(Width width, Height height) noexcept
            : width{ static_cast<value_type>(width) }
            , height{ static_cast<value_type>(height) } {}

        /// @brief 暗黙のキャストによる構築を禁止
        size(auto, auto) = delete;

        /// @brief デフォルトコピーコンストラクタ
        constexpr size(const size&) noexcept = default;

        /// @brief デフォルトムーブコンストラクタ
        constexpr size(size&&) noexcept = default;

        /// @brief デフォルトコピー代入
        constexpr size& operator=(const size& s) noexcept
        {
            width = s.width;
            height = s.height;
            return *this;
        }

        /// @brief デフォルトムーブ代入
        constexpr size& operator=(size&&) noexcept = default;

        /// @brief デフォルトデストラクタ
        ~size() noexcept = default;

        /// @brief 正の2次元サイズを返す
        /// @return 正の2次元サイズ
        [[nodiscard]] constexpr size operator+() const noexcept
        {
            return *this;
        }

        /// @brief 負の2次元サイズを返す
        /// @return 負の2次元サイズ
        [[nodiscard]] constexpr size operator-() const noexcept
        {
            return {-width, -height };
        }

        /// @brief 2次元サイズを加算する
        /// @param s 加算する2次元サイズ
        /// @return *this
        constexpr size& operator+=(size s) noexcept
        {
            width += s.width;
            height += s.height;
            return *this;
        }

        /// @brief 2次元サイズを減算する
        /// @param s 減算する2次元サイズ
        /// @return *this
        constexpr size& operator-=(size s) noexcept
        {
            width -= s.width;
            height -= s.height;
            return *this;
        }

        /// @brief 2次元サイズを乗算する
        /// @param s 乗算する値
        /// @return *this
        constexpr size& operator*=(value_type s) noexcept
        {
            width *= s;
            height *= s;
            return *this;
        }

        /// @brief 2次元サイズを除算する
        /// @param s 除算する値
        /// @return *this
        constexpr size& operator/=(value_type s) noexcept
        {
            width /= s;
            height /= s;
            return *this;
        }

        /// @brief 加算した2次元サイズを構築する
        /// @param s 加算する2次元サイズ
        /// @return 加算した2次元サイズ
        [[nodiscard]] constexpr size operator+(size s) const noexcept
        {
            return {width + s.width, width + s.height };
        }

        /// @brief 減算した2次元サイズを構築する
        /// @param s 減算する2次元サイズ
        /// @return 減算した2次元サイズ
        [[nodiscard]]  constexpr size operator-(size s) const noexcept
        {
            return {width - s.width, width - s.height };
        }

        /// @brief 乗算した2次元サイズを構築する
        /// @param s 乗算する値
        /// @return 乗算した2次元サイズ
        [[nodiscard]] constexpr size operator*(value_type s) const noexcept
        {
            return {width * s, width * s };
        }

        /// @brief 除算した2次元サイズを構築する
        /// @param s 除算する値
        /// @return 除算した2次元サイズ
        [[nodiscard]] constexpr size operator/(value_type s) const noexcept
        {
            return {width / s, width / s };
        }

        /// @brief 2次元サイズの成分を添字で取得する
        /// @param index 添字の値
        /// @return 2次元サイズの成分
        [[nodiscard]] constexpr value_type& operator[](size_type index)
        {
            switch (index)
            {
                case 0:
                    return width;
                case 1:
                    return height;
                default:
                    throw std::out_of_range("Attempted to access outside the scope of the element.");
            }
        }

        /// @brief 2次元サイズの成分を添字で取得する
        /// @param index 添字の値
        /// @return 2次元サイズの成分
        [[nodiscard]] constexpr const value_type& operator[](size_type index) const
        {
            switch (index)
            {
                case 0:
                    return width;
                case 1:
                    return height;
                default:
                    throw std::out_of_range("Attempted to access outside the scope of the element.");
            }
        }

        /// @brief 2次元サイズを等値比較する
        /// @param s 比較対象の2次元サイズ
        /// @return 等値であるか
        [[nodiscard]] constexpr bool operator==(size s) const noexcept
        {
            return ((width == s.width) && (height == s.height));
        }

        /// @brief 2次元サイズを非等値比較する
        /// @param s 比較対象の2次元サイズ
        /// @return 非等値であるか
        [[nodiscard]] constexpr bool operator!=(size s) const noexcept
        {
            return ((width != s.width) || (height != s.height));
        }

        /// @brief 2次元サイズの面積を求める
        /// @return 2次元サイズの面積
        [[nodiscard]] constexpr value_type area() const noexcept
        {
            return width * height;
        }

        /// @brief 2次元サイズの全ての幅が0かを求める
        /// @return 2次元サイズの全ての幅が0か
        [[nodiscard]] constexpr bool is_zero() const noexcept
        {
            return ((width == 0) && (height == 0));
        }

        /// @brief 全ての幅が0の2次元サイズを返す
        [[nodiscard]] static constexpr size zero() noexcept
        {
            return { 0, 0 };
        }

        /// @brief 全ての幅が1の2次元サイズを返す
        [[nodiscard]] static constexpr size one() noexcept
        {
            return { 1, 1 };
        }
    };
}

#endif // LABDOG_SIZE2D_HPP
