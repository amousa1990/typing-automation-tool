extern GtkWidget *main_window;
extern int typing;
extern int mouseclick_wait;
extern int clr_sleep;
extern int key_sleep;

void append(char * string,char ch)
{
  int size=strlen(string);
  char temp[size+1];
  strcpy(temp,string);
  temp[size]=ch;
  temp[size+1]='\0';
  strcpy(string,temp);
}

void type(char *string)
{
  if(!strcmp(string,"\new")) {
    g_print("implement here\n");
    GtkWidget *dialog;
    GtkWidget *label;
    GtkWidget *content_area;
    GtkWidget *new_set_entry;

    dialog = gtk_dialog_new_with_buttons ("New Button",GTK_WINDOW (main_window), GTK_DIALOG_MODAL, GTK_STOCK_OK,
      GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT, NULL);
    content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
    label = gtk_label_new ("New button name:");
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
    //start recording somehow
   gtk_widget_destroy (dialog);
 Display *display;
      display = XOpenDisplay(NULL);
      Window w,root;
      root = DefaultRootWindow(display);
      int x,y,i;
      int last_x,last_y;
      int second_x,second_y;
      unsigned m;
        XQueryPointer(display,root,&root,&w,&x,&y,&i,&i,&m);
            printf("\\(%i,%i)\n",x,y);
      while (1) {
        XQueryPointer(display,root,&root,&w,&x,&y,&i,&i,&m);
	if (last_x!=x && last_y!=y || last_x!=x && last_y==y || last_x==x && last_y!=y) {
	  second_x=last_x;
	  second_y=last_y;
	  last_x=x;
	  last_y=y;
          XQueryPointer(display,root,&root,&w,&x,&y,&i,&i,&m);
          printf("\\(%i,%i)\n",x,y);
	  usleep(300000);
        } else {
	//printf("value of x is %i and second_x i %i\n",x,second_x);
	  //if the mouse had not moved
	  if (x==second_x && second_y==y) {
	usleep(900000);
	  } else {
	usleep(200000);
	  }
          
	}
      }
      XCloseDisplay(display);
    break;

    case GTK_RESPONSE_REJECT:
    gtk_widget_destroy (dialog);
    break;

  }


    } else {
  gtk_widget_set_sensitive(main_window,FALSE);
  Display *display;
  display = XOpenDisplay(NULL);
  if(typing == 0) {
  //switch to active window: alt+tab
  printf("active window, alt+tab\n");
  XTestFakeKeyEvent(display, 64, True, 0);
  XTestFakeKeyEvent(display, 23, True, 0);
  XTestFakeKeyEvent(display, 23, False, 0);
  XTestFakeKeyEvent(display, 64, False, 0);
  XFlush(display);
  typing = 1;
  }
  usleep (300000);
  int size=strlen(string);
  int i;
  int modifier_key = 0; //0 for nothing, 1 for shift, 2 for ctrl
  int iterations = 0;
  int iteration_type =0;
  for (i=0;i<size;i++)
  {
  int keycode = 0;
    string[i];
    switch (string[i])
      {
      case ' ':
        keycode = 65;
      break;
      case 'e':
        keycode = 26;
      break;
      case 't':
        keycode = 28;
      break;
      case 'a':
        keycode = 38;
      break;
      case 'o':
        keycode = 32;
      break;
      case 'i':
        keycode = 31;
      break;
      case 'n':
        keycode = 57;
      break;
      case 's':
        keycode = 39;
      break;
      case 'h':
        keycode = 43;
      break;
      case 'r':
        keycode = 27;
      break;
      case 'd':
        keycode = 40;
      break;
      case 'l':
        keycode = 46;
      break;
      case 'c':
        keycode = 54;
      break;
      case 'u':
        keycode = 30;
      break;
      case 'm':
        keycode = 58;
      break;
      case 'w':
        keycode = 25;
      break;
      case 'f':
        keycode = 41;
      break;
      case 'g':
        keycode = 42;
      break;
      case 'y':
        keycode = 29;
      break;
      case 'p':
        keycode = 33;
      break;
      case 'b':
        keycode = 56;
      break;
      case 'v':
        keycode = 55;
      break;
      case 'k':
        keycode = 45;
      break;
      case 'j':
        keycode = 44;
      break;
      case 'x':
        keycode = 53;
      break;
      case 'q':
        keycode = 24;
      break;
      case 'z':
        keycode = 52;
      break;
      case '\\':
      if (string[i+1] != '(' && string[i+1]!= 'c' && string[i+2]>47 && string[i+2]<58 && iterations == 0) {
        iterations = g_ascii_digit_value(string[i+2]);
        printf("doing %i iterations\n",iterations);
      }
      switch (string[i+1])
	{
	case '(':	//mouse movement
	  usleep(mouseclick_wait);
	  i=i+2;
	  int c;
	  int x_coordinate = 0;
	  int x2_coordinate = 0;
	  int y_coordinate = 0;
	  int y2_coordinate = 0;
	  int action=0;
	  for (c=0;c<9;c++)
	  {  //x axis
	    if(string[i]>47 && string[i]<58) 
	    {
	      x_coordinate = x_coordinate * 10;
	      x_coordinate = x_coordinate + g_ascii_digit_value(string[i]);
	      i++;
	    }
	    else 
	    {
	      if (string[i]==',')
		c=9;
	      if (string[i]==';') //right click
	        action = -1;
	      if (string[i]=='.') {   //move, no click
		c=9;
	        action=-2;
	      }
	      if (string[i]=='-'){
		i++;
		action=action+1;
		for (c=0;c<4;c++){ //x2_coordinates
		  if(string[i]>47 && string[i]<58) { 
		     x2_coordinate = x2_coordinate * 10;
		     x2_coordinate = x2_coordinate + g_ascii_digit_value(string[i]);
		     i++;
		  }
		  //sleep(1);
		}
		  g_print("will drag till coordinate %i\n",x2_coordinate);

	      }
	    }
	  }
	  i++;
	  for (c=0;c<8;c++)
	  {  //y axis
	    if(string[i]>47 && string[i]<58)
	    {
	      y_coordinate = y_coordinate * 10;
	      y_coordinate = y_coordinate + g_ascii_digit_value(string[i]);
	      i++;
	    }
	    else {
	      if (string[i]=='-') {
		i++;
		action=action+2;
		for (c=0;c<4;c++){ //y2_coordinates
		  if(string[i]>47 && string[i]<58) { 
		     y2_coordinate = y2_coordinate * 10;
		     y2_coordinate = y2_coordinate + g_ascii_digit_value(string[i]);
		     i++;
		  }
		}
		g_print("will drag till %i\n",y2_coordinate);
	      }
	    }

	  }
	  g_print("x: %i\n",x_coordinate);
	  g_print("y: %i\n",y_coordinate);
	  XTestFakeMotionEvent(display,-1,x_coordinate,y_coordinate,0);
	  switch (action)
	  {
	    case -1: //right click
	      XTestFakeButtonEvent(display,3,True,CurrentTime);
	      XTestFakeButtonEvent(display,3,False,CurrentTime);
	    break;
	    case 0: //click
	      XTestFakeButtonEvent(display,1,True,CurrentTime);
	      XTestFakeButtonEvent(display,1,False,CurrentTime);
	    break;
	    case 1:   //x drag
	    printf("dragging\n");
	    XTestFakeButtonEvent(display,1,True,CurrentTime);
	    XTestFakeMotionEvent(display,-1,x2_coordinate,y_coordinate,0);
	    XTestFakeButtonEvent(display,1,False,CurrentTime);
	    break;
	    case 2:   //y drag
	    printf("y drag\n");
	    XTestFakeButtonEvent(display,1,True,CurrentTime);
	    XTestFakeMotionEvent(display,-1,x_coordinate,y2_coordinate,0);
	    XTestFakeButtonEvent(display,1,False,CurrentTime);
	    break;
	    case 3:  //diagonal drag
	    XTestFakeButtonEvent(display,1,True,CurrentTime);                   
	    XTestFakeMotionEvent(display,-1,x2_coordinate,y2_coordinate,0);
	    XTestFakeButtonEvent(display,1,False,CurrentTime);
	    break;
	  }
	  XFlush(display);
	  g_print("moved cursor,next char %c\n",string[i+1]);
	  usleep(10000);
	  i=i-1;
	break;
	case '1': //mouse click
	  XTestFakeButtonEvent(display,1,True,CurrentTime);
	  XTestFakeButtonEvent(display,1,False,CurrentTime);
	    XFlush(display);

	  usleep(500);
	  g_print("button pressed, next character is %c\n",string[i+1]);
	break;
	case '[':  //drag, format //[102-110,1000-1500]
	 i=i+2;
	break;
	case 'a': //alt
	  modifier_key = 3;
	break;
	case 'b':
          keycode = 22;
	  printf("backspace\n");
	break;
	case 'c': //ctrl+keycode
	if (string[i+2]=='m' && string[i+3]=='d') {   //\cmd(date)
	  i=i+5;
	  char command[256]="";
	  char out[256]="";
	  int special_character=0; //we use this to enable () in the commands
	  while(special_character!=0 || string[i]!=')') {
	    if (string[i] == ')')
	      special_character--;
	    if (string[i] == '(')
	      special_character++;
	    append(command,string[i]);
	    i++;
	  }
	  printf("will execute command %s\n",command);
	  FILE *cmd_pointer;
	  cmd_pointer = popen(command, "r");
	  while (fgets(command, sizeof(command)-1, cmd_pointer) != NULL) {
	    strcat(command,out);
	  }
	  pclose(cmd_pointer);
	  printf("result: %s",command);
	  typing = 1;
	  XFlush(display);
	  //usleep (20000);
	  type(command);
	} else if(string[i+2]=='l' && string[i+3]=='r') { //checking color \clr
	    //usleep(50000);
	    usleep(clr_sleep);
	    int loop_start = i; //for looping bak to the check
	    i=i+5;
	    int x_coordinate = 0;
	    while (string[i]!=')' && string[i]!= ',') {
	      x_coordinate = x_coordinate * 10;
	      x_coordinate = x_coordinate + g_ascii_digit_value(string[i]);
	      i++;
	    }
	      i++;
	    int y_coordinate = 0;
	    while (string[i]!=')' && string[i]!= ',') {
	      y_coordinate = y_coordinate * 10;
	      y_coordinate = y_coordinate + g_ascii_digit_value(string[i]);
	      i++;
	    } 
	      i++;
	    int color = 0;
	    int color_upper_bound = 0;
	    while (string[i]!=')' && string[i]!= ',') {
	      if (string[i] == '-') {
		i++;
		while (string[i]!=')' && string[i]!= ',') {
		  color_upper_bound = color_upper_bound * 10;
		  color_upper_bound = color_upper_bound + g_ascii_digit_value(string[i]);
		  i++;
		} 
	      g_print("color: %i, color upper bound: %i lower bound:%i\n",color,color_upper_bound,color);
	      } else {
		color = color * 10;
	        color = color + g_ascii_digit_value(string[i]);
	        i++;
	      }
	    }
	    if (color_upper_bound == 0)
	      color_upper_bound = color;
            Window root = XDefaultRootWindow(display);
	    XWindowAttributes attr;
	    XGetWindowAttributes(display, root, &attr);
            XImage *image;
            image = XGetImage(display,root,0,0,attr.width,attr.height,AllPlanes,ZPixmap);
            printf("x: %i, y: %i, pixel color: %i\n",x_coordinate,y_coordinate,XGetPixel(image,x_coordinate,y_coordinate));

	    g_print("x: %i, y: %i, colorshould be: %i\n",x_coordinate, y_coordinate, color);
	    int special_character=0; 
	    i=i+2;
	    char true_string[256] = "";
	    char false_string[256] = "";
	    int true_end = 0;
	    int loop = 0; //0= noloop 1= true reloop 2= false reloop
	    while(special_character < 1 ) {
              if (string[i] == '{')
                special_character--;
	      if (string[i] == '}') {
                special_character++;
	      }
	      if (string[i+1] == '\\') { //recheck
                if(string[i+2] == 'r' && string[i+3] == 'e' && string[i+4] == 'c' && string[i+5] == 'h' && string[i+6] == 'e' &&                     string[i+7] == 'c' && string[i+8] == 'k' ) {
		  printf("will loop\n");
		  special_character = 2;
		  i = i+9;
		  loop = 1;
		  typing = 1;
		}
	      }
	      append(true_string, string[i]);
	      i++;
	      true_end++ ;
	    }
	    true_string[true_end-1] = '\0';
	    printf("current character is %c\n",string[i]);
	    if(string[i] == '{') { //there is a false statement
	      special_character=0;
	      int false_end = 0;
	      i++;
	       while(special_character < 1 ) {
		 if (string[i] == '{')
		   special_character--;
		 if (string[i] == '}') {
		   special_character++;
		 }
		 if (string[i+1] == '\\') { //recheck
		   if(string[i+2] == 'r' && string[i+3] == 'e' && string[i+4] == 'c' && string[i+5] == 'h' && string[i+6] == 'e' &&                     string[i+7] == 'c' && string[i+8] == 'k' ) {
		     printf("will loop\n");
		     i=i+9;
		     special_character = 2;
		     loop = 2;
		     typing = 1;
		   }
		 }
		 append(false_string, string[i]);
		 i++;
		 false_end++ ;
	       }
	       false_string[false_end-1] = '\0';
	       printf("the false statement is %s\n",false_string);
	    }
	    int tested_color = XGetPixel(image,x_coordinate,y_coordinate);
	    if (tested_color >= color && tested_color <= color_upper_bound) { //color match
	      printf("true, will type: %s\n",true_string);
	      XFlush(display);
	      usleep(10000);
	      if (loop == 1) {
		i = loop_start;
		printf("true, reloopingthe value of loop_start is: %c\n",string[i+1]);
	        i--;
	      }
	      type(true_string);
	      i--;
	    }
	    else {
	      if (loop == 2) {
		i = loop_start;
		i--;
	      }
	       type(false_string);
	      printf("false\n");
	      i--;
	    }
	}
	else {
	  modifier_key=2;
	  g_print("the next character is %c\n",string[i+1]);
	}
	i--;
	break;
	//down
	case 'd':  //down
	if(string[i+2]=='o') {//\do(1000){hello world} 
	  i=i+4;
	    int iter = 0;
	    while (string[i]!=')' && string[i]!= ',') {
	    iter = iter * 10;
	    iter = iter + g_ascii_digit_value(string[i]);
	    i++;
	    }
	    i=i+2;
	    char loopstring[256]="";
	    while (string[i]!='}') {
	      //printf("%c",string[i]);
	      append(loopstring,string[i]);
	      i++;
	      }
	      for (int x=0;x<iter;x++) {
	        typing =1;
		type(loopstring);
		printf("iteration %i\n",x);
		}
	        //printf("%s\n",loopstring);
	    printf("iterating %i times\n",iter);
	}
	  else
            keycode = 116;
	break;
	case 'e': //end
	  keycode = 87;  //originally 87
	  if(string[i+2]=='s') {//esc
	    keycode = 9;
	    i++;
	    }
	break;
	case 'f': //f1-f9
	  switch(string[i+2]){
	  case '1':
	    keycode = 67;    
	  break;
	  case '2':
	    keycode = 68;    
	  break;
	  case '3':
	    keycode = 69;    
	  break;
	  case '4':
	    keycode = 70;    
	  break;
	  case '5':
	    keycode = 71;    
	  break;
	  case '6':
	    keycode = 72;    
	  break;
	  case '7':
	    keycode = 73;    
	  break;
	  case '8':
	    keycode = 74;    
	  break;
	  case '9':
	    keycode = 75;    
	  break;
	   
	  }
	break;
	case 'h'://home
          keycode = 110;
	break;
	case 'l':
	  keycode = 113;
	break;
        case 'n': //enter
          keycode = 36;
	break;
	case 'p': //pgup and pgdn
	  if(string[i+3] > 47 && string[i+3]< 58 && iterations == 0) {    //iterations
	    iteration_type = 1;
	    printf("current char: %c\n",string[i+3]);
	    iterations = g_ascii_digit_value(string[i+3]);
	    printf("iterating %i times\n",iterations);
	    }
	  if(string[i+2]=='u') //pgup
	    keycode = 112;
	  else //\pd page down
	    keycode= 117;
	break;
	case 'r':
          keycode = 114;
	break;
	case 's':	//sleep \s(5)
	if (string[i+2] != '(') {
	  g_print("incorrect sleep format\n");
	  break;
	}
	i=i+2;
	if (string[i]=='(')
	{
	  int sleep_time = 0;
	  int usleep_time = 0;
	  int usleep_time_counter = 0;
	  i++;
	  while(string[i]>47 && string[i]<58)      //break when a non numerical character is encoutnered, ideally a bracket
	  {
	    if (usleep_time_counter) {
	  //    usleep_time = sleep_time * 10;
	      usleep_time = sleep_time + g_ascii_digit_value(string[i]);
	    } else {
	      g_print("numeric character encountered: '%c'\n",string[i]);
	      sleep_time = sleep_time * 10;
	      sleep_time = sleep_time + g_ascii_digit_value(string[i]);
	      if(string[i+1]=='.')  {
	      usleep_time_counter = 1;
	      i++;
	      }
	    }
	      i++;
	  }
	  printf("sleeping for %i seconds\n",sleep_time);
	  sleep(sleep_time);
	  printf("sleeping for %i milliseconds\n",usleep_time * 100);
	  usleep(usleep_time*100000);
	}
	i=i-1;
	break;
	case 't': //tab
          keycode = 23;
	break;
	case 'u': 
	  keycode = 111;
	break;
	default:
          keycode = 51;
	break;
	}
	i=i+2;
      break;
      case 'T':
        keycode = 28;
	modifier_key = 1;
      break;
      case 'A':
        keycode = 38;
	modifier_key = 1;
      break;
      case 'S':
        keycode = 39;
	modifier_key = 1;
      break;
      case 'H':
        keycode = 43;
	modifier_key = 1;
      break;
      case 'W':
        keycode = 25;
	modifier_key = 1;
      break;
      case 'I':
        keycode = 31;
	modifier_key = 1;
      break;
      case 'O':
        keycode = 32;
	modifier_key = 1;
      break;
      case 'B':
        keycode = 56;
	modifier_key = 1;
      break;
      case 'M':
        keycode = 58;
	modifier_key = 1;
      break;
      case 'F':
        keycode = 41;
	modifier_key = 1;
      break;
      case 'C':
        keycode = 54;
	modifier_key = 1;
      break;
      case 'L':
        keycode = 46;
	modifier_key = 1;
      break;
      case 'D':
        keycode = 40;
	modifier_key = 1;
      break;
      case 'P':
        keycode = 33;
	modifier_key = 1;
      break;
      case 'N':
        keycode = 57;
	modifier_key = 1;
      break;
      case 'E':
        keycode = 26;
	modifier_key = 1;
      break;
      case 'G':
        keycode = 42;
	modifier_key = 1;
      break;
      case 'R':
        keycode = 27;
	modifier_key = 1;
      break;
      case 'Y':
        keycode = 29;
	modifier_key = 1;
      break;
      case 'U':
        keycode = 30;
	modifier_key = 1;
      break;
      case 'V':
        keycode = 55;
	modifier_key = 1;
      break;
      case 'J':
        keycode = 44;
	modifier_key = 1;
      break;
      case 'K':
        keycode = 45;
	modifier_key = 1;
      break;
      case 'Q':
        keycode = 24;
	modifier_key = 1;
      break;
      case 'Z':
        keycode = 52;
	modifier_key = 1;
      break;
      case 'X':
        keycode = 53;
	modifier_key = 1;
      break;
      case '!':
        keycode = 10;
	modifier_key = 1;
      break;
      case '@':
        keycode = 11;
	modifier_key = 1;
      break;
      case '#':
        keycode = 12;
	modifier_key = 1;
      break;
      case '$':
        keycode = 13;
	modifier_key = 1;
      break;
      case '%':
        keycode = 14;
	modifier_key = 1;
      break;
      case '^':
        keycode = 15;
	modifier_key = 1;
      break;
      case '&':
        keycode = 16;
	modifier_key = 1;
      break;
      case '*':
        keycode = 17;
	modifier_key = 1;
      break;
      case '(':
        keycode = 18;
	modifier_key = 1;
      break;
      case ')':
        keycode = 19;
	modifier_key = 1;
      break;
      case '0':
        keycode = 19;
      break;
      case '1':
        keycode = 10;
      break;
      case '2':
        keycode = 11;
      break;
      case '3':
        keycode = 12;
      break;
      case '4':
        keycode = 13;
      break;
      case '5':
        keycode = 14;
      break;
      case '6':
        keycode = 15;
      break;
      case '7':
        keycode = 16;
      break;
      case '8':
        keycode = 17;
      break;
      case '9':
        keycode = 18;
      break;
      case '-':
        keycode = 20;
      break;
      case '_':
        keycode = 20;
	modifier_key = 1;
      break;
      case '=':
        keycode = 21;
      break;
      case '+':
        keycode = 21;
	modifier_key = 1;
      break;
      case '`':
        keycode = 49;
      break;
      case '~':
        keycode = 49;
	modifier_key = 1;
      break;
      case '[':
        keycode = 34;
      break;
      case '{':
        keycode = 34;
	modifier_key = 1;
      break;
      case ']':
        keycode = 35;
      break;
      case '}':
        keycode = 35;
	modifier_key = 1;
      break;
      case '|':
        keycode = 51;
	modifier_key = 1;
      break;
      case ';':
        keycode = 47;
      break;
      case ':':
        keycode = 47;
	modifier_key = 1;
      break;
      case '\'':
        keycode = 48;
      break;
      case '"':
        keycode = 48;
	modifier_key = 1;
      break;
      case ',':
        keycode = 59;
      break;
      case '<':
        keycode = 59;
	modifier_key = 1;
      break;
      case '.':
        keycode = 60;
      break;
      case '>':
        keycode = 60;
	modifier_key = 1;
      break;
      case '/':
        keycode = 61;
      break;
      case '?':
        keycode = 61;
	modifier_key = 1;
      break;
      default:
      break;
    }
//    g_print("the current value of modifier is %i\n",modifier_key);
//    g_print("the keycode is %i\n",keycode);
//    g_print("the current value of i is %i\n",i);
    if (iterations > 1) {
      iterations--;
      if (iteration_type == 0)
        i=i-4;
      else
        i=i-5;
    i++;
    }
    else if(iterations ==1) 
    {
      iterations = 0;
      if (iteration_type == 1) {
        iteration_type=0;
	i++;
      }
    i++;
    }
    if (keycode!=0)
    {
      usleep(1000);
      switch (modifier_key)
      {
        case 0:
	  usleep(6000); //4000 was not good enough
          XTestFakeKeyEvent(display, keycode, True, 0);
          XTestFakeKeyEvent(display, keycode, False, 0);
        break;
        case 1: //shift press
          XTestFakeKeyEvent(display, 50, True, 0);
          XTestFakeKeyEvent(display, keycode, True, 0);
          XTestFakeKeyEvent(display, keycode, False, 0);
          XTestFakeKeyEvent(display, 50, False, 0);
	  modifier_key=0;
        break;
        case 2: //ctrl key
	  usleep(10);
          XTestFakeKeyEvent(display, 37, True, 0);
          XTestFakeKeyEvent(display, keycode, True, 0);
          XTestFakeKeyEvent(display, keycode, False, 0);
          XTestFakeKeyEvent(display, 37, False, 0);
          modifier_key=0;
	  g_print("pressed ctrl + %c\n",string[i]);
	  printf("next character %c\n",string[i+1]);
	  i++;
        break;
	case 3: //alt
	  usleep(10);
	  XTestFakeKeyEvent(display, 64, True, 0);
	  XTestFakeKeyEvent(display, keycode, True, 0);
	  XTestFakeKeyEvent(display, keycode, False, 0);
	  XTestFakeKeyEvent(display, 64, False, 0);
	  modifier_key=0;
	  g_print("pressed alt + %c\n",string[i]);
        break;
      }
    }
    usleep(key_sleep);
  XFlush(display);
  }
  XCloseDisplay(display);
  g_print("string size is %i\n",size);
  gtk_widget_set_sensitive(main_window,TRUE);
  typing =0;
  }
}
