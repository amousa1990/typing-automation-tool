#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include "type.h"
#include "read_config.h"
#include "gtk_signal_handlers.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>

GtkWidget *main_window; //this variable is defind globally, to keep the params of type function

//global config
int mouseclick_wait=800000;
int clr_sleep=0;
int key_sleep=0; //sleep after keypress
int x_coordinate = 0;
int y_coordinate = 0;
int typing = 0;
int main(int argc, char **argv) {
  switch(argc)
  {
  case 1:
  gtk_init(&argc, &argv);
  //determine config file location
  char config_file_location[43];
  FILE *config_file;
  GtkWidget *set_combo; 
  set_combo = gtk_combo_box_text_new();
  strcpy (config_file_location, getenv("HOME"));
  strcat(config_file_location,"/.tat.config");
  config_file=fopen(config_file_location,"ab+");
  read_config(config_file,(GtkComboBoxText *)set_combo);
  GtkWidget *container;
  container = gtk_vbox_new(0,0);
  main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  //test

  gtk_window_set_title(GTK_WINDOW(main_window),"tat");
  gtk_window_set_keep_above ( (GtkWindow *) main_window, TRUE); //always on top
  gtk_container_add (GTK_CONTAINER (main_window) , container);
  gtk_container_add (GTK_CONTAINER (container), set_combo);
  gtk_signal_connect (GTK_OBJECT (main_window), "destroy",GTK_SIGNAL_FUNC (destroy), &main_window);  //exit function
  static struct parameters changed_set_parameters;
  changed_set_parameters.set_combo = set_combo;
  changed_set_parameters.container = container;
  changed_set_parameters.config_file = config_file;
  changed_set_parameters.main_window = (GtkWindow *)main_window;
  gtk_signal_connect (GTK_OBJECT (set_combo), "changed",GTK_SIGNAL_FUNC(set_changed), &changed_set_parameters); //read the button config for that set
  gtk_widget_show_all(main_window);
  gtk_main ();
  break;

  default:
  if (strcmp(argv[1],"mouse")==0)
    {
      if (argc > 2)
        sleep(atoi(argv[2]));
      Display *display;
      display = XOpenDisplay(NULL);
      Window w,root;
      root = DefaultRootWindow(display);
      int x,y,i;
      unsigned m;
      XQueryPointer(display,root,&root,&w,&x,&y,&i,&i,&m);
      printf("\\(%i,%i)\n",x,y);
      XCloseDisplay(display);
      }
else if (strcmp(argv[1],"color")==0)
  {
    if (argc > 2)
      sleep(atoi(argv[2]));
    //usleep(100000);
    Display *display;
    display = XOpenDisplay(NULL);
    //display = XOpenDisplay("localhost:0.0");
    if (!display) {fprintf(stderr, "unable to connect to display\n");return 7;}
    Window w;
    int x,y,i;
    unsigned m;
    Window root = XDefaultRootWindow(display);
    if (!root) {fprintf(stderr, "unable to open rootwindow");return 8;}
    if(!XQueryPointer(display,root,&root,&w,&x,&y,&i,&i,&m))
    {  printf("unable to query pointer\n"); return 9;}
    XImage *image;
    XWindowAttributes attr;
    XGetWindowAttributes(display, root, &attr);
    image = XGetImage(display,root,0,0,x+1,y+1,AllPlanes,ZPixmap);
    if (!image) {printf("unable to get image\n"); return 10;}
    unsigned long pixel = XGetPixel(image,x,y);
    printf("\\clr(%i,%i,%lu){}\n",x,y,pixel);
    XCloseDisplay(display);
  }
  else if (strcmp(argv[1],"test")==0) {
    
    type(argv[2]);
  }
  break;
  }

  return 0;
}
