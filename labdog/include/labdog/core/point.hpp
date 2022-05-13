#ifndef LABDOG_POINT_HPP
#define LABDOG_POINT_HPP

#include "common.hpp"
#include <concepts>

namespace ld
{
    /// @brief 2次元座標(整数)
    struct point final
    {
    public:
        /// @brief 座標の要素型
        using value_type = int32;
        /// @brief 要素数を表す符号なし整数型
        using size_type = size_t;

        /// @brief 原点を指す座標を構築する
        constexpr point() noexcept
            : x{}
            , y{} {}

        /// @brief 要素の値から座標を構築する
        /// @param x x成分
        /// @param y y成分
        constexpr point(value_type x, value_type y) noexcept
            : x{ x }
            , y{ y } {}

        /// @brief デフォルトコピーコンストラクタ
        constexpr point(const point&) noexcept = default;

        /// @brief デフォルトムーブコンストラクタ
        constexpr point(point&&) noexcept = default;

        /// @brief デフォルトコピー代入
        constexpr point& operator=(const point&) noexcept = default;

        /// @brief デフォルトムーブ代入
        constexpr point& operator=(point&&) noexcept = default;

        /// @brief デフォルトデストラクタ
        ~point() noexcept = default;

        /// @brief 正の座標を返す
        /// @return 正の座標
        [[nodiscard]] constexpr point operator+() const noexcept
        {
            return *this;
        }

        /// @brief 負の座標を返す
        /// @return 負の座標
        [[nodiscard]] constexpr point operator-() const noexcept
        {
            return { -x, -y };
        }

        /// @brief 座標を加算する
        /// @param pt 加算する座標
        /// @return *this
        constexpr point& operator+=(point pt) noexcept
        {
            x += pt.x;
            y += pt.y;
            return *this;
        }

        /// @brief 座標を減算する
        /// @param pt 減算する座標
        /// @return *this
        constexpr point& operator-=(point pt) noexcept
        {
            x -= pt.x;
            y -= pt.y;
            return *this;
        }

        /// @brief 座標を乗算する
        /// @param s 乗算する値
        /// @return *this
        constexpr point& operator*=(value_type s) noexcept
        {
            x *= s;
            y *= s;
            return *this;
        }

        /// @brief 座標を除算する
        /// @param s 除算する値
        /// @return *this
        constexpr point& operator/=(value_type s) noexcept
        {
            x /= s;
            y /= s;
            return *this;
        }

        /// @brief 加算した座標を構築する
        /// @param pt 加算する座標
        /// @return 加算した座標
        [[nodiscard]] constexpr point operator+(point pt) const noexcept
        {
            return { x + pt.x, x + pt.y };
        }

        /// @brief 減算した座標を構築する
        /// @param pt 減算する座標
        /// @return 減算した座標
        [[nodiscard]]  constexpr point operator-(point pt) const noexcept
        {
            return { x - pt.x, x - pt.y };
        }

        /// @brief 乗算した座標を構築する
        /// @param s 乗算する値
        /// @return 乗算した座標
        [[nodiscard]] constexpr point operator*(value_type s) const noexcept
        {
            return { x * s, x * s };
        }

        /// @brief 除算した座標を構築する
        /// @param s 除算する値
        /// @return 除算した座標
        [[nodiscard]] constexpr point operator/(value_type s) const noexcept
        {
            return { x / s, x / s };
        }

        /// @brief 座標の成分を添字で取得する
        /// @param index 添字の値
        /// @return 座標の成分
        [[nodiscard]] constexpr value_type& operator[](size_type index)
        {
            switch (index)
            {
                case 0:
                    return x;
                case 1:
                    return y;
                default:
                    throw std::out_of_range("Attempted to access outside the scope of the element.");
            }
        }

        /// @brief 座標の成分を添字で取得する
        /// @param index 添字の値
        /// @return 座標の成分
        [[nodiscard]] constexpr const value_type& operator[](size_type index) const
        {
            switch (index)
            {
                case 0:
                    return x;
                case 1:
                    return y;
                default:
                    throw std::out_of_range("Attempted to access outside the scope of the element.");
            }
        }

        /// @brief 座標を等値比較する
        /// @param pt 比較対象の座標
        /// @return 等値であるか
        [[nodiscard]] constexpr bool operator==(point pt) const noexcept
        {
            return ((x == pt.x) && (y == pt.y));
        }

        /// @brief 座標を非等値比較する
        /// @param pt 比較対象の座標
        /// @return 非等値であるか
        [[nodiscard]] constexpr bool operator!=(point pt) const noexcept
        {
            return ((x != pt.x) || (y != pt.y));
        }

        /// @brief 座標が原点を指しているかを返す
        /// @return 座標が原点を指しているか
        [[nodiscard]] constexpr bool is_zero() const noexcept
        {
            return ((x == 0) && (y == 0));
        }

        /// @brief 原点を指す座標を返す
        [[nodiscard]] static constexpr point zero() noexcept
        {
            return { 0, 0 };
        }

        /// @brief 全ての成分が1の座標を返す
        [[nodiscard]] static constexpr point one() noexcept
        {
            return { 1, 1 };
        }

        /// @brief 原点から右方向へ移動させた座標を返す
        /// @param len 右方向への移動量
        [[nodiscard]] static constexpr point right (value_type amount = 1) noexcept
        {
            return { amount, 0 };
        }

        /// @brief 原点から左方向へ移動させた座標を返す
        /// @param len 左方向への移動量
        [[nodiscard]] static constexpr point left (value_type amount = 1) noexcept
        {
            return { -amount, 0 };
        }

        /// @brief 原点から下方向へ移動させた座標を返す
        /// @param len 下方向への移動量
        [[nodiscard]] static constexpr point down (value_type amount = 1) noexcept
        {
            return { 0, amount };
        }

        /// @brief 原点から上方向へ移動させた座標を返す
        /// @param len 上方向への移動量
        [[nodiscard]] static constexpr point up (value_type amount = 1) noexcept
        {
            return { 0, -amount };
        }

        value_type x; //!< x成分
        value_type y; //!< y成分
    };
}

#endif // LABDOG_POINT_HPP
