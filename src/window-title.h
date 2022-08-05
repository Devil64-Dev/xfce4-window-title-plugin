/*  $Id$
 *
 *  Copyright (C) 2022 Devil64-Dev <devil64dev@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __WINDOW_TITLE_PLUGIN_H__
#define __WINDOW_TITLE_PLUGIN_H__

#include <gtk/gtk.h>
#include <i3ipc-glib/i3ipc-glib.h>
#include <libxfce4panel/libxfce4panel.h>

G_BEGIN_DECLS

/* plugin structure */
typedef struct
{
  XfcePanelPlugin *plugin;

  /* panel widgets */
  GtkWidget *ebox;
  GtkWidget *hvbox;
  GtkWidget *title;

  i3ipcConnection *connection;
} WindowTitlePlugin;

G_END_DECLS

#endif /* !__WINDOW_TITLE_PLUGIN_H__ */
