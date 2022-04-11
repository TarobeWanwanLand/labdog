//=========================================================
//
//	platform.hpp
//	Copyright(c) 2022 Tomomi murakami.
//
//	Released under the MIT license.
//	see http://opensource.org/licenses/MIT
//
//=========================================================

#pragma once

//=========================================================
//	�v���b�g�t�H�[��
//=========================================================
/// @brief �v���b�g�t�H�[�����T�|�[�g�Ώۂ�
#ifndef _WIN32 // Windows�ȊO�͔�T�|�[�g
	#error Unsupported platform.
#elif !defined(_WIN64) // x86�͔�T�|�[�g
	#error Windows x86 is not supported.
#endif

//=========================================================
//	�r���h�ݒ�
//=========================================================
/// @brief �r���h�^�C�v���f�o�b�O��
#if defined(_DEBUG) || defined(DEBUG) // �f�o�b�O�r���h
	#define LABDOG_BUILD_TYPE_DEBUG true
#else
	#define LABDOG_BUILD_TYPE_DEBUG false
#endif

/// @brief STL�̃o�[�W����
#ifdef _MSVC
    #define LABDOG_STL_LANG _MSVC_LANG
#elif defined(__cplusplus)
    #define LABDOG_STL_LANG __cplusplus
#else
    #define LABDOG_STL_LANG 0L
#endif

#if __has_cpp_attribute(nodiscard) >= 201907L
    #define LABDOG_NODISCARD_CXX20 [[nodiscard]]
#else
    #define LABDOG_NODISCARD_CXX20
#endif

/// @brief �x���̃v�b�V��/�|�b�v
#ifdef _MSC_VER
	#define LABDOG_DISABLE_WARNINGS_PUSH(warnings)		\
			 __pragma(warning(push))					\
			 __pragma(warning(disable: warnings))
	#define LABDOG_DISABLE_WARNINGS_POP()				\
			 __pragma(warning(pop))
#else
	#define LABDOG_DISABLE_WARNINGS_PUSH(warnings)
	#define LABDOG_DISABLE_WARNINGS_POP()
#endif