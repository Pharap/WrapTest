#pragma once

//
// Copyright (C) 2019 Pharap (@Pharap)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

//
// For more information about these utility functions, see:
// * https://github.com/Pharap/SizeDemo
// * https://github.com/Pharap/FlashStringHelperDemo
//

#if defined(ARDUINO)

// Include size_t
#include <stddef.h>

// Include __FlashStringHelper
#include <WString.h>

// Include pgm_read_ptr
#include <avr/pgmspace.h>

// Include Print
#include <Print.h>

#else

// Include std::size_t
#include <cstddef>

#endif

//
// getSize
//

#if defined(ARDUINO)

template< typename Type, size_t size >
constexpr size_t getSize(const Type (&)[size]) noexcept
{
	return size;
}

#else

template< typename Type, std::size_t size >
constexpr std::size_t getSize(const Type (&)[size]) noexcept
{
	return size;
}

#endif

#if defined(ARDUINO)

//
// FlashStringHelper
//

using FlashStringHelper = const __FlashStringHelper *;

//
// asFlashStringHelper
//

inline FlashStringHelper asFlashStringHelper(const char * flashString) noexcept
{
	return static_cast<FlashStringHelper>(static_cast<const void *>(flashString));
}

inline FlashStringHelper asFlashStringHelper(const unsigned char * flashString) noexcept
{
	return static_cast<FlashStringHelper>(static_cast<const void *>(flashString));
}

inline FlashStringHelper asFlashStringHelper(const signed char * flashString) noexcept
{
	return static_cast<FlashStringHelper>(static_cast<const void *>(flashString));
}

//
// readFlashString
//

inline FlashStringHelper readFlashStringPointer(const char * const * flashString) noexcept
{
	return static_cast<FlashStringHelper>(pgm_read_ptr(flashString));
}

inline FlashStringHelper readFlashStringPointer(const unsigned char * const * flashString) noexcept
{
	return static_cast<FlashStringHelper>(pgm_read_ptr(flashString));
}

inline FlashStringHelper readFlashStringPointer(const signed char * const * flashString) noexcept
{
	return static_cast<FlashStringHelper>(pgm_read_ptr(flashString));
}

#endif

#if defined(ARDUINO)

//
// std::istream-like shift operator
//

template<typename Type>
Print & operator <<(Print & printer, const Type & object)
{
	printer.print(object);
	return printer;
}

#endif