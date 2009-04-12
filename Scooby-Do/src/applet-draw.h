
#ifndef __APPLET_DRAW_
#define  __APPLET_DRAW_


#include <cairo-dock.h>
#include "applet-struct.h"


void cd_do_render_cairo (CairoDock *pMainDock, cairo_t *pCairoContext);


void cd_do_render_opengl (CairoDock *pMainDock);


void cd_do_load_pending_caracters (void);


void cd_do_free_char (CDChar *pChar);
void cd_do_free_char_list (GList *pCharList);

void cd_do_launch_appearance_animation (void);


#endif