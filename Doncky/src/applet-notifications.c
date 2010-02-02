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

//\________________ Add your name in the copyright file (and / or modify your name here)

#include <stdlib.h>
#include <string.h>
#include "applet-draw.h"
#include "applet-struct.h"
#include "applet-notifications.h"
#include "applet-xml.h"



//\___________ Define here the action to be taken when the user left-clicks on your icon or on its subdock or your desklet. The icon and the container that were clicked are available through the macros CD_APPLET_CLICKED_ICON and CD_APPLET_CLICKED_CONTAINER. CD_APPLET_CLICKED_ICON may be NULL if the user clicked in the container but out of icons.
CD_APPLET_ON_CLICK_BEGIN
	
CD_APPLET_ON_CLICK_END


//\___________ Define here the entries you want to add to the menu when the user right-clicks on your icon or on its subdock or your desklet. The icon and the container that were clicked are available through the macros CD_APPLET_CLICKED_ICON and CD_APPLET_CLICKED_CONTAINER. CD_APPLET_CLICKED_ICON may be NULL if the user clicked in the container but out of icons. The menu where you can add your entries is available throught the macro CD_APPLET_MY_MENU; you can add sub-menu to it if you want.
CD_APPLET_ON_BUILD_MENU_BEGIN
	GtkWidget *pSubMenu = CD_APPLET_CREATE_MY_SUB_MENU ();
		CD_APPLET_ADD_ABOUT_IN_MENU (pSubMenu);
CD_APPLET_ON_BUILD_MENU_END


CD_APPLET_ON_SCROLL_BEGIN

CD_APPLET_ON_SCROLL_END


CD_APPLET_ON_MIDDLE_CLICK_BEGIN

	//~ // On recupere les donnees de la CG.
		//~ if (myData.cGPUName == NULL)  // nvidia-config n'a encore jamais ete appele.
			//~ cd_sysmonitor_get_nvidia_info (myApplet);
		//~ if (myData.cGPUName && strcmp (myData.cGPUName, "none") != 0)  // nvidia-config est passe.
		//~ {
			//~ if (!myConfig.bShowNvidia)
				//~ cd_sysmonitor_get_nvidia_data (myApplet);  // le thread ne passe pas par la => pas de conflit.
			//~ cGCInfos = g_strdup_printf ("\n%s : %s\n %s : %d%s \n %s : %s\n %s : %d°C", D_("GPU model"), myData.cGPUName, D_("Video Ram"), myData.iVideoRam, D_("Mb"), D_("Driver Version"), myData.cDriverVersion, D_("Core Temperature"), myData.iGPUTemp);
		//~ }



	cd_doncky_free_item_list (myApplet);
	cd_doncky_readxml (myApplet);
CD_APPLET_ON_MIDDLE_CLICK_END