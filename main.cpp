#include <gtk/gtk.h>
#include <iostream>

#include <vector>
#include <stdio.h>
#include <string.h>
#include "viewport.h"
#include "window.h"
#include "line.h"
#include "point.h"
#include "polygon.h"
#include "hermitespline.h"
#include "bspline.h"
#include "canvas.h"
#include "displayfile.h"

#define Z_STUB 0

using namespace std;

Window window;
Viewport viewport;
Displayfile displayFile;
int clippingType = 1;

static cairo_surface_t *surface = NULL;
GtkWidget *drawing_area;
GtkWidget *window_widget;

GtkBuilder *gtkBuilder;
GtkWidget *add_dialog;
GtkWidget *edit_dialog;

GtkWidget *console;
GtkNotebook *notebook;

GtkListStore *list_store;
GtkTreeView *list_objects;
GtkCellRenderer *renderer;

GtkEntry *entry_object_name;

GtkEntry* entry_x_angle;
GtkEntry* entry_y_angle;
GtkEntry* entry_z_angle;

GtkListStore *pointsPolygon;

vector<Coordenada*> polygonCoordinate;
vector<Coordenada*> bsplineCoordinate;

GtkEntry *entry_x_point;
GtkEntry *entry_y_point;
GtkEntry *entry_z_point;

GtkEntry *polygon_x;
GtkEntry *polygon_y;
GtkEntry *polygon_z;

GtkEntry *bspline_x;
GtkEntry *bspline_y;
GtkEntry *bspline_z;


GtkEntry *entry_x1_line;
GtkEntry *entry_y1_line;
GtkEntry *entry_z1_line;
GtkEntry *entry_x2_line;
GtkEntry *entry_y2_line;
GtkEntry *entry_z2_line;

GtkEntry *entry_p1_hermite;
GtkEntry *entry_p4_hermite;
GtkEntry *entry_r1_hermite;
GtkEntry *entry_r4_hermite;

GtkEntry *entry_p1_x_hermite; 
GtkEntry *entry_p1_y_hermite;
GtkEntry *entry_p1_z_hermite; 
GtkEntry *entry_p4_x_hermite; 
GtkEntry *entry_p4_y_hermite;
GtkEntry *entry_p4_z_hermite;    
GtkEntry *entry_r1_x_hermite; 
GtkEntry *entry_r1_y_hermite;
GtkEntry *entry_r1_z_hermite; 
GtkEntry *entry_r4_x_hermite; 
GtkEntry *entry_r4_y_hermite;
GtkEntry *entry_r4_z_hermite;

GtkEntry *entry_x_translate;
GtkEntry *entry_y_translate;
GtkEntry *entry_z_translate;

GtkEntry *entry_x_scale;
GtkEntry *entry_y_scale;
GtkEntry *entry_z_scale;

GtkEntry *entry_x_rotate;
GtkEntry *entry_y_rotate;

GtkEntry *zoom_factor;
GtkEntry *step_factor;
GtkEntry *angle_factor;


Object *toEdit;


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
  displayFile.deleteAll();

  gtk_widget_queue_draw (window_widget);
}

extern "C" G_MODULE_EXPORT void rotate_window() {
  cairo_t *cr = cairo_create (surface);
  clear_surface();

  float factor = atof((char*)gtk_entry_get_text(angle_factor));
  window.setAngle(factor);

  for (Object* object : displayFile.getObjects()) {
    object->draw(viewport, window, cr, clippingType);
  }

  gtk_widget_queue_draw (window_widget);
}

extern "C" G_MODULE_EXPORT void clipping_event() {
  clippingType = 0;
  printf("%s\n", " Clipping type setado para 0");
}

extern "C" G_MODULE_EXPORT void clipping_event2() {
  clippingType = 1;
  printf("%s\n", " Clipping type setado para 1");
}


/* Mover window para esquerda */
extern "C" G_MODULE_EXPORT void left_window() {
  cairo_t *cr = cairo_create (surface);
  clear_surface();

  int factor = atoi((char*)gtk_entry_get_text(step_factor));
  window.setXmin(-1.0 * factor);
  window.setXmax(-1.0 * factor);
  window.refreshCenter();
  
  for (Object* object : displayFile.getObjects()) {
    object->draw(viewport, window, cr, clippingType);
  }

  gtk_widget_queue_draw (window_widget);
}

/* Mover window para direita */
extern "C" G_MODULE_EXPORT void right_window() {
  cairo_t *cr = cairo_create (surface);
  clear_surface();

  int factor = atoi((char*)gtk_entry_get_text(step_factor));
  window.setXmin(factor);
  window.setXmax(factor);
  window.refreshCenter();

  for (Object* object : displayFile.getObjects()) {
    object->draw(viewport, window, cr, clippingType);
  }

  gtk_widget_queue_draw (window_widget);
}

extern "C" G_MODULE_EXPORT void up_window() {
  cairo_t *cr = cairo_create (surface);
  clear_surface();

  int factor = atoi((char*)gtk_entry_get_text(step_factor));
  window.setYmin(factor);
  window.setYmax(factor);
  window.refreshCenter();
  
  for (Object* object : displayFile.getObjects()) {
    object->draw(viewport, window, cr, clippingType);
  }

  gtk_widget_queue_draw (window_widget);
}

extern "C" G_MODULE_EXPORT void down_window() {
  cairo_t *cr = cairo_create (surface);
  clear_surface();

  int factor = atoi((char*)gtk_entry_get_text(step_factor));
  window.setYmin(-1 * factor);
  window.setYmax(-1 * factor);
  window.refreshCenter();

  for (Object* object : displayFile.getObjects()) {
    object->draw(viewport, window, cr, clippingType);
  }

  gtk_widget_queue_draw (window_widget);
}

extern "C" G_MODULE_EXPORT void zoom_in() {
  cairo_t *cr = cairo_create (surface);
  clear_surface();

  int factor = atoi((char*)gtk_entry_get_text(zoom_factor));
  
  window.setXmin(factor);
  window.setYmin(factor);
  
  window.setXmax(-1 * factor);
  window.setYmax(-1 * factor);
  
  for (Object* object : displayFile.getObjects()) {
    object->draw(viewport, window, cr , clippingType);
  }

  gtk_widget_queue_draw (window_widget);
}

extern "C" G_MODULE_EXPORT void zoom_out() {
  cairo_t *cr = cairo_create (surface);
  clear_surface();

  int factor = atoi((char*)gtk_entry_get_text(zoom_factor));
  
  window.setXmin(-1 * factor);
  window.setYmin(-1 * factor);
  
  window.setXmax(factor);
  window.setYmax(factor);
  
  for (Object* object : displayFile.getObjects()) {
    object->draw(viewport, window, cr, clippingType);
  }

  gtk_widget_queue_draw (window_widget);
}

extern "C" G_MODULE_EXPORT void new_element(){
  gtk_widget_show_all(add_dialog);
} 

extern "C" G_MODULE_EXPORT void edit_element(){
  GtkTreeIter iter;
  GtkTreeModel *model;

  model = gtk_tree_view_get_model(list_objects);
  if (gtk_tree_selection_get_selected (gtk_tree_view_get_selection(list_objects), &model, &iter )){
    gchar *value;
    gtk_tree_model_get (model, &iter, 0, &value, -1);

    char* name = ((char*) value);
    toEdit = displayFile.getObjectByName(name);
    printf("%s\n", toEdit->getName());

    gtk_widget_show_all(edit_dialog);
  }
  
} 


extern "C" G_MODULE_EXPORT void rotate_object(){
  int angleX = atoi((char*)   gtk_entry_get_text(entry_x_angle));
  int angleY = atoi((char*) gtk_entry_get_text(entry_y_angle));
  int angleZ = atoi((char*) gtk_entry_get_text(entry_z_angle));
  
  char* entry_x_s = (char*) gtk_entry_get_text(entry_x_rotate);
  char* entry_y_s = (char*) gtk_entry_get_text(entry_x_rotate);

  float entryX = atof(entry_x_s);
  float entryY = atof(entry_y_s);

  printf("%s\n", (char*)gtk_entry_get_text(entry_x_rotate));

  if (strcmp(entry_x_s, "") != 0 && strcmp(entry_y_s, "") != 0) {
      toEdit->rotateUsingCoordinate(angleZ, entryX, entryY);
  } else {
      toEdit->rotate(angleZ);
  }

  cairo_t *cr = cairo_create (surface);
  clear_surface();
  
  for (Object* object : displayFile.getObjects()) {
    object->draw(viewport, window, cr, clippingType);
  }

  gtk_widget_queue_draw (window_widget);

}

extern "C" G_MODULE_EXPORT void scale_object(){
  float entryX = atof((char*)gtk_entry_get_text(entry_x_scale));
  float entryY = atof((char*)gtk_entry_get_text(entry_y_scale));
  float entryZ = atof((char*)gtk_entry_get_text(entry_z_scale));

  toEdit->scale(entryX, entryY, entryZ);

  cairo_t *cr = cairo_create (surface);
  clear_surface();
  
  for (Object* object : displayFile.getObjects()) {
    object->draw(viewport, window, cr, clippingType);
  }

  gtk_widget_queue_draw (window_widget);

}

extern "C" G_MODULE_EXPORT void translate_object() {
  int entryX = atoi((char*)gtk_entry_get_text(entry_x_translate));
  int entryY = atoi((char*)gtk_entry_get_text(entry_y_translate));
  int entryZ = atoi((char*)gtk_entry_get_text(entry_z_translate));

  toEdit->translate(entryX, entryY, entryZ);

  cairo_t *cr = cairo_create (surface);
  clear_surface();
  
  for (Object* object : displayFile.getObjects()) {
    object->draw(viewport, window, cr, clippingType);
  }

  gtk_widget_queue_draw (window_widget);

}


char* getCurrentLabel(){
  return (char*) gtk_notebook_get_tab_label_text(notebook, gtk_notebook_get_nth_page(notebook, gtk_notebook_get_current_page(notebook)));
}

extern "C" G_MODULE_EXPORT void add_point_event() {
  int x = atoi((char*) gtk_entry_get_text(polygon_x));
  int y = atoi((char*) gtk_entry_get_text(polygon_y));
  int z = atoi((char*) gtk_entry_get_text(polygon_z));

  polygonCoordinate.push_back(new Coordenada(x, y, z));
}

extern "C" G_MODULE_EXPORT void add_point_bspline_event() {
  int x = atoi((char*)gtk_entry_get_text(bspline_x));
  int y = atoi((char*)gtk_entry_get_text(bspline_y));
  int z = atoi((char*)gtk_entry_get_text(bspline_z));

  bsplineCoordinate.push_back(new Coordenada(x, y, z));
}

extern "C" G_MODULE_EXPORT void add_confirm_event() {
  cairo_t *cr = cairo_create (surface);

  char* label = getCurrentLabel();
  char* entry_name = (char*) gtk_entry_get_text(entry_object_name);
  int size = sizeof(entry_name)/sizeof(char);
  char *name = new char[size];
  strncpy(name, entry_name, size);

  if (strcmp(label, "Point") == 0) {
    int x = atoi((char*)gtk_entry_get_text(entry_x_point));
    int y = atoi((char*)gtk_entry_get_text(entry_y_point));
    int z = atoi((char*)gtk_entry_get_text(entry_z_point));
    
    vector<Coordenada*> points;
    points.push_back(new Coordenada(x, y, z));
    Point* point = new Point(name, points);
    displayFile.addNewObject(point);
    point->draw(viewport, window, cr, clippingType);

  } else if (strcmp(label, "Line") == 0) {
    int x1 = atoi((char*)gtk_entry_get_text(entry_x1_line));
    int y1 = atoi((char*)gtk_entry_get_text(entry_y1_line));
    int z1 = atoi((char*)gtk_entry_get_text(entry_z1_line));

    int x2 = atoi((char*)gtk_entry_get_text(entry_x2_line));
    int y2 = atoi((char*)gtk_entry_get_text(entry_y2_line));
    int z2 = atoi((char*)gtk_entry_get_text(entry_z2_line));

    vector<Coordenada*> points;
    points.push_back(new Coordenada(x1, y1, z1));
    points.push_back(new Coordenada(x2, y2, z2));
    Line* line = new Line(name, points);
    displayFile.addNewObject(line);
    line->draw(viewport, window, cr, clippingType);
    
  } else if (strcmp(label, "Polygon") == 0) {
    Polygon* polygon = new Polygon(name, polygonCoordinate);
    displayFile.addNewObject(polygon);
    polygon->draw(viewport, window, cr, clippingType);
    polygonCoordinate.clear();
  } else if (strcmp(label, "Hermite") == 0) {

    int p1_x = atoi((char*)gtk_entry_get_text(entry_p1_x_hermite));
    int p1_y = atoi((char*)gtk_entry_get_text(entry_p1_y_hermite));
    int p1_z = atoi((char*)gtk_entry_get_text(entry_p1_z_hermite));

    int p4_x = atoi((char*)gtk_entry_get_text(entry_p4_x_hermite));
    int p4_y = atoi((char*)gtk_entry_get_text(entry_p4_y_hermite));
    int p4_z = atoi((char*)gtk_entry_get_text(entry_p4_z_hermite));

    int r1_x = atoi((char*)gtk_entry_get_text(entry_r1_x_hermite));
    int r1_y = atoi((char*)gtk_entry_get_text(entry_r1_y_hermite));
    int r1_z = atoi((char*)gtk_entry_get_text(entry_r1_z_hermite));

    int r4_x = atoi((char*)gtk_entry_get_text(entry_r4_x_hermite));
    int r4_y = atoi((char*)gtk_entry_get_text(entry_r4_y_hermite));
    int r4_z = atoi((char*)gtk_entry_get_text(entry_r4_z_hermite));


    vector<Coordenada*> points;
    HermiteSpline* spline = new HermiteSpline(name, points, new Coordenada(p1_x, p1_y, p1_z), 
      new Coordenada(p4_x, p4_y, p4_z), new Coordenada(r1_x, r1_y, r1_z), new Coordenada(r4_x, r4_y, r4_z));
    displayFile.addNewObject(spline);
    spline->draw(viewport, window, cr, clippingType);
  } else if (strcmp(label, "BSpline") == 0) {
    vector<Coordenada*> coordenadas;
    BSpline* bspline = new BSpline(name, coordenadas, bsplineCoordinate);
    displayFile.addNewObject(bspline);
    bspline->draw(viewport, window, cr, clippingType);
    bsplineCoordinate.clear();
  }

  GtkTreeIter iter;
  gtk_list_store_append(list_store, &iter);
  gtk_list_store_set(list_store, &iter, 0, name, 1, "teste", -1);


  cairo_stroke(cr);
  gtk_widget_queue_draw (window_widget);
  gtk_widget_hide(add_dialog);
}


extern "C" G_MODULE_EXPORT void create_window() {
  cairo_t *cr = cairo_create (surface);
  vector<Coordenada*> coordenadas;
  coordenadas.push_back(new Coordenada(-0.9, -0.9, Z_STUB));
  coordenadas.push_back(new Coordenada(0.9, -0.9, Z_STUB));
  coordenadas.push_back(new Coordenada(0.9, 0.9, Z_STUB));
  coordenadas.push_back(new Coordenada(-0.9, 0.9, Z_STUB));
  Canvas* canvas = new Canvas("window", coordenadas);
  displayFile.addNewObject(canvas);
  canvas->draw(viewport, window, cr, clippingType);
  cairo_stroke(cr);
  gtk_widget_queue_draw (window_widget);
}




void initializeGTKComponentes() {
  gtkBuilder = gtk_builder_new();
  gtk_builder_add_from_file(gtkBuilder, "sgi_test.glade", NULL);

  window_widget = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "main_window") );
  drawing_area = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "drawing_area") );
  add_dialog = GTK_WIDGET( gtk_builder_get_object ( GTK_BUILDER(gtkBuilder), "add_window"));
  edit_dialog = GTK_WIDGET( gtk_builder_get_object ( GTK_BUILDER(gtkBuilder), "edit_window"));

  //console = GTK_WIDGET( gtk_builder_get_object ( GTK_BUILDER(gtkBuilder), "console"));
  notebook = GTK_NOTEBOOK ( gtk_builder_get_object (GTK_BUILDER (gtkBuilder), "add_notebook"));

  entry_object_name = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_object_name"));

  entry_p1_x_hermite = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_p1_x_hermite"));
  entry_p1_y_hermite = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_p1_y_hermite"));
  entry_p1_z_hermite = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_p1_z_hermite"));
  entry_p4_x_hermite = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_p4_x_hermite"));
  entry_p4_y_hermite = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_p4_y_hermite"));
  entry_p4_z_hermite = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_p4_z_hermite"));
  entry_r1_x_hermite = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_r1_x_hermite"));
  entry_r1_y_hermite = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_r1_y_hermite"));
  entry_r1_z_hermite = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_r1_z_hermite"));
  entry_r4_x_hermite = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_r4_x_hermite"));
  entry_r4_y_hermite = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_r4_y_hermite"));
  entry_r4_z_hermite = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_r4_z_hermite"));

  entry_x1_line = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_x1_line"));
  entry_y1_line = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_y1_line"));
  entry_z1_line = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_z1_line"));
  entry_x2_line = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_x2_line"));
  entry_y2_line = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_y2_line"));
  entry_z2_line = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_z2_line"));

  entry_x_point = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_x_point"));
  entry_y_point = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_y_point"));
  entry_z_point = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_z_point"));

  bspline_x = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "bspline_x"));
  bspline_y = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "bspline_y"));
  bspline_z = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "bspline_z"));

  entry_x_translate = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_x_translate"));
  entry_y_translate = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_y_translate"));
  entry_z_translate = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_z_translate"));

  entry_x_scale = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_x_scale"));
  entry_y_scale = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_y_scale"));
  entry_z_scale = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_z_scale"));

  entry_x_angle = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_x_angle"));
  entry_y_angle = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_y_angle"));
  entry_z_angle = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_z_angle"));

  entry_x_rotate = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_x_rotate"));
  entry_y_rotate = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "entry_y_rotate"));

  zoom_factor = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "zoom_factor"));
  step_factor = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "step_factor"));
  angle_factor = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "angle_factor"));
  
  polygon_x = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "polygon_x"));
  polygon_y = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "polygon_y"));
  polygon_z = GTK_ENTRY ( gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "polygon_z"));

  list_objects = GTK_TREE_VIEW( gtk_builder_get_object( gtkBuilder, "list_objects" ) );

  list_store = gtk_list_store_new (2, G_TYPE_STRING, G_TYPE_STRING);
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (list_objects,
                                             -1,
                                             "Name",  
                                             renderer,
                                             "text", 0,
                                             NULL);

  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (list_objects,
                                             -1,
                                             "Type",
                                             renderer,
                                             "text", 1,
                                             NULL);
  gtk_tree_view_set_model (list_objects, GTK_TREE_MODEL (list_store));
  gtk_tree_view_column_set_min_width ( gtk_tree_view_get_column (list_objects, 0), 100 );
  gtk_tree_view_column_set_alignment ( gtk_tree_view_get_column (list_objects, 0), 0.5 );
  gtk_tree_view_column_set_alignment ( gtk_tree_view_get_column (list_objects, 1), 0.5 );

}


int main(int argc, char *argv[]){
  gtk_init(&argc, &argv);
  window = Window(15.0, 15.0, 285.0, 285.0);

  initializeGTKComponentes(); 
  g_signal_connect (drawing_area, "draw", G_CALLBACK (draw_cb), NULL);
  g_signal_connect (drawing_area,"configure-event", G_CALLBACK (configure_event_cb), NULL);
  g_signal_connect(add_dialog, "delete_event", G_CALLBACK (gtk_widget_hide_on_delete), NULL);
  g_signal_connect(edit_dialog, "delete_event", G_CALLBACK (gtk_widget_hide_on_delete), NULL);
  gtk_builder_connect_signals(gtkBuilder, NULL);
  
  gtk_widget_show_all(window_widget);
  gtk_main ();
  return 0;
}
