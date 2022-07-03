extern int mouseclick_wait;
extern int x_coordinate;
extern int y_coordinate;
extern int clr_sleep;
extern int key_sleep;

void read_button_config(GtkContainer *container, gchar *active_selection, FILE *config_file, GtkWindow *main_window) {
  GList *container_children, *iter;
  container_children = gtk_container_get_children(GTK_CONTAINER(container));
  for(iter = container_children; iter != NULL; iter = g_list_next(iter)) { 
    if (GTK_IS_BUTTON(iter->data))
      gtk_widget_destroy(GTK_WIDGET(iter->data));
  }
  g_list_free(container_children);
  rewind(config_file);
  char line[2048];
  int current_line_number = 0;
  while (fgets(line, sizeof line, config_file) != NULL) {
    current_line_number++;
    if (g_ascii_strncasecmp(line+5,active_selection,g_utf8_strlen(active_selection,-1))==0) {
    while (fgets(line, sizeof line, config_file) != NULL) {
    if (strncmp(line , "set ", 4)==0)
      break;
    if (strncmp(line , "button", 6)==0) {
      char temp[sizeof(line)];
      strcpy(temp,line+7);
      const char *p1 = strstr(line, "\"")+1;
      const char *p2 = strstr(p1, "\"");
      size_t len = p2-p1;
      char *button_label = (char*)malloc(sizeof(char)*(len+1));
      strncpy(button_label, p1, len);
      button_label[len] = '\0';
      GtkWidget *button = gtk_button_new_with_label (button_label);
      const char *p3 = strstr(p2, "\"")+1;
       if (p3[1]!='\"') {
	 GtkWidget *dialog = gtk_message_dialog_new((GtkWindow*)main_window,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"The text for button %s was not specified \n line %i:\n %s",button_label,current_line_number,line);
         gint response = gtk_dialog_run (GTK_DIALOG (dialog));
         gtk_widget_destroy (dialog);
	 break;
         }
       char *p4 = strstr(p3, "\"")+1;
       //this line is for lines not ending in " by mistake
       if (p4[strlen(p4)-2] == '\"')
	 p4[strlen(p4)-2] = '\0';
       else {
	 int i ;
	 for (i=strlen(p4);i>0;i--)
	   if (p4[i] == '\"')
	     p4[i] = '\0';
       }
       gtk_signal_connect_object (GTK_OBJECT (button), "clicked",GTK_SIGNAL_FUNC (type),g_strdup(p4));
       gtk_container_add (GTK_CONTAINER (container), button);
       gtk_widget_show_all ((GtkWidget *)container);
       free(button_label);
       }
       g_print("implement new button here\n");
    }
       //implement the new button here, connect the signal handler
       char *button_label = "add a new button";
       GtkWidget *button = gtk_button_new_with_label (button_label);
       gtk_container_add (GTK_CONTAINER (container), button);
       gtk_widget_show_all ((GtkWidget *)container);
       gtk_signal_connect_object (GTK_OBJECT (button), "clicked",GTK_SIGNAL_FUNC (type),"\new");
  }
}
}

void read_config(FILE * config_file,GtkComboBoxText *set_combo) {
char line[32];
char set_name[32]="";
int c = 0;
  while (fgets(line, 32, config_file) != NULL) { //read till end of line
    if (strncmp(line , "x: " , 3)==0) {
      char x_coordinate_string[4] = "";
      for (c=3;line[c]>47 && line[c]<58; c++) {
	append(x_coordinate_string, line[c]);
      }
      x_coordinate = atoi(x_coordinate_string);
    }
    else if (strncmp(line , "y: " , 3)==0) {
      char y_coordinate_string[4] = "";
      for (c=3;line[c]>47 && line[c]<58; c++) {
	append(y_coordinate_string, line[c]);
      }
      y_coordinate = atoi(y_coordinate_string);
    }
    else if (strncmp(line , "mouseclick_wait " , 16)==0) { //how long to wait after a mouse click
      char mouseclick_wait_string[10]="";
      for (c=16;line[c]>47 && line[c]<58; c++) {
	append(mouseclick_wait_string , line[c]);
      }
      append(mouseclick_wait_string , '\0');
      g_print("value of mouseclick_wait is %s\n" , mouseclick_wait_string);
      mouseclick_wait = atoi(mouseclick_wait_string);
    } else if (strncmp(line , "clr_sleep " , 10)==0) { //how long to sleep after checking a color
        char clr_sleep_string[10]="";
        for (c=10;line[c]>47 && line[c]<58; c++) {
	  append(clr_sleep_string , line[c]);
	}
	append(clr_sleep_string , '\0');
	g_print("value of clr_sleep is %s\n" , clr_sleep_string);         
     	clr_sleep = atoi(clr_sleep_string);
    }	    
    else if (strncmp(line , "sleep " , 6)==0) { //read the set name
        char key_sleep_string[10]="";
        for (c=6;line[c]>47 && line[c]<58; c++) {
          append(key_sleep_string , line[c]);
        }
        append(key_sleep_string , '\0');
        key_sleep = atoi(key_sleep_string);
        g_print("value of key_sleep is %s\n" , key_sleep_string);
    }

    else if (strncmp(line , "set ", 4)==0 && line[4]=='\"') { //read the set name
      for (c=5;c < 32; c++) {
	if (line[c]=='\0'|| line[c]=='\n' || line[c]=='"') //end of set name
	  break;
	append(set_name, line[c]); 
      }
      gtk_combo_box_text_append_text(set_combo,set_name);
      memset(&set_name[0], 0, sizeof(set_name));
    }
  }
  gtk_combo_box_text_append_text(set_combo,"add a new set");
}

