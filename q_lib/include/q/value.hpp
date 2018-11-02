/*=============================================================================
   Copyright (c) 2014-2018 Joel de Guzman. All rights reserved.

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#if !defined(CYCFI_Q_VALUE_HPP_MAY_21_2018)
#define CYCFI_Q_VALUE_HPP_MAY_21_2018

#include <type_traits>

namespace cycfi { namespace q
{
   ////////////////////////////////////////////////////////////////////////////
   // value: Value abstraction and encapsulation
   ////////////////////////////////////////////////////////////////////////////
   template <typename T, typename Derived>
   struct value
   {
      using derived_type = Derived;
      using value_type = T;

      constexpr explicit            value(T val = T(0)) : val(val) {}
      constexpr                     value(value const&) = default;
      constexpr                     value(value&&) = default;

      constexpr value&              operator=(value const&) = default;
      constexpr value&              operator=(value&&) = default;

      constexpr explicit operator   T() const         { return val; }
      constexpr derived_type        operator+() const { return derived(); }
      constexpr derived_type        operator-() const { return derived_type{-val}; }

      constexpr derived_type&       operator+=(value rhs);
      constexpr derived_type&       operator-=(value rhs);
      constexpr derived_type&       operator*=(value rhs);
      constexpr derived_type&       operator/=(value rhs);

      constexpr derived_type const& derived() const;
      constexpr derived_type&       derived();

      T val;
   };

   ////////////////////////////////////////////////////////////////////////////
   template <typename T, typename Derived>
   constexpr typename value<T, Derived>::derived_type const&
   value<T, Derived>::derived() const
   {
      return *static_cast<derived_type const*>(this);
   }

   template <typename T, typename Derived>
   constexpr typename value<T, Derived>::derived_type&
   value<T, Derived>::derived()
   {
      return *static_cast<derived_type*>(this);
   }

   ////////////////////////////////////////////////////////////////////////////
   template <typename T, typename Derived>
   constexpr bool operator==(value<T, Derived> a, value<T, Derived> b)
   {
      return a.val == b.val;
   }

   template <typename T, typename Derived>
   constexpr bool operator==(T a, value<T, Derived> b)
   {
      return a == b.val;
   }

   template <typename T, typename Derived>
   constexpr bool operator==(value<T, Derived> a, T b)
   {
      return a.val == b;
   }

   ////////////////////////////////////////////////////////////////////////////
   template <typename T, typename Derived>
   constexpr bool operator!=(value<T, Derived> a, value<T, Derived> b)
   {
      return a.val != b.val;
   }

   template <typename T, typename Derived>
   constexpr bool operator!=(T a, value<T, Derived> b)
   {
      return a != b.val;
   }

   template <typename T, typename Derived>
   constexpr bool operator!=(value<T, Derived> a, T b)
   {
      return a.val != b;
   }

   ////////////////////////////////////////////////////////////////////////////
   template <typename T, typename Derived>
   constexpr bool operator<(value<T, Derived> a, value<T, Derived> b)
   {
      return a.val < b.val;
   }

   template <typename T, typename Derived>
   constexpr bool operator<(T a, value<T, Derived> b)
   {
      return a < b.val;
   }

   template <typename T, typename Derived>
   constexpr bool operator<(value<T, Derived> a, T b)
   {
      return a.val < b;
   }

   ////////////////////////////////////////////////////////////////////////////
   template <typename T, typename Derived>
   constexpr bool operator<=(value<T, Derived> a, value<T, Derived> b)
   {
      return a.val <= b.val;
   }

   template <typename T, typename Derived>
   constexpr bool operator<=(T a, value<T, Derived> b)
   {
      return a <= b.val;
   }

   template <typename T, typename Derived>
   constexpr bool operator<=(value<T, Derived> a, T b)
   {
      return a.val <= b;
   }

   ////////////////////////////////////////////////////////////////////////////
   template <typename T, typename Derived>
   constexpr bool operator>(value<T, Derived> a, value<T, Derived> b)
   {
      return a.val > b.val;
   }

   template <typename T, typename Derived>
   constexpr bool operator>(T a, value<T, Derived> b)
   {
      return a > b.val;
   }

   template <typename T, typename Derived>
   constexpr bool operator>(value<T, Derived> a, T b)
   {
      return a.val > b;
   }

   ////////////////////////////////////////////////////////////////////////////
   template <typename T, typename Derived>
   constexpr bool operator>=(value<T, Derived> a, value<T, Derived> b)
   {
      return a.val >= b.val;
   }

   template <typename T, typename Derived>
   constexpr bool operator>=(T a, value<T, Derived> b)
   {
      return a >= b.val;
   }

   template <typename T, typename Derived>
   constexpr bool operator>=(value<T, Derived> a, T b)
   {
      return a.val >= b;
   }

   ////////////////////////////////////////////////////////////////////////////
   template <typename T, typename Derived>
   constexpr Derived& value<T, Derived>::operator+=(value<T, Derived> rhs)
   {
      val += rhs.val;
      return derived();
   }

   template <typename T, typename Derived>
   constexpr Derived& value<T, Derived>::operator-=(value<T, Derived> rhs)
   {
      val -= rhs.val;
      return derived();
   }

   template <typename T, typename Derived>
   constexpr Derived& value<T, Derived>::operator*=(value<T, Derived> rhs)
   {
      val *= rhs.val;
      return derived();
   }

   template <typename T, typename Derived>
   constexpr Derived& value<T, Derived>::operator/=(value<T, Derived> rhs)
   {
      val /= rhs.val;
      return derived();
   }

   ////////////////////////////////////////////////////////////////////////////
   template <typename T, typename Derived>
   constexpr Derived operator+(value<T, Derived> a, value<T, Derived> b)
   {
      return Derived(a.val + b.val);
   }

   template <typename T, typename Derived>
   constexpr Derived operator-(value<T, Derived> a, value<T, Derived> b)
   {
      return Derived(a.val - b.val);
   }

   template <typename T, typename Derived>
   constexpr Derived operator*(value<T, Derived> a, value<T, Derived> b)
   {
      return Derived(a.val * b.val);
   }

   template <typename T, typename Derived>
   constexpr Derived operator/(value<T, Derived> a, value<T, Derived> b)
   {
      return Derived(a.val / b.val);
   }

   ////////////////////////////////////////////////////////////////////////////
   template <typename T, typename Derived, typename T2>
   constexpr typename std::enable_if<
      !std::is_same<Derived, T2>::value, Derived
   >::type
   operator+(T2 a, value<T, Derived> b)
   {
      return Derived(a + b.val);
   }

   template <typename T, typename Derived, typename T2>
   constexpr typename std::enable_if<
     !std::is_same<Derived, T2>::value, Derived
   >::type
   operator-(T2 a, value<T, Derived> b)
   {
      return Derived(a - b.val);
   }

   template <typename T, typename Derived, typename T2>
   constexpr typename std::enable_if<
      !std::is_same<Derived, T2>::value, Derived
   >::type
   operator*(T2 a, value<T, Derived> b)
   {
      return Derived(a * b.val);
   }

   template <typename T, typename Derived, typename T2>
   constexpr typename std::enable_if<
      !std::is_same<Derived, T2>::value, Derived
   >::type
   operator/(T2 a, value<T, Derived> b)
   {
      return Derived(a / b.val);
   }

   ////////////////////////////////////////////////////////////////////////////
   template <typename T, typename Derived, typename T2>
   constexpr typename std::enable_if<
      !std::is_same<Derived, T2>::value, Derived
   >::type
   operator+(value<T, Derived> a, T2 b)
   {
      return Derived(a.val + b);
   }

   template <typename T, typename Derived, typename T2>
   constexpr typename std::enable_if<
      !std::is_same<Derived, T2>::value, Derived
   >::type
   operator-(value<T, Derived> a, T2 b)
   {
      return Derived(a.val - b);
   }

   template <typename T, typename Derived, typename T2>
   constexpr typename std::enable_if<
      !std::is_same<Derived, T2>::value, Derived
   >::type
   operator*(value<T, Derived> a, T2 b)
   {
      return Derived(a.val * b);
   }

   template <typename T, typename Derived, typename T2>
   constexpr typename std::enable_if<
      !std::is_same<Derived, T2>::value, Derived
   >::type
   operator/(value<T, Derived> a, T2 b)
   {
      return Derived(a.val / b);
   }
}}

#endif
