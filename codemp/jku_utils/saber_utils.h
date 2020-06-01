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

#ifndef _jku_utils
#define _jku_utils

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

   #include <qcommon/q_math.h>
   #include <qcommon/q_shared.h>
   #include <qcommon/q_platform.h>
   #include <game/g_local.h>
   #include <game/bg_local.h>
   #include <game/ai_main.h>
   #include <ghoul2/G2.h>

   extern void JKU_calculateSaberTrace(gentity_t *self,
      int rSaberNum,
      int rBladeNum,
      vec3_t saberStart,
      vec3_t saberEnd,
      qboolean doInterpolate,
      int trMask,
      qboolean extrapolate,
      vec3_t saberTrMins,
      vec3_t saberTrMaxs,
      vec3_t lastValidStart,
      vec3_t lastValidEnd,
      trace_t* tr);

   extern float JKU_calculateSaberHitAngle(gentity_t* self,
      gentity_t* other);

   extern float JKU_calculateAttackAngle(gentity_t* self,
      gentity_t* other);

   extern float JKU_radToDeg(float radians);

   extern int JKU_calculateSaberDamage(gentity_t *self);

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