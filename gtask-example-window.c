#include <gtk/gtk.h>
#include "gtask-example-window.h"

struct _GtaskExampleWindow
{
    GtkWindow       parent_instance;
    GtkHeaderBar    *header_bar;
    GtkLabel        *label;
    GtkButton       *button;
};

G_DEFINE_TYPE (GtaskExampleWindow, gtask_example_window, GTK_TYPE_APPLICATION_WINDOW)

gboolean display(gpointer data)
{
    GtaskExampleWindow *self = (GtaskExampleWindow *)data;
    int i;
    
    gtk_label_set_text(self->label, "Start....");
    for(i = 0; i < 1000; i++)
    {
        printf("hurrah!\n");
        while(gtk_events_pending()) gtk_main_iteration();
    }
    gtk_label_set_text(self->label, "End....");
    return FALSE;
}

void
on_clicked(GtkButton *button, gpointer data)
{
    g_idle_add(display, data);
}

static void
gtask_example_window_class_init(GtaskExampleWindowClass *klass)
{
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);

    gtk_widget_class_set_template_from_resource(widget_class, "/org/gnome/Gtask-Example/gtask-example-window.ui");
    gtk_widget_class_bind_template_child(widget_class, GtaskExampleWindow, label);
    gtk_widget_class_bind_template_child(widget_class, GtaskExampleWindow, button);
}

static void
gtask_example_window_init(GtaskExampleWindow *self)
{
    gtk_widget_init_template(GTK_WIDGET(self));
    g_signal_connect(self->button, "clicked", G_CALLBACK(on_clicked), self);
}