/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-normal-*-12-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#022C00";
static const char normbgcolor[]     = "#05120B";
static const char normfgcolor[]     = "#0CA005";
static const char selbordercolor[]  = "#0CA005";
static const char selbgcolor[]      = "#0CA005";
static const char selfgcolor[]      = "#05120B";
static const char* colors[NumColors][ColLast] = {
	// border          foreground   background
	{ normbordercolor, normfgcolor, normbgcolor },  // normal
	{ selbordercolor,  selfgcolor,  selbgcolor  },  // selected

	{ normbordercolor, selbgcolor,  selfgcolor  },  // warning
	{ normbordercolor, "#ffffff",   "#ff0000"   },  // error
	{ normbordercolor, "#7598b2",   normbgcolor },  // delim

    { normbordercolor, "#b10000",   normbgcolor },  // hot
	{ normbordercolor, "#b15c00",   normbgcolor },  // medium
	{ normbordercolor, "#6cb100",   normbgcolor },  // cool
};
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "feh",      NULL,       NULL,       0,            True,        -1 },
	{ "MPlayer",  NULL,       NULL,       0,            True,        -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },
	{ "[]=",      tile },    /* first entry is default */
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
static const char *dmenucmd[]           = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]            = { "urxvtc", NULL };
static const char *lockcmd[]            = { "xlock", NULL };
static const char *browsercmd2[]        = { "jumanji", NULL };
static const char *browsercmd[]         = { "firefox", NULL };
static const char *smscmd[]             = { "esmska", NULL };
static const char *mocnextcmd[]         = { "mocp", "-f", NULL };
static const char *mocprevcmd[]         = { "mocp", "-r", NULL };
static const char *mocplaypausecmd[]    = { "mocp", "-G", NULL };
//static const char *quitcmd[] = { "killall", "xinit", NULL };



static Key keys[] = {
	/* modifier                     key         function        argument */
	{ MODKEY|ControlMask,           XK_x,       spawn,          {.v = dmenucmd } },
	{ MODKEY|ControlMask,           XK_Return,  spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_l,       spawn,          {.v = lockcmd } },
	{ MODKEY|ControlMask,           XK_d,       spawn,          {.v = browsercmd } },
	{ MODKEY|ControlMask,           XK_f,       spawn,          {.v = browsercmd2 } },
	{ MODKEY|ControlMask,           XK_e,       spawn,          {.v = smscmd } },
	{ WINKEY,                       XK_F7,      spawn,          {.v = mocplaypausecmd } },
	{ WINKEY,                       XK_F8,      spawn,          {.v = mocprevcmd } },
	{ WINKEY,                       XK_F9,      spawn,          {.v = mocnextcmd } },
	{ WINKEY|ControlMask,           XK_b,       togglebar,      {0} },
	{ MODKEY,                       XK_Tab,     focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,     focusstack,     {.i = -1 } },
	{ WINKEY|ShiftMask,             XK_h,       incnmaster,     {.i = +1 } },
	{ WINKEY|ShiftMask,             XK_l,       incnmaster,     {.i = -1 } },
	{ WINKEY,                       XK_h,       setmfact,       {.f = -0.05} },
	{ WINKEY,                       XK_l,       setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,  zoom,           {0} },
	{ MODKEY,                       XK_Escape,  killclient,     {0} },
	{ WINKEY|ControlMask,           XK_m,       setlayout,      {.v = &layouts[0]} },
	{ WINKEY|ControlMask,           XK_d,       setlayout,      {.v = &layouts[1]} },
	{ WINKEY|ControlMask,           XK_f,       setlayout,      {.v = &layouts[2]} },
	{ WINKEY|ControlMask,           XK_space,   setlayout,      {0} },
	{ WINKEY,                       XK_space,   togglefloating, {0} },
	{ MODKEY,                       XK_comma,   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,  tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_F1,                      0)
	TAGKEYS(                        XK_F2,                      1)
	TAGKEYS(                        XK_F3,                      2)
	TAGKEYS(                        XK_F4,                      3)
	TAGKEYS(                        XK_F5,                      4)
	TAGKEYS(                        XK_F6,                      5)
	{ MODKEY|ShiftMask,             XK_q,       quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkWinTitle,          0,              Button1,        focusonclick,   {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

