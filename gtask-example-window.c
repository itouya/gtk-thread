#include <gtk/gtk.h>
#include "gtask-example-window.h"

struct _GtaskExampleWindow
{
    GtkWindow       parent_instance;
    GtkHeaderBar    *header_bar;
    GtkLabel        *label;
    GtkDrawingArea  *canvas;
    GtkButton       *button;
    GdkPoint        point[5];
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

gboolean
draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    guint w, h;
    GdkRGBA color;
    GtkStyleContext *context;
    GtaskExampleWindow *self = (GtaskExampleWindow *)data;
    GRand *rand;
    guint32 num;
    int i;

    context = gtk_widget_get_style_context(widget);
    rand = g_rand_new();
    num = g_rand_int(rand);

    w = gtk_widget_get_allocated_width(widget);
    h = gtk_widget_get_allocated_height(widget);

    gtk_render_background(context, cr, 0, 0, w, h);

    gtk_style_context_get_color(context, gtk_style_context_get_state(context), &color);
    for(i = 0; i < 6; i++)
    {
        if(i == num % 6)
        {
            color.red = 1.0;
        }
        else
        {
            color.green = 1.0;
        }
        gdk_cairo_set_source_rgba(cr, &color);
        cairo_arc(cr, self->point[i].x, self->point[i].y, 20.0, 0, 2 * G_PI);
    }
    cairo_fill(cr);
    g_rand_free(rand);

    return FALSE;
}

static void
gtask_example_window_class_init(GtaskExampleWindowClass *klass)
{
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);

    gtk_widget_class_set_template_from_resource(widget_class, "/org/gnome/Gtask-Example/gtask-example-window.ui");
    gtk_widget_class_bind_template_child(widget_class, GtaskExampleWindow, label);
    gtk_widget_class_bind_template_child(widget_class, GtaskExampleWindow, canvas);
    gtk_widget_class_bind_template_child(widget_class, GtaskExampleWindow, button);
}

static void
gtask_example_window_init(GtaskExampleWindow *self)
{
    self->point[0].x = 40.0;
    self->point[0].y = 40.0;
    self->point[1].x = 140.0;
    self->point[1].y = 40.0;
    self->point[2].x = 240.0;
    self->point[2].y = 40.0;
    self->point[3].x = 340.0;
    self->point[3].y = 40.0;
    self->point[4].x = 440.0;
    self->point[4].y = 40.0;
    self->point[5].x = 540.0;
    self->point[5].y = 40.0;
    gtk_widget_init_template(GTK_WIDGET(self));
    g_signal_connect(self->button, "clicked", G_CALLBACK(on_clicked), self);
    g_signal_connect(self->canvas, "draw", G_CALLBACK(draw_cb), self);
}