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

#include "draw_utils.h"

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

void JKU_DrawAmmoAndClipReserve(centity_t	*cent, menuDef_t *menuHUD)
{
	playerState_t	*ps;
	itemDef_t		*focusItem;
	int				ammoValue = 0;
	int				clipValue = 100; // JKU-Bunisher: Need to re-do this. Hardcoded for now.

	ps = &cg.snap->ps;

	if (!menuHUD) {
		return;
	}

	if (!cent->currentState.weapon) {
		return;
	}

	if (ps->ammo[weaponData[cent->currentState.weapon].ammoIndex] < 0) {
		return;
	}

	if (cg.oldammo < ps->ammo[weaponData[cent->currentState.weapon].ammoIndex]) {
		cg.oldAmmoTime = cg.time + 200;
	}

	ammoValue = ps->ammo[weaponData[cent->currentState.weapon].ammoIndex];
	cg.oldammo = ammoValue;

	focusItem = Menu_FindItemByName(menuHUD, "ammoamountandclipreserve");

	if (weaponData[cent->currentState.weapon].energyPerShot == 0 &&
		weaponData[cent->currentState.weapon].altEnergyPerShot == 0) {

		focusItem = Menu_FindItemByName(menuHUD, "ammoamountandclipreserveinfinite");
		if (focusItem) {
			CG_DrawScaledProportionalString(focusItem->window.rect.x, focusItem->window.rect.y, "~ | ~", UI_CENTER, focusItem->window.foreColor, 0.5f);
		}
	}
	else
	{
		focusItem = Menu_FindItemByName(menuHUD, "ammoamountandclipreserve");
		if (focusItem) {
			ammoValue = ps->ammo[weaponData[cent->currentState.weapon].ammoIndex];
			CG_DrawScaledProportionalString(focusItem->window.rect.x, focusItem->window.rect.y, va("%d | %d", ammoValue, clipValue), UI_CENTER, focusItem->window.foreColor, 0.5f);
		}
	}
}

void JKU_DrawForceCircle(centity_t *cent, menuDef_t *menuHUD)
{
	itemDef_t		*focusItem;
	float			value;

	// Can we find the menu?
	if (!menuHUD)
	{
		return;
	}

	// don't display if dead
	if (cg.snap->ps.stats[STAT_HEALTH] <= 0)
	{
		return;
	}

	value = cg.snap->ps.fd.forcePower;

	if (value >= 0)
	{
		focusItem = Menu_FindItemByName(menuHUD, "forcecircle_tick1");

		if (focusItem)
		{
			trap->R_SetColor(colorTable[CT_WHITE]);
			CG_DrawPic(
				focusItem->window.rect.x,
				focusItem->window.rect.y,
				focusItem->window.rect.w,
				focusItem->window.rect.h,
				focusItem->window.background
			);
		}
	}
	if (value >= 12.5)
	{
		focusItem = Menu_FindItemByName(menuHUD, "forcecircle_tick2");

		if (focusItem)
		{
			trap->R_SetColor(colorTable[CT_WHITE]);
			CG_DrawPic(
				focusItem->window.rect.x,
				focusItem->window.rect.y,
				focusItem->window.rect.w,
				focusItem->window.rect.h,
				focusItem->window.background
			);
		}
	}
	if (value >= 25)
	{
		focusItem = Menu_FindItemByName(menuHUD, "forcecircle_tick3");

		if (focusItem)
		{
			trap->R_SetColor(colorTable[CT_WHITE]);
			CG_DrawPic(
				focusItem->window.rect.x,
				focusItem->window.rect.y,
				focusItem->window.rect.w,
				focusItem->window.rect.h,
				focusItem->window.background
			);
		}
	}
	if (value >= 37.5)
	{
		focusItem = Menu_FindItemByName(menuHUD, "forcecircle_tick4");

		if (focusItem)
		{
			trap->R_SetColor(colorTable[CT_WHITE]);
			CG_DrawPic(
				focusItem->window.rect.x,
				focusItem->window.rect.y,
				focusItem->window.rect.w,
				focusItem->window.rect.h,
				focusItem->window.background
			);
		}
	}
	if (value >= 50)
	{
		focusItem = Menu_FindItemByName(menuHUD, "forcecircle_tick5");

		if (focusItem)
		{
			trap->R_SetColor(colorTable[CT_WHITE]);
			CG_DrawPic(
				focusItem->window.rect.x,
				focusItem->window.rect.y,
				focusItem->window.rect.w,
				focusItem->window.rect.h,
				focusItem->window.background
			);
		}
	}
	if (value >= 62.5)
	{
		focusItem = Menu_FindItemByName(menuHUD, "forcecircle_tick6");

		if (focusItem)
		{
			trap->R_SetColor(colorTable[CT_WHITE]);
			CG_DrawPic(
				focusItem->window.rect.x,
				focusItem->window.rect.y,
				focusItem->window.rect.w,
				focusItem->window.rect.h,
				focusItem->window.background
			);
		}
	}
	if (value >= 75)
	{
		focusItem = Menu_FindItemByName(menuHUD, "forcecircle_tick7");

		if (focusItem)
		{
			trap->R_SetColor(colorTable[CT_WHITE]);
			CG_DrawPic(
				focusItem->window.rect.x,
				focusItem->window.rect.y,
				focusItem->window.rect.w,
				focusItem->window.rect.h,
				focusItem->window.background
			);
		}
	}
	if (value >= 87.5)
	{
		focusItem = Menu_FindItemByName(menuHUD, "forcecircle_tick8");

		if (focusItem)
		{
			trap->R_SetColor(colorTable[CT_WHITE]);
			CG_DrawPic(
				focusItem->window.rect.x,
				focusItem->window.rect.y,
				focusItem->window.rect.w,
				focusItem->window.rect.h,
				focusItem->window.background
			);
		}
	}
}

void JKU_DrawForcePower(centity_t *cent, menuDef_t *menuHUD)
{
	float x = 287.5;
	float y = 400;
	float w = 64;
	float h = 64;

	int	i;
	int	count = 0;

	if (cg.snap->ps.stats[STAT_HEALTH] <= 0 ||
		!cg.snap->ps.fd.forcePowersKnown) {
		return;
	}

	for (i = 0; i < NUM_FORCE_POWERS; ++i) {
		if (ForcePower_Valid(i)) {
			count++;
		}
	}

	if (count == 0) {
		return;
	}

	i = BG_ProperForceIndex(cg.forceSelect) - 1;
	if (i < 0) {
		i = NUM_FORCE_POWERS - 1;
	}

	if (ForcePower_Valid(cg.forceSelect)) {
		if (cgs.media.forcePowerIcons[cg.forceSelect]) {
			CG_DrawPic(x, y, w, h, cgs.media.forcePowerIcons[cg.forceSelect]);
		}
	}

	i = BG_ProperForceIndex(cg.forceSelect) + 1;
	if (i >= NUM_FORCE_POWERS) {
		i = 0;
	}
}

void JKU_DrawWeaponry(void)
{
	float			iconX = 529, iconY = 370;
	float			iconHeight = 32, iconWidth = 128;
	float			iconY_adjust;

	int				iconMax = 1;
	int				iconDownCnt, iconCnt, iconUpCnt, holdCnt;
	int				i, bits, count = 0;

	qboolean		drewConc = qfalse;

	if (cg.predictedPlayerState.emplacedIndex) {
		cg.weaponSelectTime = 0;
	}

	if (cg.predictedPlayerState.stats[STAT_HEALTH] <= 0) {
		return;
	}

	cg.itemPickupTime = 0;
	bits = cg.predictedPlayerState.stats[STAT_WEAPONS];

	if (!CG_WeaponSelectable(cg.weaponSelect) &&
		(cg.weaponSelect == WP_THERMAL || cg.weaponSelect == WP_TRIP_MINE)) {
		count++;
	}

	for (i = 1; i < WP_NUM_WEAPONS; i++) {
		if (bits & (1 << i)) {
			if (CG_WeaponSelectable(i) ||
				(i != WP_THERMAL && i != WP_TRIP_MINE)) {
				count++;
			}
		}
	}

	if (count == 0) {
		return;
	}


	holdCnt = count - 1;

	if (holdCnt == 0) {
		iconUpCnt = 0;
		iconDownCnt = 0;
	}

	else if (count > (2 * iconMax)) {
		iconUpCnt = iconMax;
		iconDownCnt = iconMax;
	}

	else {
		iconUpCnt = holdCnt / 2;
		iconDownCnt = holdCnt - iconUpCnt;
	}

	if (cg.weaponSelect == WP_CONCUSSION) {
		i = WP_FLECHETTE;
	}

	else {
		i = cg.weaponSelect - 1;
	}

	if (i<1) {
		i = LAST_USEABLE_WEAPON;
	}

	// Up
	iconY_adjust = iconY - 30;
	drewConc = qfalse;

	for (iconCnt = 1; iconCnt<(iconUpCnt + 1); i--) {
		if (i == WP_CONCUSSION) {
			i--;
		}

		else if (i == WP_FLECHETTE && !drewConc && cg.weaponSelect != WP_CONCUSSION) {
			i = WP_CONCUSSION;
		}

		if (i<1) {
			i = LAST_USEABLE_WEAPON;
		}

		if (!(bits & (1 << i))) {
			if (i == WP_CONCUSSION) {
				drewConc = qtrue;
				i = WP_ROCKET_LAUNCHER;
			}
			continue;
		}

		if (!CG_WeaponSelectable(i) &&
			(i == WP_THERMAL || i == WP_TRIP_MINE)) {
			continue;
		}

		++iconCnt;

		if (cgs.media.weaponIcons[i]) {
			CG_RegisterWeapon(i);
			CG_DrawPic(iconX, iconY_adjust, iconWidth, iconHeight, cgs.media.weaponIcons_NA[i]);
			iconY_adjust -= 30;
		}

		if (i == WP_CONCUSSION) {
			drewConc = qtrue;
			i = WP_ROCKET_LAUNCHER;
		}
	}

	// Center
	if (cgs.media.weaponIcons[cg.weaponSelect])
	{
		CG_RegisterWeapon(cg.weaponSelect);
		CG_DrawPic(iconX, iconY, iconWidth, iconHeight, cgs.media.weaponIcons[cg.weaponSelect]);
	}

	if (cg.weaponSelect == WP_CONCUSSION) {
		i = WP_ROCKET_LAUNCHER;
	}

	else {
		i = cg.weaponSelect + 1;
	}

	if (i> LAST_USEABLE_WEAPON) {
		i = 1;
	}

	// Down
	iconY_adjust = iconY + 30;
	for (iconCnt = 1; iconCnt<(iconDownCnt + 1); i++) {
		if (i == WP_CONCUSSION) {
			i++;
		}

		else if (i == WP_ROCKET_LAUNCHER && !drewConc && cg.weaponSelect != WP_CONCUSSION) {
			i = WP_CONCUSSION;
		}

		if (i>LAST_USEABLE_WEAPON) {
			i = 1;
		}

		if (!(bits & (1 << i))) {
			if (i == WP_CONCUSSION) {
				drewConc = qtrue;
				i = WP_FLECHETTE;
			}
			continue;
		}

		if (!CG_WeaponSelectable(i) &&
			(i == WP_THERMAL || i == WP_TRIP_MINE)) {
			continue;
		}

		++iconCnt;

		if (cgs.media.weaponIcons[i]) {
			CG_RegisterWeapon(i);
			CG_DrawPic(iconX, iconY_adjust, iconWidth, iconHeight, cgs.media.weaponIcons_NA[i]);
			iconY_adjust += 30;
		}

		if (i == WP_CONCUSSION) {
			drewConc = qtrue;
			i = WP_FLECHETTE;
		}
	}
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