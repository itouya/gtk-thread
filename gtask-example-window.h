#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GTASK_EXAMPLE_TYPE_WINDOW (gtask_example_window_get_type())
G_DECLARE_FINAL_TYPE (GtaskExampleWindow, gtask_example_window, GTASK_EXAMPLE, WINDOW, GtkApplicationWindow)

G_END_DECLS
