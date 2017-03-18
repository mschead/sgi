#include <gtk/gtk.h>
#include <iostream>
#include <vector>

static cairo_surface_t *surface = NULL;
GtkWidget *drawing_area;
GtkWidget *window_widget;

GtkBuilder *gtkBuilder;
GtkWidget *add_dialog;

/*Clear the surface, removing the scribbles*/
static void clear_surface (){
  cairo_t *cr;

  cr = cairo_create (surface);

  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_paint (cr);

  cairo_destroy (cr);
}

/*Creates the surface*/
static gboolean configure_event_cb (GtkWidget *widget, GdkEventConfigure *event, gpointer data){
  if (surface)
    cairo_surface_destroy (surface);

  surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
                                       CAIRO_CONTENT_COLOR,
                                       gtk_widget_get_allocated_width (widget),
                                       gtk_widget_get_allocated_height (widget));
  clear_surface ();
  return TRUE;
}

/* Redraw the screen from the surface */
static gboolean draw_cb (GtkWidget *widget, cairo_t   *cr,  gpointer   data){
  cairo_set_source_surface (cr, surface, 0, 0);
  cairo_paint (cr);

  return FALSE;
}



/* Mover window para esquerda */
extern "C" G_MODULE_EXPORT void left_window() {

}

/* Mover window para direita */
extern "C" G_MODULE_EXPORT void right_window() {

}

extern "C" G_MODULE_EXPORT void up_window() {

}

extern "C" G_MODULE_EXPORT void down_window() {

}

extern "C" G_MODULE_EXPORT void zoom_in() {

}

extern "C" G_MODULE_EXPORT void zoom_out() {

}

/* Adicionar nova linha */
 extern "C" G_MODULE_EXPORT void new_element(){
  gtk_widget_show_all(add_dialog);
} 

extern "C" G_MODULE_EXPORT void add_line_button() {
  cairo_t *cr;
  cr = cairo_create (surface);
  
  // int x1 = atoi((char*)gtk_entry_get_text(fieldx1Line));
  // int y1 = atoi((char*)gtk_entry_get_text(fieldy1Line));

  // int x2 = atoi((char*)gtk_entry_get_text(fieldx2Line));
  // int y2 = atoi((char*)gtk_entry_get_text(fieldy2Line));

  // cairo_move_to(cr, x1, y1);
  // cairo_line_to(cr, x2, y2);
  // cairo_stroke(cr);
  // gtk_widget_queue_draw (window_widget);
}




void initializeGTKComponentes() {
  gtkBuilder = gtk_builder_new();
  gtk_builder_add_from_file(gtkBuilder, "sgi.glade", NULL);

  window_widget = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "main_window") );
  drawing_area = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "drawing_area") );
  add_dialog = GTK_WIDGET( gtk_builder_get_object ( GTK_BUILDER(gtkBuilder), "add_window"));

}


int main(int argc, char *argv[]){
  gtk_init(&argc, &argv);

  initializeGTKComponentes(); 
  g_signal_connect (drawing_area, "draw", G_CALLBACK (draw_cb), NULL);
  g_signal_connect (drawing_area,"configure-event", G_CALLBACK (configure_event_cb), NULL);
  gtk_builder_connect_signals(gtkBuilder, NULL);
  gtk_widget_show_all(window_widget);
  gtk_main ();
  return 0;
}