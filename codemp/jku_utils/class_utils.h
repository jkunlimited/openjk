/*
===========================================================================
Copyright (C) 2000 - 2013, Raven Software, Inc.
Copyright (C) 2001 - 2013, Activision, Inc.
Copyright (C) 2013 - 2015, OpenJK contributors
Copyright (C) 2019 - 2020, Jedi Knight Unlimited contributors

This file is part of the JKU source code.

OpenJK is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.
===========================================================================
*/

#pragma once

#ifndef _jku_class_utils
#define _jku_class_utils

#ifdef _WIN32
	#ifdef __cplusplus
	extern "C"
	{
	#endif
#else
	#ifdef __GNUG__
	extern "C"
	{
	#endif
#endif

// [ClassSystem]
#define	CLASS_INVALID			-1
#define	CLASS_GUNNER			 0
#define	CLASS_FORCE_SENSITIVE	 1

#define	CLASSPERK_INVALID		-1
#define	CLASSPERK_VANGUARD		 0
#define	CLASSPERK_GUNSLINGER	 1
#define	CLASSPERK_POWERTECH		 2
#define	CLASSPERK_OPERATIVE		 3
#define	CLASSPERK_COMBATMEDIC	 4
#define	CLASSPERK_SWORDSMAN		 5
// [/ClassSystem]

#ifdef _WIN32
#ifdef __cplusplus
	}
#endif
#else
#ifdef __GNUG__
	}
#endif
#endif

#endif