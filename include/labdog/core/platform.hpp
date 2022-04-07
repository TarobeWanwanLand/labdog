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

//=========================================================
//	�R���p�C���g��(MSVC)
//=========================================================
/// @brief pragma warning(push), pragma warning(pop)
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