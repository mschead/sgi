#include <gtk/gtk.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include "viewport.h"
#include "window.h"
#include "displayfile.h"

using namespace std;

Window window;
Viewport viewport;
Displayfile displayFile;

static cairo_surface_t *surface = NULL;
GtkWidget *drawing_area;
GtkWidget *window_widget;

GtkBuilder *gtkBuilder;
GtkWidget *add_dialog;

GtkWidget *console;
GtkNotebook *notebook;

GtkEntry *entry_object_name;

GtkEntry *entry_x_point;
GtkEntry *entry_y_point;
GtkEntry *polygon_x;
GtkEntry *polygon_y;

std::vector<int> xPolygon;
std::vector<int>  yPolygon;
int polygonPoint = 0;

GtkEntry *entry_x1_line;
GtkEntry *entry_y1_line;
GtkEntry *entry_x2_line;
GtkEntry *entry_y2_line;

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


/* Limpar canvas */
extern "C" G_MODULE_EXPORT void clear_event(){
  clear_surface ();

  gtk_widget_queue_draw (window_widget);
}

/* Mover window para esquerda */
extern "C" G_MODULE_EXPORT void left_window() {
  cairo_t *cr;
  cr = cairo_create (surface);

  window.setXmin(-10);
  window.setXmax(-10);
  
  Object object = displayFile.getObject();

  vector<Coordenada*> coordenadas = object.getPoints();
  Coordenada* c1 = coordenadas.at(0);
  Coordenada* c2 = coordenadas.at(1);


  int x1 = viewport.obterXdaViewport(c1->getX(), window.getXmin(), window.getXmax());
  int y1 = viewport.obterYdaViewport(c1->getY(), window.getYmin(), window.getYmax());

  int x2 = viewport.obterXdaViewport(c2->getX(), window.getXmin(), window.getXmax());
  int y2 = viewport.obterYdaViewport(c2->getY(), window.getYmin(), window.getYmax());


  clear_surface();
  cairo_move_to(cr, x1, y1);
  cairo_line_to(cr, x2, y2);

  // printf("%d\n", x1);
  // printf("%d\n", y1);
  // printf("%d\n", x2);
  // printf("%d\n", y2);

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

 extern "C" G_MODULE_EXPORT void new_element(){
  gtk_widget_show_all(add_dialog);
} 

char* getCurrentLabel(){
  return (char*) gtk_notebook_get_tab_label_text(notebook, gtk_notebook_get_nth_page(notebook, gtk_notebook_get_current_page(notebook)));
}

extern "C" G_MODULE_EXPORT void add_point_event() {
  xPolygon.push_back(atoi((char*)gtk_entry_get_text(polygon_x)));
  yPolygon.push_back(atoi((char*)gtk_entry_get_text(polygon_y)));

  polygonPoint++;
}

extern "C" G_MODULE_EXPORT void add_confirm_event() {
  cairo_t *cr;
  cr = cairo_create (surface);

  char* label = getCurrentLabel();
  printf("%s\n",label);

  char* name = (char*) gtk_entry_get_text(entry_object_name);

  if (strcmp(label, "Point") == 0) {
    int x = atoi((char*)gtk_entry_get_text(entry_x_point));
    int y = atoi((char*)gtk_entry_get_text(entry_y_point));

    x = viewport.obterXdaViewport(x, window.getXmin(), window.getXmax());
    y = viewport.obterYdaViewport(y, window.getYmin(), window.getYmax());

    cairo_arc(cr, x, y, 1, 0, 2*3.1415);

  } else if (strcmp(label, "Line") == 0) {
    int x1 = atoi((char*)gtk_entry_get_text(entry_x1_line));
    int y1 = atoi((char*)gtk_entry_get_text(entry_y1_line));

    int x2 = atoi((char*)gtk_entry_get_text(entry_x2_line));
    int y2 = atoi((char*)gtk_entry_get_text(entry_y2_line));

    x1 = viewport.obterXdaViewport(x1, window.getXmin(), window.getXmax());
    y1 = viewport.obterYdaViewport(y1, window.getYmin(), window.getYmax());

    x2 = viewport.obterXdaViewport(x2, window.getXmin(), window.getXmax());
    y2 = viewport.obterYdaViewport(y2, window.getYmin(), window.getYmax());

    vector<Coordenada*> points{new Coordenada(x1, y1), new Coordenada(x2, y2)};
    Object object = Object(name, Tipo::reta, points);
    displayFile.addNewObject(object);

    cairo_move_to(cr, x1, y1);
    cairo_line_to(cr, x2, y2);
    
  } else if (strcmp(label, "Polygon") == 0) {
    int x_inicial, y_inicial, x_final, y_final;
    int n =0;
    int totalSide = polygonPoint;
    int x_init;
    int y_init;
    x_init = xPolygon.front();
    y_init = yPolygon.front();

    for(n=0; n<totalSide; n++){
     x_inicial = xPolygon.back();
     xPolygon.pop_back();
     y_inicial = yPolygon.back();
     yPolygon.pop_back();
	if(n==totalSide-1){
 	x_final = x_init;
	y_final = y_init;
        }else{
        x_final = xPolygon.back();
	y_final = yPolygon.back();
	}

    x_inicial = viewport.obterXdaViewport(x_inicial, window.getXmin(), window.getXmax());
    y_inicial = viewport.obterYdaViewport(y_inicial, window.getYmin(), window.getYmax());

    x_final = viewport.obterXdaViewport(x_final, window.getXmin(), window.getXmax());
    y_final = viewport.obterYdaViewport(y_final, window.getYmin(), window.getYmax());

    vector<Coordenada*> points{new Coordenada(x_inicial, y_inicial), new Coordenada(x_final, y_final)};

    Object object = Object(name, Tipo::reta, points);
    displayFile.addNewObject(object);

    cairo_move_to(cr, x_inicial, y_inicial);
    cairo_line_to(cr, x_final, y_final);
    polygonPoint =0;
    }
  }

  cairo_stroke(cr);
  gtk_widget_queue_draw (window_widget);
  gtk_widget_hide(add_dialog);
}





void initializeGTKComponentes() {
  gtkBuilder = gtk_builder_new();
  gtk_builder_add_from_file(gtkBuilder, "sgi_test.glade", NULL);

  window_widget = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "main_window") );
  drawing_area = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "drawing_area") );
  add_dialog = GTK_WIDGET( gtk_builder_get_object ( GTK_BUILDER(gtkBuilder), "add_window"));

  console = GTK_WIDGET( gtk_builder_get_object ( GTK_BUILDER(gtkBuilder), "console"));
  notebook = GTK_NOTEBOOK ( gtk_builder_get_object (GTK_BUILDER (gtkBuilder), "add_notebook"));

  entry_object_name = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_object_name"));

  entry_x1_line = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_x1_line"));
  entry_y1_line = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_y1_line"));
  entry_x2_line = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_x2_line"));
  entry_y2_line = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_y2_line"));

  entry_x_point = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_x_point"));
  entry_y_point = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_y_point"));

  polygon_x = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "polygon_x"));
  polygon_y = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "polygon_y"));
}


int main(int argc, char *argv[]){
  gtk_init(&argc, &argv);
  window = Window(0, 0, 500, 500);


  initializeGTKComponentes(); 
  g_signal_connect (drawing_area, "draw", G_CALLBACK (draw_cb), NULL);
  g_signal_connect (drawing_area,"configure-event", G_CALLBACK (configure_event_cb), NULL);
  gtk_builder_connect_signals(gtkBuilder, NULL);
  gtk_widget_show_all(window_widget);
  gtk_main ();
  return 0;
}
