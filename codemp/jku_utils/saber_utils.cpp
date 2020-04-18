/*
===========================================================================
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

#include "saber_utils.h"
#include <cmath>
#include <vector>
#include <numeric>

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

#include <game/w_saber.h>

void JKU_calculateSaberTrace(gentity_t *self,
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
   trace_t* tr)
{
   float saberBoxSize = d_saberBoxTraceSize.value;
   qboolean saberTraceDone = qfalse;

   //Add the standard radius into the box size
   saberBoxSize += (self->client->saber[rSaberNum].blade[rBladeNum].radius*0.5f);

   if (self->client->ps.weaponTime <= 0)
   { //if not doing any attacks or anything, just use point traces.
      VectorClear(saberTrMins);
      VectorClear(saberTrMaxs);
   }
   else if (d_saberGhoul2Collision.integer)
   {
      if (d_saberSPStyleDamage.integer)
      {//SP-size saber damage traces
         VectorSet(saberTrMins, -2, -2, -2);
         VectorSet(saberTrMaxs, 2, 2, 2);
      }
      else
      {
         VectorSet(saberTrMins, -saberBoxSize * 3, -saberBoxSize * 3, -saberBoxSize * 3);
         VectorSet(saberTrMaxs, saberBoxSize * 3, saberBoxSize * 3, saberBoxSize * 3);
      }
   }
   else if (self->client->ps.fd.saberAnimLevel < FORCE_LEVEL_2)
   { //box trace for fast, because it doesn't get updated so often
      VectorSet(saberTrMins, -saberBoxSize, -saberBoxSize, -saberBoxSize);
      VectorSet(saberTrMaxs, saberBoxSize, saberBoxSize, saberBoxSize);
   }
   else if (d_saberAlwaysBoxTrace.integer)
   {
      VectorSet(saberTrMins, -saberBoxSize, -saberBoxSize, -saberBoxSize);
      VectorSet(saberTrMaxs, saberBoxSize, saberBoxSize, saberBoxSize);
   }
   else
   { //just trace the minimum blade radius
      saberBoxSize = (self->client->saber[rSaberNum].blade[rBladeNum].radius*0.4f);

      VectorSet(saberTrMins, -saberBoxSize, -saberBoxSize, -saberBoxSize);
      VectorSet(saberTrMaxs, saberBoxSize, saberBoxSize, saberBoxSize);
   }

   while (!saberTraceDone)
   {
      if (doInterpolate
         && !d_saberSPStyleDamage.integer)
      { //This didn't quite work out like I hoped. But it's better than nothing. Sort of.
         vec3_t oldSaberStart, oldSaberEnd, saberDif, oldSaberDif;
         int traceTests = 0;
         float trDif = 8;

         if ((level.time - self->client->saber[rSaberNum].blade[rBladeNum].trail.lastTime) > 100)
         {//no valid last pos, use current
            VectorCopy(saberStart, oldSaberStart);
            VectorCopy(saberEnd, oldSaberEnd);
         }
         else
         {//trace from last pos
            VectorCopy(self->client->saber[rSaberNum].blade[rBladeNum].trail.base, oldSaberStart);
            VectorCopy(self->client->saber[rSaberNum].blade[rBladeNum].trail.tip, oldSaberEnd);
         }

         VectorSubtract(saberStart, saberEnd, saberDif);
         VectorSubtract(oldSaberStart, oldSaberEnd, oldSaberDif);

         VectorNormalize(saberDif);
         VectorNormalize(oldSaberDif);

         saberEnd[0] = saberStart[0] - (saberDif[0] * trDif);
         saberEnd[1] = saberStart[1] - (saberDif[1] * trDif);
         saberEnd[2] = saberStart[2] - (saberDif[2] * trDif);

         oldSaberEnd[0] = oldSaberStart[0] - (oldSaberDif[0] * trDif);
         oldSaberEnd[1] = oldSaberStart[1] - (oldSaberDif[1] * trDif);
         oldSaberEnd[2] = oldSaberStart[2] - (oldSaberDif[2] * trDif);

         trap->Trace(tr, saberEnd, saberTrMins, saberTrMaxs, saberStart, self->s.number, trMask, qfalse, 0, 0);

         VectorCopy(saberEnd, lastValidStart);
         VectorCopy(saberStart, lastValidEnd);
         if (tr->entityNum < MAX_CLIENTS)
         {
            G_G2TraceCollide(tr, lastValidStart, lastValidEnd, saberTrMins, saberTrMaxs);
         }
         else if (tr->entityNum < ENTITYNUM_WORLD)
         {
            gentity_t *trHit = &g_entities[tr->entityNum];

            if (trHit->inuse && trHit->ghoul2)
            { //hit a non-client entity with a g2 instance
               G_G2TraceCollide(tr, lastValidStart, lastValidEnd, saberTrMins, saberTrMaxs);
            }
         }

         trDif++;

         while (tr->fraction == 1.0 && traceTests < 4 && tr->entityNum >= ENTITYNUM_NONE)
         {
            if ((level.time - self->client->saber[rSaberNum].blade[rBladeNum].trail.lastTime) > 100)
            {//no valid last pos, use current
               VectorCopy(saberStart, oldSaberStart);
               VectorCopy(saberEnd, oldSaberEnd);
            }
            else
            {//trace from last pos
               VectorCopy(self->client->saber[rSaberNum].blade[rBladeNum].trail.base, oldSaberStart);
               VectorCopy(self->client->saber[rSaberNum].blade[rBladeNum].trail.tip, oldSaberEnd);
            }

            VectorSubtract(saberStart, saberEnd, saberDif);
            VectorSubtract(oldSaberStart, oldSaberEnd, oldSaberDif);

            VectorNormalize(saberDif);
            VectorNormalize(oldSaberDif);

            saberEnd[0] = saberStart[0] - (saberDif[0] * trDif);
            saberEnd[1] = saberStart[1] - (saberDif[1] * trDif);
            saberEnd[2] = saberStart[2] - (saberDif[2] * trDif);

            oldSaberEnd[0] = oldSaberStart[0] - (oldSaberDif[0] * trDif);
            oldSaberEnd[1] = oldSaberStart[1] - (oldSaberDif[1] * trDif);
            oldSaberEnd[2] = oldSaberStart[2] - (oldSaberDif[2] * trDif);

            trap->Trace(tr, saberEnd, saberTrMins, saberTrMaxs, saberStart, self->s.number, trMask, qfalse, 0, 0);

            VectorCopy(saberEnd, lastValidStart);
            VectorCopy(saberStart, lastValidEnd);
            if (tr->entityNum < MAX_CLIENTS)
            {
               G_G2TraceCollide(tr, lastValidStart, lastValidEnd, saberTrMins, saberTrMaxs);
            }
            else if (tr->entityNum < ENTITYNUM_WORLD)
            {
               gentity_t *trHit = &g_entities[tr->entityNum];

               if (trHit->inuse && trHit->ghoul2)
               { //hit a non-client entity with a g2 instance
                  G_G2TraceCollide(tr, lastValidStart, lastValidEnd, saberTrMins, saberTrMaxs);
               }
            }

            traceTests++;
            trDif += 8;
         }
      }
      else
      {
         vec3_t saberEndExtrapolated;
         if (extrapolate)
         {//extrapolate 16
            vec3_t diff;
            VectorSubtract(saberEnd, saberStart, diff);
            VectorNormalize(diff);
            VectorMA(saberStart, SABER_EXTRAPOLATE_DIST, diff, saberEndExtrapolated);
         }
         else
         {
            VectorCopy(saberEnd, saberEndExtrapolated);
         }
         trap->Trace(tr, saberStart, saberTrMins, saberTrMaxs, saberEndExtrapolated, self->s.number, trMask, qfalse, 0, 0);

         VectorCopy(saberStart, lastValidStart);
         VectorCopy(saberEndExtrapolated, lastValidEnd);
         /*
         if ( tr.allsolid || tr.startsolid )
         {
         if ( tr.entityNum == ENTITYNUM_NONE )
         {
         qboolean whah = qtrue;
         }
         Com_Printf( "saber trace start/all solid - ent is %d\n", tr.entityNum );
         }
         */
         if (tr->entityNum < MAX_CLIENTS)
         {
            G_G2TraceCollide(tr, lastValidStart, lastValidEnd, saberTrMins, saberTrMaxs);
         }
         else if (tr->entityNum < ENTITYNUM_WORLD)
         {
            gentity_t *trHit = &g_entities[tr->entityNum];

            if (trHit->inuse && trHit->ghoul2)
            { //hit a non-client entity with a g2 instance
               G_G2TraceCollide(tr, lastValidStart, lastValidEnd, saberTrMins, saberTrMaxs);
            }
         }
      }

      saberTraceDone = qtrue;
   }
}

#define MATH_PI 3.14159265
float JKU_calculateSaberHitAngle(gentity_t* self,
   gentity_t* other)
{
   if (!self->client || !other->client)
   {
      return 180.0f;
   }

   float dotProduct =
      (self->client->ps.viewangles[0] * other->client->ps.viewangles[0]) +
      (self->client->ps.viewangles[1] * other->client->ps.viewangles[1]) +
      (self->client->ps.viewangles[2] * other->client->ps.viewangles[2]);

   float selfAngleLength = std::sqrt(std::pow(self->client->ps.viewangles[0], 2.0f) +
      std::pow(self->client->ps.viewangles[1], 2.0f) +
      std::pow(self->client->ps.viewangles[2], 2.0f));

   float otherAngleLength = std::sqrt(std::pow(other->client->ps.viewangles[0], 2.0f) +
      std::pow(other->client->ps.viewangles[1], 2.0f) +
      std::pow(other->client->ps.viewangles[2], 2.0f));

   return dotProduct / (selfAngleLength * otherAngleLength);

   //return std::acos(cosAngle) * 180.0 / MATH_PI;
}

float JKU_calculateAttackAngle(gentity_t* self,
   gentity_t* other)
{
   vec3_t crossProduct;
   crossProduct[0] = (self->client->ps.viewangles[1] * other->client->ps.viewangles[2]) - (self->client->ps.viewangles[2] * other->client->ps.viewangles[1]);
   crossProduct[1] = (self->client->ps.viewangles[2] * other->client->ps.viewangles[0]) - (self->client->ps.viewangles[0] * other->client->ps.viewangles[2]);
   crossProduct[2] = (self->client->ps.viewangles[0] * other->client->ps.viewangles[1]) - (self->client->ps.viewangles[1] * other->client->ps.viewangles[0]);

   float crossProductLength = std::sqrt(std::pow(crossProduct[0], 2.0f) +
      std::pow(crossProduct[1], 2.0f) +
      std::pow(crossProduct[2], 2.0f));

   float selfAngleLength = std::sqrt(std::pow(self->client->ps.viewangles[0], 2.0f) +
      std::pow(self->client->ps.viewangles[1], 2.0f) +
      std::pow(self->client->ps.viewangles[2], 2.0f));

   float otherAngleLength = std::sqrt(std::pow(other->client->ps.viewangles[0], 2.0f) +
      std::pow(other->client->ps.viewangles[1], 2.0f) +
      std::pow(other->client->ps.viewangles[2], 2.0f));

   float sinAngle = crossProductLength / (selfAngleLength * otherAngleLength);

   return std::asin(sinAngle) * 180.0f / MATH_PI;
}

float JKU_radToDeg(float radians)
{
   return std::acos(radians) * 180.0 / MATH_PI;
}

int JKU_calculateSaberDamage(gentity_t *self)
{
   //Fnuki: New specification of damage application:

   /*
   Change the HP damage of lightsaber styles to the following:
      --- Fast 15 Damage
      --- Medium 20 Damage
      --- Strong 35
      --- Duals 20
      --- Staff 25
   */

   int damage = 20;

   if (self && self->client)
   {
      switch (self->client->ps.fd.saberAnimLevel)
      {
      case SS_DUAL:
         damage = 20;
         break;
      case SS_STAFF:
         damage = 25;
         break;
      case SS_FAST:
         damage = 15;
         break;
      case SS_STRONG:
         damage = 35;
         break;
      case SS_MEDIUM:
         damage = 20;
         break;
      default:
         break;
      }
   }

   return damage;
}

#ifdef _WIN32
#ifdef __cplusplus
	}
#endif
#else
#ifdef __GNUG__
	}
#endif
#endif