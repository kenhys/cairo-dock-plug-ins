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

#ifndef __CD_APPLET_STRUCT__
#define  __CD_APPLET_STRUCT__

#include <cairo-dock.h>

//\___________ structure containing the applet's configuration parameters.
struct _AppletConfig {
	gboolean bShowKbdIndicator;
	gchar *cBackgroundImage;
	gdouble fTextRatio;
	GldiTextDescription textDescription;
	gint iTransitionDuration;
	gchar *cShortkey;
	gchar *cEmblemNumLock;
	gchar *cEmblemCapsLock;
	gint iNLetters;
	} ;

//\___________ structure containing the applet's data, like surfaces, dialogs, results of calculus, etc.
struct _AppletData {
	CairoDockImageBuffer bgImage;
	CairoDockImageBuffer *pCurrentImage;
	CairoDockImageBuffer *pOldImage;
	/**cairo_surface_t *pCurrentSurface;
	GLuint iCurrentTexture;
	gint iCurrentTextWidth, iCurrentTextHeight;
	cairo_surface_t *pOldSurface;
	GLuint iOldTexture;
	gint iOldTextWidth, iOldTextHeight;*/
	gint iCurrentGroup;
	guint iCurrentIndic, iPreviousIndic;
	GldiShortkey *pKeyBinding;
	gchar *cEmblemNumLock;
	gchar *cEmblemCapsLock;
	gpointer pEngine; // const, should not be freed
	gchar *cShortGroupName;  // current text displayed
	gchar *cGroupName;  // current label displayed
	} ;


#endif
