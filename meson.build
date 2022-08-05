project('xfce4-window-title-plugin', 'c', version : '1.0.0')

i18n = import('i18n')

add_project_arguments('-DGETTEXT_PACKAGE="@0@"'.format(meson.project_name()), language : 'c')
add_project_arguments('-DPACKAGE_NAME="@0@"'.format(meson.project_name()), language : 'c')
add_project_arguments('-DLOCALEDIR="@0@"'.format(join_paths(get_option('prefix'), get_option('localedir'))), language : 'c')

plugin_deps = [
    dependency('gtk+-3.0', version : '>= 3.20.0'),
    dependency('libxfce4panel-2.0', version : '>= 4.14.0'),
    dependency('i3ipc-glib-1.0', version: '>= 0.5'),
    dependency('libxfce4util-1.0')
]

shared_library(
    'windowtitle',
    'src/window-title.c',
    dependencies : plugin_deps,
    install_dir : join_paths(get_option('libdir'), 'xfce4/panel/plugins'),
    install : true
)

i18n.merge_file(
    input : 'window-title.desktop.in',
    output: 'window-title.desktop',
    type : 'desktop',
    po_dir : 'po',
    install_dir : join_paths(get_option('datadir'), 'xfce4/panel/plugins'),
    install: true
)

subdir('po')
