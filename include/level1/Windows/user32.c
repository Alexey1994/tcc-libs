#ifndef SYSTEM_WINDOWS_USER32_INCLUDED
#define SYSTEM_WINDOWS_USER32_INCLUDED


#include <types.c>
#include <Windows/gdi32.c>


//https://docs.microsoft.com/en-us/windows/win32/winprog/windows-data-types
//https://github.com/tpn/winsdk-10/blob/master/Include/10.0.10240.0/um/WinUser.h


#define DEFAULT_ICON                                32512
#define DEFAULT_ARROW                               32512

//#define POPUP_WINDOW_STYLE                          0x80000000
//#define USER_DATA                                   -21


typedef enum {
	// Window messages
	GETTEXTLENGTH_MESSAGE          = 0x000E,
	GETTEXT_MESSAGE                = 0x000D,
	SIZE_MESSAGE                   = 0x0005,
	SIZING_MESSAGE                 = 0x0214,
	USER_MESSAGE                   = 0X0400,

	CREATE_MESSAGE                 = 0x0001,
	DESTROY_MESSAGE                = 0x0002,
	MOVE_MESSAGE                   = 0x0003,
	WM_SIZE                        = 0x0005,
	ACTIVATE_MESSAGE               = 0x0006,
	SETFOCUS_MESSAGE               = 0x0007,
	KILLFOCUS_MESSAGE              = 0x0008,
	ENABLE_MESSAGE                 = 0x000A,
	SETREDRAW_MESSAGE              = 0x000B,
	SETTEXT_MESSAGE                = 0x000C,
	WM_GETTEXT                     = 0x000D,
	PAINT_MESSAGE                  = 0x000F,
	CLOSE_MESSAGE                  = 0x0010,
	QUERYENDSESSION_MESSAGE        = 0x0011,
	QUIT_MESSAGE                   = 0x0012,
	QUERYOPEN_MESSAGE              = 0x0013,
	ERASEBKGND_MESSAGE             = 0x0014,
	SYSCOLORCHANGE_MESSAGE         = 0x0015,
	ENDSESSION_MESSAGE             = 0x0016,
	SHOWWINDOW_MESSAGE             = 0x0018,

	SETTINGCHANGE_MESSAGE          = 0x001A,
	WININICHANGE_MESSAGE           = 0x001A,
	DEVMODECHANGE_MESSAGE          = 0x001B,
	ACTIVATEAPP_MESSAGE            = 0x001C,
	FONTCHANGE_MESSAGE             = 0x001D,
	TIMECHANGE_MESSAGE             = 0x001E,
	CANCELMODE_MESSAGE             = 0x001F,

	IME_STARTCOMPOSITION_MESSAGE   = 0x010D,
	IME_ENDCOMPOSITION_MESSAGE     = 0x010E,
	IME_COMPOSITION_MESSAGE        = 0x010F,

	SETCURSOR_MESSAGE              = 0x0020,
	MOUSEACTIVATE_MESSAGE          = 0x0021,
	CHILDACTIVATE_MESSAGE          = 0x0022,
	QUEUESYNC_MESSAGE              = 0x0023,
	GETMINMAXINFO_MESSAGE          = 0x0024,
	PAINTICON_MESSAGE              = 0x0026,
	ICONERASEBKGND_MESSAGE         = 0x0027,
	NEXTDLGCTL_MESSAGE             = 0x0028,
	SPOOLERSTATUS_MESSAGE          = 0x002A,
	DRAWITEM_MESSAGE               = 0x002B,
	MEASUREITEM_MESSAGE            = 0x002C,
	DELETEITEM_MESSAGE             = 0x002D,
	VKEYTOITEM_MESSAGE             = 0x002E,
	CHARTOITEM_MESSAGE             = 0x002F,
	SETFONT_MESSAGE                = 0x0030,
	GETFONT_MESSAGE                = 0x0031,
	SETHOTKEY_MESSAGE              = 0x0032,
	GETHOTKEY_MESSAGE              = 0x0033,
	QUERYDRAGICON_MESSAGE          = 0x0037,
	COMPAREITEM_MESSAGE            = 0x0039,
	GETOBJECT_MESSAGE              = 0x003D,
	COMPACTING_MESSAGE             = 0x0041,
	COMMNOTIFY_MESSAGE             = 0x0044,
	WINDOWPOSCHANGING_MESSAGE      = 0x0046,
	WINDOWPOSCHANGED_MESSAGE       = 0x0047,
	POWER_MESSAGE                  = 0x0048,
	NOTIFY_MESSAGE                 = 0x004E,
	COPYDATA_MESSAGE               = 0x004A,
	CANCELJOURNAL_MESSAGE          = 0x004B,
	INPUTLANGCHANGEREQUEST_MESSAGE = 0x0050,
	INPUTLANGCHANGE_MESSAGE        = 0x0051,
	TCARD_MESSAGE                  = 0x0052,
	HELP_MESSAGE                   = 0x0053,
	USERCHANGED_MESSAGE            = 0x0054,
	NOTIFYFORMAT_MESSAGE           = 0x0055,

	PARENTNOTIFY_MESSAGE           = 0x0210,
	ENTERMENULOOP_MESSAGE          = 0x0211,
	EXITMENULOOP_MESSAGE           = 0x0212,
	NEXTMENU_MESSAGE               = 0x0213,
	WM_SIZING                      = 0x0214,
	CAPTURECHANGED_MESSAGE         = 0x0215,
	MOVING_MESSAGE                 = 0x0216,
	POWERBROADCAST_MESSAGE         = 0x0218,
	DEVICECHANGE_MESSAGE           = 0x0219,
	MDICREATE_MESSAGE              = 0x0220,
	MDIDESTROY_MESSAGE             = 0x0221,
	MDIACTIVATE_MESSAGE            = 0x0222,
	MDIRESTORE_MESSAGE             = 0x0223,
	MDINEXT_MESSAGE                = 0x0224,
	MDIMAXIMIZE_MESSAGE            = 0x0225,
	MDITILE_MESSAGE                = 0x0226,
	MDICASCADE_MESSAGE             = 0x0227,
	MDIICONARRANGE_MESSAGE         = 0x0228,
	MDIGETACTIVE_MESSAGE           = 0x0229,
	MDISETMENU_MESSAGE             = 0x0230,
	ENTERSIZEMOVE_MESSAGE          = 0x0231,
	EXITSIZEMOVE_MESSAGE           = 0x0232,
	DROPFILES_MESSAGE              = 0x0233,
	MDIREFRESHMENU_MESSAGE         = 0x0234,
	IME_SETCONTEXT_MESSAGE         = 0x0281,
	IME_NOTIFY_MESSAGE             = 0x0282,
	IME_CONTROL_MESSAGE            = 0x0283,
	IME_COMPOSITIONFULL_MESSAGE    = 0x0284,
	IME_SELECT_MESSAGE             = 0x0285,
	IME_CHAR_MESSAGE               = 0x0286,
	IME_REQUEST_MESSAGE            = 0x0288,
	IME_KEYDOWN_MESSAGE            = 0x0290,
	IME_KEYUP_MESSAGE              = 0x0291,
	NCMOUSEHOVER_MESSAGE           = 0x02A0,
	MOUSEHOVER_MESSAGE             = 0x02A1,
	NCMOUSELEAVE_MESSAGE           = 0x02A2,
	MOUSELEAVE_MESSAGE             = 0x02A3,
	WTSSESSION_CHANGE_MESSAGE      = 0x02B1,
	TABLET_FIRST_MESSAGE           = 0x02C0,
	TABLET_LAST_MESSAGE            = 0x02DF,

	CUT_MESSAGE                    = 0x0300,
	COPY_MESSAGE                   = 0x0301,
	PASTE_MESSAGE                  = 0x0302,
	CLEAR_MESSAGE                  = 0x0303,
	UNDO_MESSAGE                   = 0x0304,
	PALETTEISCHANGING_MESSAGE      = 0x0310,
	HOTKEY_MESSAGE                 = 0x0312,
	PALETTECHANGED_MESSAGE         = 0x0311,
	PRINT_MESSAGE                  = 0x0317,
	PRINTCLIENT_MESSAGE            = 0x0318,
	APPCOMMAND_MESSAGE             = 0x0319,
	QUERYNEWPALETTE_MESSAGE        = 0x030F,
	THEMECHANGED_MESSAGE           = 0x031A,
	HANDHELDFIRST_MESSAGE          = 0x0358,
	HANDHELDLAST_MESSAGE           = 0x035F,
	AFXFIRST_MESSAGE               = 0x0360,
	AFXLAST_MESSAGE                = 0x037F,
	PENWINFIRST_MESSAGE            = 0x0380,
	PENWINLAST_MESSAGE             = 0x038F,

	CONTEXTMENU_MESSAGE            = 0x007B,
	STYLECHANGING_MESSAGE          = 0x007C,
	STYLECHANGED_MESSAGE           = 0x007D,
	DISPLAYCHANGE_MESSAGE          = 0x007E,
	GETICON_MESSAGE                = 0x007F,
	SETICON_MESSAGE                = 0x0080,
	NCCREATE_MESSAGE               = 0x0081,
	NCDESTROY_MESSAGE              = 0x0082,
	NCCALCSIZE_MESSAGE             = 0x0083,
	NCHITTEST_MESSAGE              = 0x0084,
	NCPAINT_MESSAGE                = 0x0085,
	NCACTIVATE_MESSAGE             = 0x0086,
	GETDLGCODE_MESSAGE             = 0x0087,
	SYNCPAINT_MESSAGE              = 0x0088,

	//события в верхней полоске окна
	NCMOUSEMOVE_MESSAGE            = 0x00A0,
	NCLBUTTONDOWN_MESSAGE          = 0x00A1,
	NCLBUTTONUP_MESSAGE            = 0x00A2,
	NCLBUTTONDBLCLK_MESSAGE        = 0x00A3,
	NCRBUTTONDOWN_MESSAGE          = 0x00A4,
	NCRBUTTONUP_MESSAGE            = 0x00A5,
	NCRBUTTONDBLCLK_MESSAGE        = 0x00A6,
	NCMBUTTONDOWN_MESSAGE          = 0x00A7,
	NCMBUTTONUP_MESSAGE            = 0x00A8,
	NCMBUTTONDBLCLK_MESSAGE        = 0x00A9,
	NCXBUTTONDOWN_MESSAGE          = 0x00AB,
	NCXBUTTONUP_MESSAGE            = 0x00AC,
	NCXBUTTONDBLCLK_MESSAGE        = 0x00AD,

	KEY_DOWN_MESSAGE               = 0x0100,
	KEYFIRST_MESSAGE               = 0x0100,
	KEY_UP_MESSAGE                 = 0x0101,
	CHAR_MESSAGE                   = 0x0102,
	DEADCHAR_MESSAGE               = 0x0103,
	SYSKEYDOWN_MESSAGE             = 0x0104,
	SYSKEYUP_MESSAGE               = 0x0105,
	SYSCHAR_MESSAGE                = 0x0106,
	SYSDEADCHAR_MESSAGE            = 0x0107,
	KEYLAST_MESSAGE                = 0x0109,
	UNICHAR_MESSAGE                = 0x0109,

	INITDIALOG_MESSAGE             = 0x0110,
	COMMAND_MESSAGE                = 0x0111,
	SYSCOMMAND_MESSAGE             = 0x0112,
	TIMER_MESSAGE                  = 0x0113,
	HSCROLL_MESSAGE                = 0x0114,
	VSCROLL_MESSAGE                = 0x0115,
	INITMENU_MESSAGE               = 0x0116,
	INITMENUPOPUP_MESSAGE          = 0x0117,
	MENUSELECT_MESSAGE             = 0x011F,
	MENUCHAR_MESSAGE               = 0x0120,
	ENTERIDLE_MESSAGE              = 0x0121,
	MENURBUTTONUP_MESSAGE          = 0x0122,
	MENUDRAG_MESSAGE               = 0x0123,
	MENUGETOBJECT_MESSAGE          = 0x0124,
	UNINITMENUPOPUP_MESSAGE        = 0x0125,
	MENUCOMMAND_MESSAGE            = 0x0126,
	CHANGEUISTATE_MESSAGE          = 0x0127,
	UPDATEUISTATE_MESSAGE          = 0x0128,
	QUERYUISTATE_MESSAGE           = 0x0129,
	CTLCOLORMSGBOX_MESSAGE         = 0x0132,
	CTLCOLOREDIT_MESSAGE           = 0x0133,
	CTLCOLORLISTBOX_MESSAGE        = 0x0134,
	CTLCOLORBTN_MESSAGE            = 0x0135,
	CTLCOLORDLG_MESSAGE            = 0x0136,
	CTLCOLORSCROLLBAR_MESSAGE      = 0x0137,
	CTLCOLORSTATIC_MESSAGE         = 0x0138,
	CTLCOLOR_MESSAGE               = 0x0019,

	// Button messages
	MOUSE_MOVE_MESSAGE  = 0x0200,
	WM_LBUTTONDOWN      = 0x0201,
	WM_LBUTTONUP        = 0x0202,
	WM_LBUTTONDBLCLK    = 0x0203,
	WM_RBUTTONDOWN      = 0x0204,
	WM_RBUTTONUP        = 0x0205,
	WM_RBUTTONDBLCLK    = 0x0206,
	WM_MBUTTONDOWN      = 0x0207,
	WM_MBUTTONUP        = 0x0208,
	WM_MBUTTONDBLCLK    = 0x0209,
	WM_MOUSEWHEEL       = 0x020A,

	// Edit text messages
	EM_CANUNDO             = 0x00C6,
	EM_CHARFROMPOS         = 0x00D7,
	EM_EMPTYUNDOBUFFER     = 0x00CD,
	EM_FMTLINES            = 0x00C8,
	EM_GETCUEBANNER        = 0x1502, // (ECM_FIRST + 2) Unicode
	EM_GETFIRSTVISIBLELINE = 0x00CE,
	EM_GETHANDLE           = 0x00BD,
	EM_GETHILITE           = 0x1506, // (ECM_FIRST + 6) Unicode >= Vista, not documented
	EM_GETIMESTATUS        = 0x00D9,
	EM_GETLIMITTEXT        = 0x00D5,
	EM_GETLINE             = 0x00C4,
	EM_GETLINECOUNT        = 0x00BA,
	EM_GETMARGINS          = 0x00D4,
	EM_GETMODIFY           = 0x00B8,
	EM_GETPASSWORDCHAR     = 0x00D2,
	EM_GETRECT             = 0x00B2,
	EM_GETSEL              = 0x00B0,
	EM_GETTHUMB            = 0x00BE,
	EM_GETWORDBREAKPROC    = 0x00D1,
	EM_HIDEBALLOONTIP      = 0x1504, // (ECM_FIRST + 4) Unicode
	EM_LIMITTEXT           = 0x00C5,
	EM_LINEFROMCHAR        = 0x00C9,
	EM_LINEINDEX           = 0x00BB,
	EM_LINELENGTH          = 0x00C1,
	EM_LINESCROLL          = 0x00B6,
	EM_POSFROMCHAR         = 0x00D6,
	EM_REPLACESEL          = 0x00C2,
	EM_SCROLL              = 0x00B5,
	EM_SCROLLCARET         = 0x00B7,
	EM_SETCUEBANNER        = 0x1501, // (ECM_FIRST + 1) Unicode
	EM_SETHANDLE           = 0x00BC,
	EM_SETHILITE           = 0x1505, // (ECM_FIRST + 5) Unicode >= Vista, not documented
	EM_SETIMESTATUS        = 0x00D8,
	EM_SETLIMITTEXT        = 0x00C5, // EM_LIMITTEXT
	EM_SETMARGINS          = 0x00D3,
	EM_SETMODIFY           = 0x00B9,
	EM_SETPASSWORDCHAR     = 0x00CC,
	EM_SETREADONLY         = 0x00CF,
	EM_SETRECT             = 0x00B3,
	EM_SETRECTNP           = 0x00B4,
	EM_SETSEL              = 0x00B1,
	EM_SETTABSTOPS         = 0x00CB,
	EM_SETWORDBREAKPROC    = 0x00D0,
	EM_SHOWBALLOONTIP      = 0x1503, // (ECM_FIRST + 2) Unicode
	EM_UNDO                = 0x00C7,

	// List Box messages
	LB_ADDSTRING      = 0x0180,
	LB_INSERTSTRING   = 0x0181,
	LB_DELETESTRING   = 0x0182,
	LB_SELITEMRANGEEX = 0x0183,
	LB_RESETCONTENT   = 0x0184,
	LB_SETSEL         = 0x0185,
	LB_SETCURSEL      = 0x0186,
	LB_GETSEL         = 0x0187,
	LB_GETCURSEL      = 0x0188,
	LB_GETTEXT        = 0x0189,
	LB_GETTEXTLEN     = 0x018A,
	LB_GETCOUNT       = 0x018B,
	LB_SELECTSTRING   = 0x018C,
	LB_DIR            = 0x018D,
	LB_GETTOPINDEX    = 0x018E,
	LB_FINDSTRING     = 0x018F,
	LB_GETSELCOUNT    = 0x0190,
	LB_GETSELITEMS    = 0x0191,
	LB_SETTABSTOPS    = 0x0192,
	LB_GETHORIZONTALEXTENT= 0x0193,
	LB_SETHORIZONTALEXTENT= 0x0194,
	LB_SETCOLUMNWIDTH = 0x0195,
	LB_ADDFILE        = 0x0196,
	LB_SETTOPINDEX    = 0x0197,
	LB_GETITEMRECT= 0x0198,
	LB_GETITEMDATA= 0x0199,
	LB_SETITEMDATA= 0x019A,
	LB_SELITEMRANGE= 0x019B,
	LB_SETANCHORINDEX= 0x019C,
	LB_GETANCHORINDEX= 0x019D,
	LB_SETCARETINDEX= 0x019E,
	LB_GETCARETINDEX= 0x019F,
	LB_SETITEMHEIGHT= 0x01A0,
	LB_GETITEMHEIGHT= 0x01A1,
	LB_FINDSTRINGEXACT= 0x01A2,
	LB_SETLOCALE= 0x01A5,
	LB_GETLOCALE= 0x01A6,
	LB_SETCOUNT= 0x01A7,
	LB_INITSTORAGE= 0x01A8,
	LB_ITEMFROMPOINT= 0x01A9,

	LBN_ERRSPACE  = (-2),
	LBN_SELCHANGE = 1,
	LBN_DBLCLK    = 2,
	LBN_SELCANCEL = 3,
	LBN_SETFOCUS  = 4,
	LBN_KILLFOCUS = 5
}
Windows_Message_Type;

typedef struct {
	Byte*                window;
	Windows_Message_Type type;
	Number*              parameter1;
	Signed_Number*       parameter2;
	Number32             time;
	Windows_Point        point;
	Number               pad;
}
Windows_Message;

typedef enum {
	NO_REMOVE_MESSAGE_FROM_QUEUE = 0x0000,
	REMOVE_MESSAGE_FROM_QUEUE    = 0x0001,
	NO_YIELD_MESSAGE_FROM_QUEUE  = 0x0002
}
Remove_Message_From_Queue;

import stdcall Number32         PeekMessageA     (Windows_Message* message, Byte* window, Number32 filter_min, Number32 filter_max, Remove_Message_From_Queue remove_type);
import stdcall Number32         PeekMessageW     (Windows_Message* message, Byte* window, Number32 filter_min, Number32 filter_max, Remove_Message_From_Queue remove_type);
import stdcall Signed_Number32  DispatchMessageA (Windows_Message* message);
import stdcall Signed_Number32  DispatchMessageW (Windows_Message* message);
import stdcall Number32         TranslateMessage (Windows_Message* message);
import stdcall Number32         GetMessageA      (Windows_Message* message, Byte* window, Number32 filter_min, Number32 filter_max);
import stdcall Number32         GetMessageW      (Windows_Message* message, Byte* window, Number32 filter_min, Number32 filter_max);
import stdcall Number32         SendMessageA     (Byte* window, Windows_Message_Type type, Number16 short_parameter, Number32 long_parameter);
import stdcall Number32         SendMessageW     (Byte* window, Windows_Message_Type type, Number16 short_parameter, Number32 long_parameter);
import stdcall Boolean          PostMessageA     (Byte* window, Windows_Message_Type type, Number16 short_parameter, Number32 long_parameter);
import stdcall Boolean          PostMessageW     (Byte* window, Windows_Message_Type type, Number16 short_parameter, Number32 long_parameter);
import stdcall void             PostQuitMessage  (Number32 exit_code);
import stdcall Boolean          IsDialogMessageW (Byte* window, Windows_Message* message);
import stdcall Boolean          TranslateAcceleratorW (Byte* window, Byte* accelerator_table, Windows_Message* message);


typedef struct {

}
Icon;

typedef struct {

}
Cursor;

typedef struct {

}
Brush;

typedef struct {
	Signed_Number32 left;
	Signed_Number32 top;
	Signed_Number32 right;
	Signed_Number32 bottom;
}
Windows_Rectangle;

typedef struct {
	Byte*             context;
	Signed_Number32   erase_background;
	Windows_Rectangle rectangle;
	Signed_Number32   restore;
	Signed_Number32   update;
	Byte              color[36];
}
Windows_Paint;


typedef enum {
	//REDRAW_IF_CHANGED_WINDOW_SIZE  = 0x0001,
	CS_VREDRAW                     = 0x0001,
	CS_HREDRAW                     = 0x0002,
	CS_DBLCLKS                     = 0x0008,
	OWN_WINDOW_CONTEXT             = 0x0020,
	CS_CLASSDC                     = 0x0040,
	CS_PARENTDC                    = 0x0080,
	DISABLE_CLOSE_WINDOW           = 0x0200,
	CS_SAVEBITS                    = 0x0800,
	CS_BYTEALIGNCLIENT             = 0x1000,
	CS_BYTEALIGNWINDOW             = 0x2000,
	CS_GLOBALCLASS                 = 0x4000,
	DROPSHADOW_WINDOW              = 0x00020000,

	SS_OWNERDRAW                   = 0x0000000D,


	WS_EX_DLGMODALFRAME            = 0x00000001,
	WS_EX_WINDOWEDGE               = 0x00000100,
	WS_EX_CLIENTEDGE               = 0x00000200,
	WS_EX_RIGHT                    = 0x00001000,
	WS_EX_CONTROLPARENT            = 0x00010000,
	WS_EX_NOACTIVATE               = 0x08000000,
}
Window_Class_Style;

typedef struct {
	Number32           structure_size;
	Window_Class_Style style;
	Number32           (stdcall *window_procedure)(
		Byte* window,
		Windows_Message_Type type,
		Number32* parameters_1,
		Signed_Number32* parameters_2
	);
	Number32           class;
	Number32           window;
	Number16*          instance;
	Icon*              icon;
	Cursor*            cursor;
	Brush*             background;
	Byte*              menu_name;
	Byte*              class_name;
	Icon*              small_icon;
}
Window_Class;

import stdcall Number16 RegisterClassExA (Window_Class* class);
import stdcall Number16 RegisterClassExW (Window_Class* class);
import stdcall Number32 UnregisterClassA (Byte* class_name, Byte* instance);
import stdcall Number32 UnregisterClassW (Number16* class_name, Byte* instance);

typedef enum {
	GCL_CBCLSEXTRA    = -20,
	GCL_CBWNDEXTRA    = -18,
	GCL_HBRBACKGROUND = -10,
	GCL_HCURSOR       = -12,
	GCL_HICON         = -14,
	GCL_HICONSM       = -34,
	GCL_HMODULE       = -16,
	GCL_MENUNAME      = -8,
	GCL_STYLE         = -26,
	GCL_WNDPROC       = -24
}
Class_Index;

import stdcall Number32 SetClassLongA (Byte* window, Class_Index index, Number32 value);
import stdcall Number32 SetClassLongW (Byte* window, Class_Index index, Number32 value);

//https://github.com/AHK-just-me/AHK_Gui_Constants/tree/master/Sources
//https://github.com/forcedotcom/dataloader/blob/master/windows-dependencies/autoit/Include/ButtonConstants.au3
typedef enum {
	WS_OVERLAPPED   = 0x00000000L,
	WS_MAXIMIZEBOX  = 0x00010000L,
	WS_TABSTOP      = 0x00010000L,
	WS_MINIMIZEBOX  = 0x00020000L,
	WS_GROUP        = 0x00020000L,
	WS_SIZEBOX      = 0x00040000L,
	WS_THICKFRAME   = 0x00040000L,
	WS_SYSMENU      = 0x00080000L,
	WS_HSCROLL      = 0x00100000L,
	WS_VSCROLL      = 0x00200000L,
	WS_DLGFRAME     = 0x00400000L,
	WS_BORDER       = 0x00800000L,
	WS_CAPTION      = 0x00C00000L,
	WS_MAXIMIZE     = 0x01000000L,
	WS_CLIPCHILDREN = 0x02000000L,
	WS_CLIPSIBLINGS = 0x04000000L,
	WS_DISABLED     = 0x08000000L,
	WS_VISIBLE      = 0x10000000L,
	WS_MINIMIZE     = 0x20000000L,
	WS_ICONIC       = 0x20000000L,
	WS_CHILD        = 0x40000000L,
	WS_CHILDWINDOW  = 0x40000000L,
	WS_POPUP        = 0x80000000L,

	// Static
	SS_LEFT           = 0x0000,
	SS_CENTER         = 0x0001,
	SS_RIGHT          = 0x0002,
	SS_ICON           = 0x0003,
	SS_BLACKRECT      = 0x0004,
	SS_GRAYRECT       = 0x0005,
	SS_WHITERECT      = 0x0006,
	SS_BLACKFRAME     = 0x0007,
	SS_GRAYFRAME      = 0x0008,
	SS_WHITEFRAME     = 0x0009,
	SS_SIMPLE         = 0x000B,
	SS_LEFTNOWORDWRAP = 0x000C,
	SS_BITMAP         = 0x000E,
	SS_ETCHEDHORZ     = 0x0010,
	SS_ETCHEDVERT     = 0x0011,
	SS_ETCHEDFRAME    = 0x0012,
	SS_NOPREFIX       = 0x0080,
	SS_NOTIFY         = 0x0100,
	SS_CENTERIMAGE    = 0x0200,
	SS_RIGHTJUST      = 0x0400,
	SS_SUNKEN         = 0x1000,

	// Button
	BS_PUSHBUTTON        = 0x0000,
	BS_DEFPUSHBUTTON     = 0x0001,
	BS_CHECKBOX          = 0x0002,
	BS_AUTOCHECKBOX      = 0x0003,
	BS_RADIOBUTTON       = 0x0004,
	BS_3STATE            = 0x0005,
	BS_AUTO3STATE        = 0x0006,
	BS_GROUPBOX          = 0x0007,
	BS_USERBUTTON        = 0x0008,
	BS_AUTORADIOBUTTON   = 0x0009,
	BS_PUSHBOX           = 0x000A,
	BS_OWNERDRAW         = 0x000B,
	BS_SPLITBUTTON       = 0x000C, // >= Vista
	BS_DEFSPLITBUTTON    = 0x000D, // >= Vista
	BS_COMMANDLINK       = 0x000E, // >= Vista
	BS_DEFCOMMANDLINK    = 0x000F, // >= Vista
	BS_RIGHTBUTTON       = 0x0020, // BS_LEFTTEXT
	BS_ICON              = 0x0040,
	BS_BITMAP            = 0x0080,
	BS_LEFT              = 0x0100,
	BS_RIGHT             = 0x0200,
	BS_CENTER            = 0x0300,
	BS_TOP               = 0x0400,
	BS_BOTTOM            = 0x0800,
	BS_VCENTER           = 0x0C00,
	BS_PUSHLIKE          = 0x1000,
	BS_MULTILINE         = 0x2000,
	BS_NOTIFY            = 0x4000,
	BS_FLAT              = 0x8000,

	// Edit text
	ES_LEFT                = 0x0000,
	ES_CENTER              = 0x0001,
	ES_RIGHT               = 0x0002,
	ES_MULTILINE           = 0x0004,
	ES_UPPERCASE           = 0x0008,
	ES_LOWERCASE           = 0x0010,
	ES_PASSWORD            = 0x0020,
	ES_AUTOVSCROLL         = 0x0040,
	ES_AUTOHSCROLL         = 0x0080,
	ES_NOHIDESEL           = 0x0100,
	ES_OEMCONVERT          = 0x0400,
	ES_READONLY            = 0x0800,
	ES_WANTRETURN          = 0x1000,
	ES_NUMBER              = 0x2000,

	// List Box
	LBS_NOTIFY            = 0x0001L,
	LBS_SORT              = 0x0002L,
	LBS_NOREDRAW          = 0x0004L,
	LBS_MULTIPLESEL       = 0x0008L,
	LBS_OWNERDRAWFIXED    = 0x0010L,
	LBS_OWNERDRAWVARIABLE = 0x0020L,
	LBS_HASSTRINGS        = 0x0040L,
	LBS_USETABSTOPS       = 0x0080L,
	LBS_NOINTEGRALHEIGHT  = 0x0100L,
	LBS_MULTICOLUMN       = 0x0200L,
	LBS_WANTKEYBOARDINPUT = 0x0400L,
	LBS_EXTENDEDSEL       = 0x0800L,
	LBS_DISABLENOSCROLL   = 0x1000L,
	LBS_NODATA            = 0x2000L,
	LBS_NOSEL             = 0x4000L,
	LBS_COMBOBOX          = 0x8000L
}
Window_Style;

typedef struct {
	void*           params;
	Byte*           instance;
	Byte*           menu;
	Byte*           parent;
	Signed_Number32 cy;
	Signed_Number32 cx;
	Signed_Number32 y;
	Signed_Number32 x;
	Window_Style    style;
	Byte*           name;
	Byte*           class;
	Number32        ex_style;
}
Create_Window;


import stdcall Byte* CreateWindowA(
	Byte*            class_name,
	Byte*            window_name,
	Window_Style     style,
	Signed_Number32  x,
	Signed_Number32  y,
	Signed_Number32  width,
	Signed_Number32  height,
	Byte*            parent_window,
	Byte*            menu,
	Byte*            instance,
	Number32*        parameters
);
import stdcall Byte* CreateWindowW(
	Byte*            class_name,
	Byte*            window_name,
	Window_Style     style,
	Signed_Number32  x,
	Signed_Number32  y,
	Signed_Number32  width,
	Signed_Number32  height,
	Byte*            parent_window,
	Byte*            menu,
	Byte*            instance,
	Number32*        parameters
);
import stdcall Byte* CreateWindowExA(
	Number32         extended_style,
	Byte*            class_name,
	Byte*            window_name,
	Number32         style, //Window_Style
	Signed_Number32  x,
	Signed_Number32  y,
	Signed_Number32  width,
	Signed_Number32  height,
	Byte*            parent_window,
	Byte*            menu,
	Byte*            instance,
	Number32*        parameters
);
import stdcall Byte* CreateWindowExW(
	Number32         extended_style,
	Number16*        class_name,
	Number16*        window_name,
	Window_Style     style,
	Signed_Number32  x,
	Signed_Number32  y,
	Signed_Number32  width,
	Signed_Number32  height,
	Byte*            parent_window,
	Byte*            menu,
	Byte*            instance,
	Number32*        parameters
);
import stdcall Byte* GetDesktopWindow();
import stdcall Number32 DestroyWindow(Byte* window);


typedef enum {
	HIDE_WINDOW                     = 0,
	SHOW_NORMAL_WINDOW              = 1,
	SHOW_MINIMIZED_WINDOW           = 2,
	SHOW_MAXIMIZED_WINDOW           = 3,
	SHOW_NO_ACTIVE_WINDOW           = 4,
	SHOW_WINDOW                     = 5,
	MINIMIZE_WINDOW                 = 6,
	SHOW_MINIMIZED_NO_ACTIVE_WINDOW = 7,
	SHOW_NO_ACTIVATED_WINDOW        = 8,
	RESTORE_WINDOW                  = 9,
	SHOW_DEFAULT_WINDOW             = 10,
	FORCE_MINIMIZE_WINDOW           = 11
}
Show_Window_Type;

typedef enum {
	GWL_WNDPROC    = -4,
	GWL_HINSTANCE  = -6,
	GWL_HWNDPARENT = -8,
	GWL_ID         = -12,
	GWL_STYLE      = -16,
	GWL_EXSTYLE    = -20,
	GWL_USERDATA   = -21
}
Window_Field_Index;

import stdcall Number32 ShowWindow       (Byte* window, Show_Window_Type type);
import stdcall Number32 UpdateWindow     (Byte* window);

typedef enum {
	RDW_INVALIDATE      = 1,
	RDW_INTERNALPAINT   = 2,
	RDW_ERASE           = 4,
	RDW_VALIDATE        = 8,
	RDW_NOINTERNALPAINT = 16,
	RDW_NOERASE         = 32,
	RDW_NOCHILDREN      = 64,
	RDW_ALLCHILDREN     = 128,
	RDW_UPDATENOW       = 256,
	RDW_ERASENOW        = 512,
	RDW_FRAME           = 1024,
	RDW_NOFRAME         = 2048
}
Redraw_Window_Flag;

typedef enum {
	SB_HORZ = 0,
	SB_VERT = 1,
	SB_CTL  = 2
}
Scroll_Bar_Type;

typedef enum {
	SB_LINEUP        = 0,
	SB_LINELEFT      = 0,
	SB_LINEDOWN      = 1,
	SB_LINERIGHT     = 1,
	SB_PAGEUP        = 2,
	SB_PAGELEFT      = 2,
	SB_PAGEDOWN      = 3,
	SB_PAGERIGHT     = 3,
	SB_THUMBPOSITION = 4,
	SB_THUMBTRACK    = 5,
	SB_TOP           = 6,
	SB_LEFT          = 6,
	SB_BOTTOM        = 7,
	SB_RIGHT         = 7,
	SB_ENDSCROLL     = 8
}
Scroll_Message_Type;

typedef enum {
	GET_FIRST_WINDOW = 0,
	GET_LAST_WINDOW = 1,
	GET_NEXT_WINDOW = 2,
	GET_PREV_WINDOW = 3,
	GET_OWNER_WINDOW = 4,
	GET_CHILD_WINDOW = 5,
	GET_ENABLED_POPUP_WINDOW = 6
}
Get_Window_Type;

typedef enum {
	HWND_TOPMOST = -1,
	HWND_NOTOPMOST = -2,
	HWND_TOP = 0,
	HWND_BOTTOM = 1,
}
SetWindowPos_After;

typedef enum {
	SWP_NOSIZE = 0x0001,
	SWP_NOMOVE = 0x0002,
	SWP_NOZORDER = 0x0004,
	SWP_NOREDRAW = 0x0008,
	SWP_NOACTIVATE = 0x0010,
	SWP_DRAWFRAME = 0x0020,
	SWP_SHOWWINDOW = 0x0040,
	SWP_HIDEWINDOW = 0x0080,
	SWP_NOCOPYBITS = 0x0100,
	SWP_NOREPOSITION = 0x0200,
	SWP_NOSENDCHANGING = 0x0400,
	SWP_DEFERERASE = 0x2000,
	SWP_ASYNCWINDOWPOS = 0x4000
}
SetWindowPos_Flags;

import stdcall Number32 RedrawWindow     (Byte* window, Windows_Rectangle* region, Byte* update_region, Number32 flags);
import stdcall Boolean  MoveWindow       (Byte* window, Signed_Number32 x, Signed_Number32 y, Signed_Number32 width, Signed_Number32 height, Boolean repaint);
import stdcall Boolean  SetWindowPos     (Byte* window, Byte* after, Signed_Number32 x, Signed_Number32 y, Signed_Number32 width, Signed_Number32 height, Number32 flags);
import stdcall Number32 GetWindowRect    (Byte* window, Windows_Rectangle* rectangle);
import stdcall Number32 GetClientRect    (Byte* window, Windows_Rectangle* rectangle);
import stdcall Boolean  SetWindowTextW   (Byte* window, Number16* text);
import stdcall Boolean  ScrollWindow     (Byte* window, Signed_Number32 x_amount, Signed_Number32 y_amount, Windows_Rectangle* rectangle, Windows_Rectangle* clip_rectangle);
import stdcall Boolean  ShowScrollBar    (Byte* window, Scroll_Bar_Type scrollbar_index, Boolean show);
import stdcall Number32 SetScrollPos     (Byte* window, Scroll_Bar_Type scrollbar_index, Signed_Number32 position, Boolean redraw);
import stdcall Byte*    SetFocus         (Byte* window);
import stdcall Byte*    GetParent        (Byte* window);
import stdcall Byte*    GetWindow        (Byte* window, Number32 type);
import stdcall Byte*    GetDC            (Byte* window);
import stdcall Number32 SetWindowLongA   (Byte* window, Window_Field_Index field_index, Number32 value);
import stdcall Number32 SetWindowLongW   (Byte* window, Window_Field_Index field_index, Number32 value);
import stdcall Number32 GetWindowLongA   (Byte* window, Window_Field_Index field_index);
import stdcall Number32 GetWindowLongW   (Byte* window, Window_Field_Index field_index);
import stdcall Number32 DefWindowProcA   (Byte* window, Windows_Message_Type type, Number16* parameter1, Number32* parameter2);
import stdcall Number32 DefWindowProcW   (Byte* window, Windows_Message_Type type, Number16* parameter1, Number32* parameter2);
import stdcall Number32 DefDlgProcW      (Byte* window, Windows_Message_Type type, Number16* parameter1, Number32* parameter2);


typedef enum {
	TME_CANCEL = 0x80000000,
	TME_HOVER = 0x00000001,
	TME_LEAVE = 0x00000002,
	TME_NONCLIENT = 0x00000010,
	TME_QUERY = 0x40000000
}
Track_Mouse_Event_Flag;

typedef struct {
	Number32 size;
	Number32 flags;
	Byte*    window;
	Number32 hover_time;
	Number32 pad; //!!!
}
Track_Mouse_Event_Params;

import stdcall Boolean TrackMouseEvent(Track_Mouse_Event_Params* params);


typedef enum {
	CTLCOLOR_MSGBOX         = 0,
	CTLCOLOR_EDIT           = 1,
	CTLCOLOR_LISTBOX        = 2,
	CTLCOLOR_BTN            = 3,
	CTLCOLOR_DLG            = 4,
	CTLCOLOR_SCROLLBAR      = 5,
	CTLCOLOR_STATIC         = 6,
	CTLCOLOR_MAX            = 7,

	COLOR_SCROLLBAR           = 0,
	COLOR_BACKGROUND          = 1,
	COLOR_ACTIVECAPTION       = 2,
	COLOR_INACTIVECAPTION     = 3,
	COLOR_MENU                = 4,
	COLOR_WINDOW              = 5,
	COLOR_WINDOWFRAME         = 6,
	COLOR_MENUTEXT            = 7,
	COLOR_WINDOWTEXT          = 8,
	COLOR_CAPTIONTEXT         = 9,
	COLOR_ACTIVEBORDER        = 10,
	COLOR_INACTIVEBORDER      = 11,
	COLOR_APPWORKSPACE        = 12,
	COLOR_HIGHLIGHT           = 13,
	COLOR_HIGHLIGHTTEXT       = 14,
	COLOR_BTNFACE             = 15,
	COLOR_BTNSHADOW           = 16,
	COLOR_GRAYTEXT            = 17,
	COLOR_BTNTEXT             = 18,
	COLOR_INACTIVECAPTIONTEXT = 19,
	COLOR_BTNHIGHLIGHT        = 20
}
Windows_Color;

import stdcall Byte*    BeginPaint       (Byte* window, Windows_Paint* paint);
import stdcall Number32 FillRect         (Byte* device, Windows_Rectangle* rectangle, Byte* brush);

typedef enum {
	DT_TOP                  = 0,
	DT_LEFT                 = 0,
	DT_CENTER               = 1,
	DT_RIGHT                = 2,
	DT_VCENTER              = 4,
	DT_BOTTOM               = 8,
	DT_WORDBREAK            = 0x10,
	DT_SINGLELINE           = 0x20,
	DT_EXPANDTABS           = 0x40,
	DT_TABSTOP              = 0x80,
	DT_NOCLIP               = 0x100,
	DT_EXTERNALLEADING      = 0x200,
	DT_CALCRECT             = 0x400,
	DT_NOPREFIX             = 0x800,
	DT_INTERNAL             = 0x1000,
	DT_EDITCONTROL          = 0x2000,
	DT_PATH_ELLIPSIS        = 0x4000,
	DT_END_ELLIPSIS         = 0x8000,
	DT_MODIFYSTRING         = 0x10000,
	DT_RTLREADING           = 0x20000,
	DT_WORDELLIPSIS         = 0x40000,
	DT_NOFULLWIDTHCHARBREAK = 0x80000,
	DT_HIDEPREFIX           = 0x100000,
	DT_PREFIXONLY           = 0x200000
}
Draw_Text_Format;

import stdcall Number32 DrawTextW        (Byte* device, Number16* text, Number32 number_of_characters, Windows_Rectangle* region, Number32 format);
import stdcall Number32 DrawTextExW      (Byte* device, Number16* text, Number32 number_of_characters, Windows_Rectangle* region, Number32 format, struct ext_params* params);
import stdcall Number32 EndPaint         (Byte* window, Windows_Paint* paint);

import stdcall Icon*    LoadIconA        (Byte* instance, Byte* icon_name);
import stdcall Cursor*  LoadCursorA      (Byte* instance, Byte* cursor_name);

import stdcall Number32 InvalidateRect   (Byte* window, Windows_Rectangle* rectangle, Number32 clean);

import stdcall Number32 GetAsyncKeyState (Number32 key);
import stdcall Number32 GetCursorPos     (Windows_Point* coords);


//======== Display ====================

//https://docs.microsoft.com/en-us/windows/desktop/api/wingdi/ns-wingdi-_display_devicea
typedef struct {
	Number32 structure_size;
	Byte     device_name[32];
	Byte     device_context_name[128];
	Number32 state;
	Byte     device_id[128];
	Byte     device_key[128];
}
Display;

//https://vxlab.info/wasm/article.php-article=Multimon.htm
typedef enum {
	DISPLAY_IS_ATTACHED_TO_DESKTOP  = 0x00000001,
	DISPLAY_IS_MULTI_DRIVER         = 0x00000002,
	DISPLAY_IS_PRIMARY_DEVICE       = 0x00000004,
	DISPLAY_IS_MIRRORING_DRIVER     = 0x00000008,
	DISPLAY_IS_VGA_COMPATIBLE       = 0x00000010,
}
Display_States;

//https://docs.microsoft.com/en-us/windows/desktop/api/wingdi/ns-wingdi-_devicemodea
typedef struct {
	Byte     device_name[32];
	Number32 version;
	Number16 structure_size;
	Number16 private_structure_size;
	Number32 fields;

	union {
		struct {
			Number16 orientaion;
			Number16 paper_size;
			Number16 paper_length;
			Number16 paper_width;
			Number16 scale;
			Number16 copies;
			Number16 default_score;
			Number16 quality;
		}
		printer;

		struct {
			Number32 x;
			Number32 y;
		}
		position;

		struct {
			struct {
				Number32 x;
				Number32 y;
			}
			position;

			Number32 orientation;
			Number32 output;
		}
		display;
	};

	Number16 color;
	Number16 duplex;
	Number16 y_resolution;
	Number16 option;
	Number16 collate;
	Byte     form_name[32];
	Number16 pixels_per_inch;
	Number32 bits_per_pixel;
	Number32 width;
	Number32 height;

	union {
		Number32 display_flags;
		Number32 NUP;
	};

	Number32 frequency;
	Number32 ICM_method;
	Number32 ICM_intent;
	Number32 media_type;
	Number32 dither_type;
	Number32 reserved1;
	Number32 reserved2;
	Number32 panning_width;
	Number32 panning_height;
}
Dispaly_Mode;

//http://www.asmcommunity.net/forums/topic/?id=2281
typedef enum {
	DM_PELSWIDTH        = 0x00080000,
	DM_PELSHEIGHT       = 0x00100000,
	DM_DISPLAYFREQUENCY = 0x00400000
}
Display_Mode_Flags;

typedef enum {
	ENUM_CURRENT_SETTINGS  = -1,
	ENUM_REGISTRY_SETTINGS = -2
}
Enum_Display_Settings_Flags;

//https://gist.github.com/curzona/92cdeb66e850846c1e69f29b63f34691
typedef enum {
	CDS_UPDATEREGISTRY       = 0x00000001,
	CDS_RESET                = 0x40000000
}
Change_Display_Settings_Flags;

import stdcall Number32 EnumDisplayDevicesA    (Byte* name, Number32 display_number, Display* display, Number32 flags);
import stdcall Number32 EnumDisplayMonitors    (Byte* hdc, Windows_Rectangle* clip, Number32 (stdcall *enum_monitor)(Byte* monitor, Byte* hdc, Windows_Rectangle* rectangle, Byte* parameter), Byte* parameter);
import stdcall Number32 EnumDisplaySettingsA   (Byte* name, Number32 mode, Dispaly_Mode* display_mode);
import stdcall Number32 ChangeDisplaySettingsA (Dispaly_Mode* display_mode, Number32 flags);

import stdcall Number32 SelectObject(Byte* device, Byte* object);

import stdcall Number32 ReleaseDC(Byte* window, Byte* context);

typedef enum {
	IMAGE_BITMAP = 0,
	IMAGE_ICON   = 1,
	IMAGE_CURSOR = 2,
}
Image_Type;

typedef enum {
	LR_DEFAULTCOLOR     = 0x0,
	LR_MONOCHROME       = 0x1,
	LR_COLOR            = 0x2,
	LR_COPYRETURNORG    = 0x4,
	LR_COPYDELETEORG    = 0x8,
	LR_LOADFROMFILE     = 0x10,
	LR_LOADTRANSPARENT  = 0x20,
	LR_DEFAULTSIZE      = 0x40,
	LR_VGACOLOR         = 0x80,
	LR_LOADMAP3DCOLORS  = 0x1000,
	LR_CREATEDIBSECTION = 0x2000,
	LR_COPYFROMRESOURCE = 0x4000,
	LR_SHARED           = 0x8000,
	
}
Load_Image_Option;

import stdcall Byte* LoadImageW(Byte* instance, Number16* name, Number32 type, Signed_Number32 x, Signed_Number32 y, Number32 options);


import stdcall Number32 WaitForInputIdle(Byte* process, Number32 milliseconds);


#endif //SYSTEM_WINDOWS_USER32_INCLUDED