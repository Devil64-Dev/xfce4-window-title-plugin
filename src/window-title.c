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

#include "window-title.h"
#include <gtk/gtk.h>
#include <i3ipc-glib/i3ipc-glib.h>
#include <libxfce4panel/libxfce4panel.h>
#include <libxfce4util/libxfce4util.h>

static void plugin_construct(XfcePanelPlugin *plugin);

// Register the plugin
XFCE_PANEL_PLUGIN_REGISTER(plugin_construct);

static const gchar *get_title(i3ipcConnection *connection) {
  i3ipcCon *root;
  i3ipcCon *window;

  root = i3ipc_connection_get_tree(connection, NULL);
  window = i3ipc_con_find_focused(root);

  return i3ipc_con_get_name(window);
}

static gboolean show_title(WindowTitlePlugin *wtp) {
  const gchar *title;

  title = get_title(wtp->connection);
  gtk_label_set_ellipsize(GTK_LABEL(wtp->title), PANGO_ELLIPSIZE_END);
  gtk_label_set_text(GTK_LABEL(wtp->title), title);

  return TRUE;
}

static void on_title_changed(i3ipcConnection *connection, i3ipcGenericEvent *event, gpointer user) {
  WindowTitlePlugin *wtp;
  
  wtp = (WindowTitlePlugin*) user;
  show_title(wtp);
  
}

static void init_connection(WindowTitlePlugin *wtp) {
  i3ipcCommandReply *reply;

  wtp->connection = i3ipc_connection_new(NULL, NULL);
  reply = i3ipc_connection_subscribe(wtp->connection, I3IPC_EVENT_WINDOW, NULL);

  if(reply->success)
    g_signal_connect_after(wtp->connection, "window", G_CALLBACK(on_title_changed), wtp);

  i3ipc_command_reply_free(reply);
}


static void on_reconnect(GtkMenuItem *item, WindowTitlePlugin *wtp) {
  g_object_unref(wtp->connection);
  init_connection(wtp);
}

static void plugin_free(XfcePanelPlugin *plugin, WindowTitlePlugin *wtp) {
  GtkWidget *dialog;

  /* check if the dialog is still open. if so, destroy it */
  dialog = g_object_get_data (G_OBJECT (plugin), "dialog");
  if (G_UNLIKELY (dialog != NULL))
    gtk_widget_destroy (dialog);

  /* destroy the panel widgets */
  gtk_widget_destroy (wtp->hvbox);

  /* free the plugin structure */
  g_slice_free(WindowTitlePlugin, wtp);
}

static void plugin_construct(XfcePanelPlugin *plugin) {
  WindowTitlePlugin *wtp;
  GtkWidget *title;
  GtkWidget *reconnect_button;

  xfce_textdomain("xfce4-window-title-plugin", "/usr/share/locale", "UTF-8");

  wtp = g_slice_new0(WindowTitlePlugin);
  title = gtk_label_new("");
  reconnect_button = gtk_menu_item_new_with_label("Reconnect");

  wtp->title = title;
  gtk_label_set_xalign(GTK_LABEL(wtp->title), 0.);

  init_connection(wtp);

  xfce_panel_plugin_menu_insert_item(plugin, GTK_MENU_ITEM(reconnect_button));
  gtk_widget_show(reconnect_button);

  gtk_container_add(GTK_CONTAINER(plugin), title);
  gtk_widget_show_all(title);

  xfce_panel_plugin_set_expand(XFCE_PANEL_PLUGIN(plugin), TRUE);

  g_signal_connect(G_OBJECT(reconnect_button), "activate", G_CALLBACK(on_reconnect), wtp);
  g_signal_connect(G_OBJECT(plugin), "free-data", G_CALLBACK(plugin_free), plugin);
}
