/******************************************************************************

This file is a part of the cairo-dock program,
released under the terms of the GNU General Public License.

Written by Fabrice Rey (for any bug report, please mail me to fabounet@users.berlios.de)

******************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <glib/gstdio.h>

#include "applet-struct.h"
#include "applet-load-icons.h"
#include "applet-read-data.h"
#include "applet-notifications.h"

CD_APPLET_INCLUDE_MY_VARS

extern AppletConfig myConfig;
extern AppletData myData;


CD_APPLET_ABOUT (_D("This is the weather applet\n made by Fabrice Rey for Cairo-Dock"))


CD_APPLET_ON_CLICK_BEGIN
	if (myDock != NULL && myIcon->pSubDock != NULL && pClickedContainer == CAIRO_DOCK_CONTAINER (myIcon->pSubDock))  // on a clique sur une icone du sous-dock.
	{
		cd_debug (" clic sur %s", pClickedIcon->acName);
		cd_weather_show_forecast_dialog (pClickedIcon);
	}
	else if (myDesklet != NULL && pClickedContainer == myContainer && pClickedIcon != NULL)  // on a clique sur une icone du desklet.
	{
		/*int iMouseX = - (int) myDesklet->diff_x;
		int iMouseY = - (int) myDesklet->diff_y;
		cd_debug (" clic en (%d;%d)", iMouseX, iMouseY);
		
		if (myIcon->fDrawX < iMouseX && myIcon->fDrawX + myIcon->fWidth > iMouseX && myIcon->fDrawY < iMouseY && myIcon->fDrawY + myIcon->fHeight > iMouseY)
		{
			cd_weather_show_current_conditions_dialog ();
		}
		else
		{
			GList* ic;
			Icon *icon;
			for (ic = myData.pDeskletIconList; ic != NULL; ic = ic->next)
			{
				icon = ic->data;
				if (icon->fDrawX < iMouseX && icon->fDrawX + icon->fWidth * icon->fScale > iMouseX && icon->fDrawY < iMouseY && icon->fDrawY + icon->fHeight * icon->fScale > iMouseY)
				{
					cd_weather_show_forecast_dialog (icon);
					break ;
				}
			}
		}*/
		if (pClickedIcon == myIcon)
			cd_weather_show_current_conditions_dialog ();
		else
			cd_weather_show_forecast_dialog (pClickedIcon);
	}
	else
		return CAIRO_DOCK_LET_PASS_NOTIFICATION;
CD_APPLET_ON_CLICK_END



static void _cd_weather_location_choosed (int iAnswer, GtkWidget *pWidget, gpointer data)
{
	if (iAnswer == GTK_RESPONSE_OK)
	{
		//\____________________ On recupere le code choisi.
		gchar *cChoosedText = gtk_combo_box_get_active_text (GTK_COMBO_BOX (pWidget));
		g_return_if_fail (cChoosedText != NULL);
		
		gchar *str = strrchr (cChoosedText, ':');
		g_return_if_fail (str != NULL);
		
		myConfig.cLocationCode = g_strdup (str+2);  // on saute le ':' et l'espace.
		g_free (cChoosedText);
		
		//\____________________ On l'ecrit dans le fichier de conf.
		cairo_dock_update_conf_file (myIcon->pModule->cConfFilePath,
			G_TYPE_STRING, "Configuration", "location code", myConfig.cLocationCode,
			G_TYPE_INVALID);
		
		//\____________________ On recharge l'applet.
		g_source_remove (myData.iSidTimer);
		myData.iSidTimer = 0;
		
		cd_weather_launch_measure ();  // asynchrone
	}
}
static void _cd_weather_search_for_location (GtkMenuItem *menu_item, gpointer *data)
{
	gchar *cLocation = cairo_dock_show_demand_and_wait (_("Enter your location\n (for exemple : Paris, France)"),
		myIcon,
		myContainer,
		NULL);
	if (cLocation != NULL)
	{
		gchar *cFilePath = cd_weather_get_location_data (cLocation);
		
		GError *erreur = NULL;
		GList *pLocationsList = cd_weather_parse_location_data (cFilePath, &erreur);
		if (erreur != NULL)
		{
			gchar *cIconPath = g_strdup_printf ("%s/broken.png", MY_APPLET_SHARE_DATA_DIR);
			cairo_dock_show_temporary_dialog_with_icon (_("I couldn't get the info\n Is connexion alive ?"),
				myIcon,
				myContainer,
				0,
				cIconPath);
			g_free (cIconPath);
			
			g_error_free (erreur);
			erreur = NULL;  // on ne garde pas trace de l'erreur, c'est deja fait au (re)chargement.
		}
		else if (pLocationsList == NULL)
		{
			gchar *cIconPath = g_strdup_printf ("%s/broken.png", MY_APPLET_SHARE_DATA_DIR);
			cairo_dock_show_temporary_dialog_with_icon (_("I couldn't get the info\n Is connexion alive ?"),
				myIcon,
				myContainer,
				0,
				cIconPath);
			g_free (cIconPath);
			
			g_error_free (erreur);
			erreur = NULL;
		}
		else
		{
			GtkWidget *pCombo = gtk_combo_box_new_text ();
			gchar *cLocationName, *cLocationCode;
			GString *sOneLocation = g_string_new ("");
			GList *list;
			for (list = pLocationsList; list != NULL; list = list->next)
			{
				cLocationCode = list->data;
				list = list->next;
				cLocationName = list->data;
				
				g_string_printf (sOneLocation, "%s : %s", cLocationName, cLocationCode);
				gtk_combo_box_append_text (GTK_COMBO_BOX (pCombo), sOneLocation->str);
			}
			g_string_free (sOneLocation, TRUE);
			
			gchar *cImageFilePath = g_strdup_printf ("%s/%s.png", myConfig.cThemePath, "32");
			if (! g_file_test (cImageFilePath, G_FILE_TEST_EXISTS))
			{
				g_free (cImageFilePath);
				cImageFilePath = g_strdup_printf ("%s/%s.svg", myConfig.cThemePath, "32");
			}
			CairoDockDialog *pDialog = cairo_dock_build_dialog (_("Choose your location :"),
				myIcon,
				myContainer,
				cImageFilePath,
				pCombo,
				GTK_BUTTONS_OK_CANCEL,
				(CairoDockActionOnAnswerFunc) _cd_weather_location_choosed,
				NULL,
				NULL);
			g_free (cImageFilePath);
		}
		
		
		g_remove (cFilePath);
		g_free (cFilePath);
	}
}
static void _cd_weather_reload (GtkMenuItem *menu_item, gpointer *data)
{
	g_source_remove (myData.iSidTimer);
	myData.iSidTimer = 0;
	
	cd_weather_launch_measure ();  // asynchrone
}
CD_APPLET_ON_BUILD_MENU_BEGIN
	CD_APPLET_ADD_SUB_MENU ("weather", pSubMenu, CD_APPLET_MY_MENU)
		CD_APPLET_ADD_IN_MENU (_("Search for your location"), _cd_weather_search_for_location, pSubMenu)
		CD_APPLET_ADD_IN_MENU (_("Reload now"), _cd_weather_reload, pSubMenu)
		CD_APPLET_ADD_ABOUT_IN_MENU (pSubMenu)
CD_APPLET_ON_BUILD_MENU_END


CD_APPLET_ON_MIDDLE_CLICK_BEGIN
	if (pClickedIcon == myIcon)
	{
		cd_weather_show_current_conditions_dialog ();
	}
	else
		return CAIRO_DOCK_LET_PASS_NOTIFICATION;
CD_APPLET_ON_MIDDLE_CLICK_END


CairoDockDialog *cd_weather_show_forecast_dialog (Icon *pIcon)
{
	if (myDock != NULL)
		g_list_foreach (myIcon->pSubDock->icons, (GFunc) cairo_dock_remove_dialog_if_any, NULL);
	else
		//g_list_foreach (myData.pDeskletIconList, (GFunc) cairo_dock_remove_dialog_if_any, NULL);
		cairo_dock_remove_dialog_if_any (myIcon);
	
	if (myData.bErrorRetrievingData)
	{
		cairo_dock_show_temporary_dialog_with_icon (_("No data were available\n is connection alive ?"), 
			(myDock ? pIcon : myIcon),
			(myDock ? CAIRO_DOCK_CONTAINER (myIcon->pSubDock) : myContainer),
			myConfig.cDialogDuration,
			pIcon->acFileName);
		return ;
	}
	
	int iNumDay = ((int) pIcon->fOrder) / 2, iPart = ((int) pIcon->fOrder) - 2 * iNumDay;
	g_return_val_if_fail (iNumDay < myConfig.iNbDays && iPart < 2, NULL);
	
	Day *day = &myData.days[iNumDay];
	DayPart *part = &day->part[iPart];
	cairo_dock_show_temporary_dialog_with_icon ("%s (%s) : %s\n %s : %s%s -> %s%s\n %s : %s%s (%s)\n %s : %s\n %s : %s  %s %s",
		(myDock ? pIcon : myIcon), (myDock ? CAIRO_DOCK_CONTAINER (myIcon->pSubDock) : myContainer), myConfig.cDialogDuration, pIcon->acFileName,
		day->cName, day->cDate, part->cWeatherDescription,
		_D("Temperature"), _display (day->cTempMin), myData.units.cTemp, _display (day->cTempMax), myData.units.cTemp,
		_D("Wind"), _display (part->cWindSpeed), myData.units.cSpeed, _display (part->cWindDirection),
		_D("Humidity"), _display (part->cHumidity),  // unite ?...
		_D("SunRise"), _display (day->cSunRise), _("SunSet"), _display (day->cSunSet));
}

CairoDockDialog *cd_weather_show_current_conditions_dialog (void)
{
	cairo_dock_remove_dialog_if_any (myIcon);
	
	if (myData.bErrorRetrievingData)
	{
		cairo_dock_show_temporary_dialog_with_icon (_("No data were available\n is connection alive ?"), 
			myIcon,
			myContainer,
			myConfig.cDialogDuration,
			myIcon->acFileName);
		return ;
	}
	
	CurrentContitions *cc = &myData.currentConditions;
	cairo_dock_show_temporary_dialog_with_icon ("%s (%s, %s)\n %s : %s%s (%s : %s%s)\n %s : %s%s (%s)\n %s : %s - %s : %s%s\n %s : %s  %s %s",
		myIcon, myContainer, myConfig.cDialogDuration, myIcon->acFileName,
		cc->cWeatherDescription, cc->cDataAcquisitionDate, cc->cObservatory,
		_D("Temperature"), _display (cc->cTemp), myData.units.cTemp, _D("feeled"), _display (cc->cFeeledTemp), myData.units.cTemp,
		_D("Wind"), _display (cc->cWindSpeed), myData.units.cSpeed, _display (cc->cWindDirection),
		_D("Humidity"), _display (cc->cHumidity), _D("Pressure"), _display (cc->cPressure), myData.units.cPressure,  // unite ?...
		_D("SunRise"), _display (cc->cSunRise), _D("SunSet"), _display (cc->cSunSet));
}
