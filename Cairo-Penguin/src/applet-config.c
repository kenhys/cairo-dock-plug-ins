/**
* This file is a part of the Cairo-Dock project
*
* Copyright : (C) see the 'copyright' file.
* E-mail    : see the 'copyright' file.
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 3
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <string.h>

#include "applet-struct.h"
#include "applet-config.h"


CD_APPLET_GET_CONFIG_BEGIN
	//\_________________ On recupere toutes les valeurs de notre fichier de conf.
	myConfig.cThemePath = CD_CONFIG_GET_THEME_PATH ("Configuration", "theme", "themes", "Classic");
	
	myConfig.iDelayBetweenChanges = MAX (2, CD_CONFIG_GET_INTEGER ("Configuration", "change delay"));
	
	myConfig.fAlpha = CD_CONFIG_GET_DOUBLE ("Configuration", "alpha");
	
	myConfig.bFree = CD_CONFIG_GET_BOOLEAN ("Configuration", "free");
	
	myConfig.iGroundOffset = CD_CONFIG_GET_INTEGER ("Configuration", "ground");
CD_APPLET_GET_CONFIG_END


CD_APPLET_RESET_CONFIG_BEGIN
	g_free (myConfig.cThemePath);
CD_APPLET_RESET_CONFIG_END


static void _penguin_reset_one_animation (PenguinAnimation *pAnimation)
{
	if (pAnimation->pSurfaces != NULL)
	{
		int i, j;
		for (i = 0; i < pAnimation->iNbDirections; i ++)
		{
			for (j = 0; j < pAnimation->iNbFrames; j ++)
			{
				cairo_surface_destroy (pAnimation->pSurfaces[i][j]);
			}
			g_free (pAnimation->pSurfaces[i]);
			pAnimation->pSurfaces[i] = NULL;
		}
		g_free (pAnimation->pSurfaces);
		pAnimation->pSurfaces = NULL;
	}
	if (pAnimation->iTexture != 0)
	{
		_cairo_dock_delete_texture (pAnimation->iTexture);
		pAnimation->iTexture = 0;
	}
}

void cd_penguin_reset_data (GldiModuleInstance *myApplet)
{
	int i;
	for (i = 0; i < myData.iNbAnimations; i++)
	{
		_penguin_reset_one_animation (&myData.pAnimations[i]);
	}
	
	g_free (myData.pAnimations);
	myData.pAnimations = NULL;
	g_free (myData.pBeginningAnimations);
	myData.pBeginningAnimations = NULL;
	g_free (myData.pEndingAnimations);
	myData.pEndingAnimations = NULL;
	g_free (myData.pGoUpAnimations);
	myData.pGoUpAnimations = NULL;
	g_free (myData.pMovmentAnimations);
	myData.pMovmentAnimations = NULL;
	g_free (myData.pRestAnimations);
	myData.pRestAnimations = NULL;
}

CD_APPLET_RESET_DATA_BEGIN
	cd_penguin_reset_data (myApplet);
CD_APPLET_RESET_DATA_END
