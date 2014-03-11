/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

#include "colors.h"
#include "font.h"

#include "selfrestart.c"

static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "feh",      NULL,       NULL,       0,            True,        -1 },
	{ "MPlayer",  NULL,       NULL,       0,            True,        -1 },
	{ "Gsimplecal",NULL,      NULL,      ~0,            True,        -1 },
	{ "esmska-Main",NULL,     NULL,       0,            True,        -1 },
	{ "Qjackctl", NULL,       NULL,       0,            True,        -1 },
	{ "Qsynth",   NULL,       NULL,       0,            True,        -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },    /* first entry is default */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod1Mask
#define WINKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                     KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ WINKEY,                     KEY,      tag,            {.ui = 1 << TAG} }, \
	{ WINKEY|ShiftMask,           KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[]           = { "dmenu_run", "-b", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]            = { "urxvt", NULL };
static const char *calcmd[]             = { "gsimplecal", NULL };
static const char *lockcmd[]            = { "xscreensaver-command", "-lock", NULL };
static const char *browsercmd[]         = { "firefox", NULL };

static const char *mocnextcmd[]         = { "mocp", "-f", NULL };
static const char *mocprevcmd[]         = { "mocp", "-r", NULL };
static const char *mocplaypausecmd[]    = { "mocp", "-G", NULL };

static const char *vol0_upcmd[]         = { "mixer-set.sh", "0", "up", "5", NULL };
static const char *vol0_downcmd[]       = { "mixer-set.sh", "0", "down", "5", NULL };
static const char *vol0_togglecmd[]     = { "mixer-set.sh", "0", "toggle", NULL };

static const char *bright_up_cmd[]      = { "xbacklight", "-time", "0", "-inc", "10", NULL };
static const char *bright_down_cmd[]    = { "xbacklight", "-time", "0", "-dec", "10", NULL };

static const char *switchdisplay1_cmd[] = { "switchdisplay.sh", "standalone", NULL };
static const char *switchdisplay2_cmd[] = { "switchdisplay.sh", "lcdtop", NULL };

static Key keys[] = {
	/* modifier                     key         function        argument */
	{ MODKEY|ControlMask,           XK_x,       spawn,          {.v = dmenucmd } },
	{ MODKEY|ControlMask,           XK_Return,  spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_l,       spawn,          {.v = lockcmd } },
	{ MODKEY|ControlMask,           XK_d,       spawn,          {.v = browsercmd } },
	{ 0,               XF86XK_AudioPlay,        spawn,          {.v = mocplaypausecmd } },
	{ 0,               XF86XK_AudioPrev,        spawn,          {.v = mocprevcmd } },
	{ 0,               XF86XK_AudioNext,        spawn,          {.v = mocnextcmd } },
	{ 0,               XF86XK_AudioMute,        spawn,          {.v = vol0_togglecmd } },
	{ 0,               XF86XK_AudioLowerVolume, spawn,          {.v = vol0_downcmd } },
	{ 0,               XF86XK_AudioRaiseVolume, spawn,          {.v = vol0_upcmd } },
	{ 0,               XF86XK_WebCam,           spawn,          {.v = switchdisplay1_cmd } },
	{ 0,               XF86XK_Display,          spawn,          {.v = switchdisplay2_cmd } },
	{ 0,              XF86XK_MonBrightnessUp,   spawn,          {.v = bright_up_cmd } },
	{ 0,              XF86XK_MonBrightnessDown, spawn,          {.v = bright_down_cmd } },
	{ WINKEY|ControlMask,           XK_b,       togglebar,      {0} },
	{ MODKEY,                       XK_Tab,     focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,     focusstack,     {.i = -1 } },
	{ WINKEY|ShiftMask,             XK_h,       incnmaster,     {.i = +1 } },
	{ WINKEY|ShiftMask,             XK_l,       incnmaster,     {.i = -1 } },
	{ WINKEY,                       XK_h,       setmfact,       {.f = -0.05} },
	{ WINKEY,                       XK_l,       setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,  zoom,           {0} },
	{ MODKEY,                       XK_KP_Enter,zoom,           {0} },
	{ MODKEY,                       XK_Escape,  killclient,     {0} },
	{ WINKEY|ControlMask,           XK_m,       setlayout,      {.v = &layouts[0]} },
	{ WINKEY|ControlMask,           XK_d,       setlayout,      {.v = &layouts[1]} },
	{ WINKEY|ControlMask,           XK_f,       setlayout,      {.v = &layouts[2]} },
	{ WINKEY|ControlMask,           XK_space,   setlayout,      {0} },
	{ WINKEY,                       XK_f,       togglefloating, {0} },
	{ MODKEY,                       XK_comma,   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,  focusmon,       {.i = +1 } },
	{ WINKEY,                       XK_comma,   tagmon,         {.i = -1 } },
	{ WINKEY,                       XK_period,  tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_F1,                      0)
	TAGKEYS(                        XK_F2,                      1)
	TAGKEYS(                        XK_F3,                      2)
	TAGKEYS(                        XK_F4,                      3)
	TAGKEYS(                        XK_F5,                      4)
	TAGKEYS(                        XK_F6,                      5)
	TAGKEYS(                        XK_F7,                      6)
	TAGKEYS(                        XK_F8,                      7)
	TAGKEYS(                        XK_F9,                      8)
	{ WINKEY|ControlMask,           XK_r,       restart,        {0} },
	{ WINKEY|ControlMask,           XK_q,       quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = calcmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = mocplaypausecmd } },
	{ ClkStatusText,        0,              Button4,        spawn,          {.v = vol0_upcmd } },
	{ ClkStatusText,        0,              Button5,        spawn,          {.v = vol0_downcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

