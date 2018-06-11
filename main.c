#include <stdio.h>
#include <glib/gi18n.h>
#include "gtask-example-window.h"

static void
on_shutdown(GtkApplication *app)
{
    g_application_quit(G_APPLICATION(app));
}

static void
on_activate(GtkApplication *app)
{
    GtkWindow *window;

    g_assert(GTK_IS_APPLICATION(app));

    window = gtk_application_get_active_window(app);
    if(window == NULL)
        window = g_object_new(GTASK_EXAMPLE_TYPE_WINDOW,
        "application", app,
        "default-width", 600,
        "default_height", 300,
        NULL);

    gtk_window_present(window);
}

int main(int argc, char *argv[])
{
    g_autoptr(GtkApplication) app = NULL;
    int ret;

    app = gtk_application_new("org.gnome.Gtask-Example", G_APPLICATION_FLAGS_NONE);

    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    g_signal_connect(app, "shutdown", G_CALLBACK(on_shutdown), NULL);

    ret = g_application_run(G_APPLICATION(app), argc, argv);

    return ret;
}