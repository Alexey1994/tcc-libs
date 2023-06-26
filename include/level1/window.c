#ifndef SYSTEM_WINDOW_INCLUDED
#define SYSTEM_WINDOW_INCLUDED


#include <types.c>


typedef enum {
	NO_MESSAGES,
	UNKNOWN_GRAPHICS_MESSAGE,
	DRAW_MESSAGE,
	CREATE_GRAPHICS,
	DESTROY_GRAPHICS,
	CLICK_MESSAGE,
	BUTTON_DOWN_MESSAGE,
	BUTTON_UP_MESSAGE
}
Window_Message_Type;


typedef struct {
	Window_Message_Type type;
}
Window_Message;


/*typedef struct {
	Window_Message last_message;
	Byte*          window;
}
Window;*/


//Byte*   create_window           (Boolean (*handle_messages)(Number32 message_type, Number32 parameter1, Number32 parameter2));
//void    set_window_name         (Byte* window, Byte* name);
//void    set_window_position     (Byte* window, Number x, Number y, Number width, Number height);
//void    show_window             (Byte* window);
//void    hide_window             (Byte* window);
//void                repaint_window          (Byte* window);
//Window_Message_Type get_next_window_message (Byte* window);
//void                destroy_window     (Byte* window);


#ifdef __WIN32__


#include <Windows/user32.c>
#include <string.c>


typedef struct {
	Byte*           window;
	struct Window*  parent;
	Boolean       (*message_handler)(struct Window* parameters);
	Number32        message_type;
	Number32        parameter1;
	Number32        parameter2;
	Byte*           argument1;
	Byte*           argument2;
	Byte*           argument3;
	Byte*           argument4;
	Windows_Paint   draw;
}
Window;


static stdcall Number32 update_window_state(Byte* window, Windows_Message_Type type, Number32* parameter1, Number32* parameter2)
{
	Window* parameters;

	switch(type) {
		case CREATE_MESSAGE: {
			Create_Window* create_parameters = parameter2;
			SetWindowLongW(window, GWL_USERDATA, create_parameters->params);
			break;
		}
		
		case MOUSE_MOVE_MESSAGE: {
			Track_Mouse_Event_Params track_params = {
				.size = sizeof(Track_Mouse_Event_Params),
				.flags = TME_HOVER | TME_LEAVE, //TME_CANCEL | TME_HOVER | TME_LEAVE | TME_NONCLIENT,// | TME_QUERY
				.window = window,
				.hover_time = 1//0xFFFFFFFF
			};
			TrackMouseEvent(&track_params);
			break;
		}
	}
	
	parameters = GetWindowLongW(window, GWL_USERDATA);
	
	if(parameters) {
		parameters->message_type = type;
		parameters->parameter1 = parameter1;
		parameters->parameter2 = parameter2;
		parameters->message_handler(parameters);
	}

	return DefWindowProcW(window, type, parameter1, parameter2);
}


//static stdcall Number32 update_subwindow_state(Byte* window, Windows_Message_Type type, Number32* parameters_1, Integer_Number32* parameters_2)
//{
//	return DefWindowProcW(window, type, parameters_1, parameters_2);
//}


void initialize_window(Window* parameters, Window* parent, Boolean (*message_handler)(struct Window* parameters))
{
	Window_Class window_class = {
		.structure_size   = sizeof(Window_Class),
		.window_procedure = &update_window_state,
		//.style            = CS_HREDRAW | CS_VREDRAW,
		.background       = 0,//1,
		.cursor           = LoadCursorA(0, DEFAULT_ARROW),
		.class_name       = L"Window"
	};
	
	Byte* parent_window;
	
	parameters->parent = parent;
	parameters->message_handler = message_handler;

	parent_window = parameters->parent
		? ((Window*)parameters->parent)->window
		: 0;

	RegisterClassExW(&window_class);

	parameters->window = CreateWindowExW(
		WS_EX_CONTROLPARENT,
		L"Window",
		L"",
		parent_window
			? (WS_CHILD | WS_VISIBLE)
			: (WS_SYSMENU | WS_MAXIMIZEBOX | WS_SIZEBOX | WS_MINIMIZEBOX),// | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SIZEBOX,
		0x80000000,
		0x80000000,
		0,
		0,
		parent_window,
		0,
		0,
		parameters
	);
}


void deinitialize_window(Window* parameters)
{
	DestroyWindow(parameters->window);
}


Window* get_prev_window(Window* parameters)
{
	Byte*   prev_window;
	Window* prev_window_context;
	
	prev_window = GetWindow(parameters->window, GET_PREV_WINDOW);
	
	if(!prev_window) {
		return 0;
	}
	
	return GetWindowLongW(prev_window, GWL_USERDATA);
}


/*
void initialize_subwindow(Window* parent, Window* parameters)
{
	//Byte* window;
	Window_Class window_class = {
		.structure_size   = sizeof(Window_Class),
		.window_procedure = &update_window_state,
		.background       = 15,
		.cursor           = LoadCursorA(0, DEFAULT_ARROW),
		.class_name       = L"Subwindow"
	};

	RegisterClassExW(&window_class);

	parameters->window = CreateWindowExW(
		0,
		L"Subwindow",
		L"",
		WS_CHILD | WS_VISIBLE,
		0,//0x80000000,
		0,//0x80000000,
		200,
		200,
		parent->window,
		0,
		0,
		parameters
	);
	
	//SetWindowLongW(parameters->window, GWL_USERDATA, parameters);
}*/


void set_window_name(Window* parameters, Byte* name)
{
	Number16* unicode_name;

	unicode_name = convert_utf8_to_unicode(name);
	SetWindowTextW(parameters->window, unicode_name);
	free_memory(unicode_name);
}


void set_window_position(Window* parameters, Number x, Number y, Number width, Number height)
{
	MoveWindow(parameters->window, x, y, width, height, 1);
}


void get_window_position(Window* parameters, Number* x, Number* y, Number* width, Number* height)
{
	Windows_Rectangle rectangle;

	GetWindowRect(parameters->window, &rectangle);
	*x = rectangle.left;
	*y = rectangle.top;
	*width = rectangle.right - rectangle.left;
	*height = rectangle.bottom - rectangle.top;
}


void get_window_client_position(Window* parameters, Number* x, Number* y, Number* width, Number* height)
{
	Windows_Rectangle rectangle;

	GetClientRect(parameters->window, &rectangle);
	*x = rectangle.left;
	*y = rectangle.top;
	*width = rectangle.right - rectangle.left;
	*height = rectangle.bottom - rectangle.top;
}


void move_window_after(Window* parameters, Window* after)
{
	SetWindowPos(parameters->window, after->window, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
}


void move_window_in_top(Window* parameters)
{
	SetWindowPos(parameters->window, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
}


void move_window_in_bottom(Window* parameters)
{
	SetWindowPos(parameters->window, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
}


void redraw_window(Window* parameters)
{
	InvalidateRect(parameters->window, 0, 1);
}


Byte* begin_window_draw(Window* parameters)
{
	parameters->draw.erase_background = 1;
	return BeginPaint(parameters->window, &parameters->draw);
}

void end_window_draw(Window* parameters)
{
	EndPaint(parameters->window, &parameters->draw);
}


void show_window(Window* parameters)
{
	ShowWindow(parameters->window, SHOW_DEFAULT_WINDOW);
}

void show_maximized_window(Window* parameters)
{
	ShowWindow(parameters->window, SHOW_MAXIMIZED_WINDOW);
}

void show_fullscreen_window(Window* parameters)
{
	SetWindowLongW(parameters->window, GWL_STYLE, WS_POPUP | WS_VISIBLE);
	ShowWindow(parameters->window, SHOW_MAXIMIZED_WINDOW);
	redraw_window(parameters);
}

void hide_window_controls(Window* parameters)
{
	SetWindowLongW(parameters->window, GWL_STYLE, WS_POPUP | WS_VISIBLE);
	redraw_window(parameters);
}

void hide_window(Window* parameters)
{
	ShowWindow(parameters->window, HIDE_WINDOW);
}


Window_Message_Type pop_window_message()
{
	Windows_Message message;
	Boolean         has_messages;
	
	has_messages = PeekMessageW(&message, 0, 0, 0, REMOVE_MESSAGE_FROM_QUEUE);
	
	if(has_messages) { //&& !IsDialogMessageW(message.window, &message)) {
		if(!IsDialogMessageW(message.window, &message)) {
			TranslateMessage(&message);
			DispatchMessageW(&message);
		}
	}
	else {
		return NO_MESSAGES;
	}

	return message.type;
}

/*
Window_Message_Type get_next_window_message(Window* parameters)
{
	Windows_Message     message;
	Boolean             has_messages;
	Window_Message_Type window_message;
	//Byte*               dialog_modeles;
	//Byte*               accelerator;

	//do {
		has_messages = PeekMessageW(&message, 0, 0, 0, REMOVE_MESSAGE_FROM_QUEUE);
		
	//	if(
	//		has_messages
			//&& !IsDialogMessageW(window, &message)
			//&& !TranslateAcceleratorW(window, 0, &message)
	//	) {
	//		TranslateMessage(&message);
	//		DispatchMessageW(&message);
	//	}
	//}
	//while(has_messages && message.window != window);

	if(has_messages) {
		//print("-%d-", message.type);

		TranslateMessage(&message);
		DispatchMessageW(&message);

		switch(message.type) {
			case PAINT_MESSAGE:
				window_message = DRAW_MESSAGE;
				//print("{paint}");
				break;
			case CREATE_MESSAGE: window_message = CREATE_GRAPHICS; break;
			case DESTROY_MESSAGE: window_message = DESTROY_GRAPHICS; break;
			case WM_LBUTTONDOWN: window_message = BUTTON_DOWN_MESSAGE; break;
			case WM_LBUTTONUP: window_message = BUTTON_UP_MESSAGE; break;
			//case COMMAND_MESSAGE: window_message = CLICK_MESSAGE; print("command"); break;

			default:
				window_message = UNKNOWN_GRAPHICS_MESSAGE;
		}
	}
	else {
		return NO_MESSAGES;
	}

	return window_message;
}*/


Byte* get_window_display(Window* parameters)
{
	return GetDC(parameters->window);
}




Byte* create_button(Window* parent)
{
	Byte* button;

	button = CreateWindowExW(
		0,
		L"BUTTON",
		L"",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,// | BS_LEFT,
		0,
		0,
		50,
		20,
		parent->window,
		0,
		GetWindowLongW(parent->window, GWL_HINSTANCE),
		0
	);

	return button;
}


void set_button_text(Byte* button, Byte* text)
{
	Number16* button_text;

	button_text = convert_utf8_to_unicode(text);
	SendMessageW(button, SETTEXT_MESSAGE, 0, button_text);
	free_memory(button_text);
}


#endif//__WIN32__

#endif//SYSTEM_WINDOW_INCLUDED

/*
Byte* handle_messages(Window* window)
{
	print("{%d}", window->message_type);
	
	return 0;
}


Number main(Number number_of_arguments, Byte** arguments)
{
	Window window;

	initialize_window(&window, 0, &handle_messages);
	show_window(&window);
	
	for(;;) {
		pop_window_message();
	}
}*/

/*
#include <thread.c>
#include <graphics.c>


Byte* handle_messages(Window* window)
{
	print("{%d}", window->message_type);
	
	return 0;
}


Number main()
{
	Byte*               window;
	Byte*               subwindow;
	Window_Message_Type message;

	window = create_window(&handle_messages);
	//window = GetDesktopWindow();
	set_window_name(window, "WXВовкаWX");
	set_window_position(window, 0, 0, 200, 200);
	show_window(window);
	
	subwindow = create_subwindow(window, &handle_messages);//create_button(window);
	set_window_name(subwindow, "WXВовкаWX");
	set_window_position(subwindow, 0, 0, 200, 200);
	
	for(;;) {
		message = get_next_window_message(window);
			
		if(!message) {
			sleep_thread(4);
			continue;
		}
			
		if(message == DESTROY_GRAPHICS) {
			goto stop;
		}
		else if(message = DRAW_MESSAGE) {
			//print("paint");
			Byte* display = get_window_display(subwindow);
			draw_rectangle(display, 0, 0, 100, 100, 255 << 8);
			draw_text(display, "Жопка", 100, 100, 255);
		}
	}

	stop: {
		destroy_window(window);
	}
	
	return 0;
}*/