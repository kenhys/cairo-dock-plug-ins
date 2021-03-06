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
#include <cairo-dock.h>

#include "applet-struct.h"
#include "applet-slider.h"
#include "applet-config.h"


//\_________________ Here you have to get all your parameters from the conf file. Use the macros CD_CONFIG_GET_BOOLEAN, CD_CONFIG_GET_INTEGER, CD_CONFIG_GET_STRING, etc. myConfig has been reseted to 0 at this point. This function is called at the beginning of init and reload.
CD_APPLET_GET_CONFIG_BEGIN
	myConfig.cDirectory 		= CD_CONFIG_GET_STRING("Configuration", "directory");
	myConfig.iSlideTime 		= CD_CONFIG_GET_INTEGER ("Configuration", "slide time");
	myConfig.bSubDirs 		= CD_CONFIG_GET_BOOLEAN_WITH_DEFAULT ("Configuration", "sub directories", TRUE);
	myConfig.bRandom 			= CD_CONFIG_GET_BOOLEAN ("Configuration", "random");
	myConfig.bGetExifDataAtOnce 	= CD_CONFIG_GET_BOOLEAN ("Configuration", "get exif");
	myConfig.bImageName		= CD_CONFIG_GET_BOOLEAN ("Configuration", "image name");
	
	myConfig.bNoStretch 		= CD_CONFIG_GET_BOOLEAN ("Configuration", "no stretch");
	myConfig.bFillIcon 		= CD_CONFIG_GET_BOOLEAN ("Configuration", "fill icon");
	myConfig.iAnimation 		= CD_CONFIG_GET_INTEGER ("Configuration", "change animation");
	myConfig.iNbAnimationStep 	= CD_CONFIG_GET_INTEGER_WITH_DEFAULT ("Configuration", "nb step", 20);
	myConfig.iClickOption 		= CD_CONFIG_GET_INTEGER ("Configuration", "click");
	myConfig.iMiddleClickOption 	= CD_CONFIG_GET_INTEGER_WITH_DEFAULT ("Configuration", "middle click", SLIDER_OPEN_FOLDER);
	
	myConfig.bUseThread 		= CD_CONFIG_GET_BOOLEAN_WITH_DEFAULT ("Configuration", "use_thread", TRUE);
	myConfig.iBackgroundType 	= CD_CONFIG_GET_INTEGER_WITH_DEFAULT ("Configuration", "bg type", 2);
	double white[4] = {1,1,1,1};
	if (myConfig.iBackgroundType != 0)
		CD_CONFIG_GET_COLOR_RGBA_WITH_DEFAULT ("Configuration", "background_color", myConfig.pBackgroundColor, white);
	myConfig.iFrameWidth 	= CD_CONFIG_GET_INTEGER_WITH_DEFAULT ("Configuration", "bg width", 8);
CD_APPLET_GET_CONFIG_END


//\_________________ Here you have to free all ressources allocated for myConfig. This one will be reseted to 0 at the end of this function. This function is called right before yo get the applet's config, and when your applet is stopped.
CD_APPLET_RESET_CONFIG_BEGIN
	g_free (myConfig.cDirectory);
CD_APPLET_RESET_CONFIG_END


//\_________________ Here you have to free all ressources allocated for myData. This one will be reseted to 0 at the end of this function. This function is called when your applet is stopped.
CD_APPLET_RESET_DATA_BEGIN
	g_free (myData.cDirectory);
CD_APPLET_RESET_DATA_END
