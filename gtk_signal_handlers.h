extern GtkWidget *main_window;

struct parameters {
  GtkWidget *set_combo;
  GtkWidget *container;
  FILE *config_file;
  GtkWindow *main_window;
};

void destroy(GtkWidget *widget, GtkWidget *main_window) {
  //fclose((FILE *)config_file);
  gtk_main_quit ();
}



void set_changed(GtkComboBox *widget, gpointer callback_params) {
  gchar *active_set = gtk_combo_box_text_get_active_text ((GtkComboBoxText *)((struct parameters *) callback_params)->set_combo);
  g_print ("changing set to: %s\n",active_set);
  if (!strcmp(active_set,"add a new set")) {
     GtkWidget *dialog;
     GtkWidget *label;
     GtkWidget *content_area;
     GtkWidget *new_set_entry;

    dialog = gtk_dialog_new_with_buttons ("Adding a new set",GTK_WINDOW (main_window), GTK_DIALOG_MODAL, GTK_STOCK_OK, 
      GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT, NULL);
    content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
    label = gtk_label_new ("New set name:");
  //entry 
  new_set_entry = gtk_entry_new();
  gtk_container_add (GTK_CONTAINER (content_area), label);
  gtk_container_add (GTK_CONTAINER (content_area), new_set_entry);
  gint result;
  gtk_widget_show_all (dialog);
  result = gtk_dialog_run (GTK_DIALOG(dialog));
  switch (result)
  {
	case GTK_RESPONSE_OK:
	goto empty_statement;
	empty_statement: ;
        //gchar *new_set= gtk_entry_get_text(GTK_ENTRY (new_set_entry));
        gchar *new_set= gtk_entry_get_text((GtkEntry *) new_set_entry);
	  if (strlen(new_set)!=0) {
	  //add the new set to the config
	    g_print("please enter the set name\n");
	    char config_file_location[43];
	    char line_to_append[43];
	    strcpy (line_to_append,"set \"");
	    strcat (line_to_append,new_set);
	    strcat (line_to_append,"\"\n");
	    strcpy (config_file_location, getenv("HOME"));
  	    strcat(config_file_location,"/.tat");
	    FILE *pFile2;
	    pFile2 = fopen(config_file_location, "a");
	    fprintf(pFile2, "%s" , line_to_append);
	    //change to the new set and reload config
	    gtk_combo_box_text_insert_text((GtkComboBoxText *)((struct parameters *) callback_params)->set_combo , gtk_combo_box_get_active((GtkComboBox *)((struct parameters *) callback_params)->set_combo) , new_set);
	    gtk_combo_box_set_active((GtkComboBox *)((struct parameters *) callback_params)->set_combo , gtk_combo_box_get_active((GtkComboBox *)((struct parameters *) callback_params)->set_combo) -1 );
	    //gtk_combo_box_text_apend_text((GtkComboBoxText *)((struct parameters *) callback_params)->set_combo , new_set);
	    }
	  else 
	    g_print("please enter a set name\n");
	    gtk_widget_destroy (dialog);
            break;
        case GTK_RESPONSE_REJECT:
	    gtk_widget_destroy (dialog);
            break;
  }
  gtk_widget_show_all (dialog);
    }
  gchar * active_selection = gtk_combo_box_text_get_active_text ((GtkComboBoxText *)((struct parameters *) callback_params)->set_combo);
  read_button_config(((GtkContainer *)((struct parameters *) callback_params)->container),active_selection,((FILE *)((struct parameters *) callback_params)->config_file), ((GtkWindow *)((struct parameters *) callback_params)->main_window));
}


