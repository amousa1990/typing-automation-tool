extern GtkWidget *main_window;
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
  gtk_widget_set_sensitive(main_window,FALSE);
  Display *display;
  display = XOpenDisplay(NULL);
  //switch to active window: alt+tab
  XTestFakeKeyEvent(display, 64, True, 0);
  XTestFakeKeyEvent(display, 23, True, 0);
  XTestFakeKeyEvent(display, 23, False, 0);
  XTestFakeKeyEvent(display, 64, False, 0);
  XFlush(display);
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
	  usleep(800000);
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
		  g_print("will drag till coordinate %i\n",x2_coordinate);
		  //sleep(1);
		}

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
	if (string[i+2]=='m' && string[i+3]=='d'){   //\cmd(date)
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
	  XTestFakeKeyEvent(display, 64, True, 0);
	  XTestFakeKeyEvent(display, 23, True, 0);
	  XTestFakeKeyEvent(display, 23, False, 0);
	  XTestFakeKeyEvent(display, 64, False, 0);
	  XFlush(display);
	  //usleep (20000);
	  type(command);
	} else {
	  modifier_key=2;
	  g_print("the next character is %c\n",string[i+1]);
	}
	i--;
	break;
	//down
	case 'd':  //down
          keycode = 116;
	break;
	case 'e':
	  keycode = 87;
	break;
	case 'h'://home
          keycode = 110;
	break;
	case 'l':
	  keycode = 113;
	break;
        case 'n':
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
	i=i+2;
	if (string[i]=='(')
	{
	  int sleep_time = 0;
	  i++;
	  while(string[i]>47 && string[i]<58)      //break when a non number character is encoutnered, ideally a bracket
	  {
	    g_print("numeric character encountered: '%c'\n",string[i]);
	    sleep_time = sleep_time * 10;
	    sleep_time = sleep_time + g_ascii_digit_value(string[i]);
	    i++;
	  }
	  sleep(sleep_time);
	}
	i=i-1;
	break;
	case 't':
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
      switch (modifier_key)
      {
        case 0:
	  usleep(3000);
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
  XFlush(display);
  }
  XCloseDisplay(display);
  g_print("string size is %i\n",size);
  gtk_widget_set_sensitive(main_window,TRUE);
}
