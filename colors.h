#ifndef _COLORS_H
/* appearance */
static const char font[]            = "-*-terminus-medium-r-normal-*-14-*-*-*-*-*-*-*";
/* emacs green */
//static const char normbordercolor[] = "#022C00";
//static const char normbgcolor[]     = "#05120B";
//static const char normfgcolor[]     = "#0CA005";
//static const char selbordercolor[]  = "#0CA005";
//static const char selbgcolor[]      = "#0CA005";
//static const char selfgcolor[]      = "#05120B";

/* murrina red */
static const char normbordercolor[] = "#171717"; /* not active window borders */
static const char normbgcolor[]     = "#171717"; /* not selected tags bg, status bg */
static const char normfgcolor[]     = "#AEAEAE"; /* not selected tags text and status text */
static const char selbordercolor[]  = "#AEAEAE"; /* active window border */
static const char selbgcolor[]      = "#313131"; /* selected tags bg, taskbar bg */
static const char selfgcolor[]      = "#AEAEAE"; /* selected tag text, taskbar text */
static const char urgbordercolor[]  = "#A60000";

/* clearlooks shadow */
//static const char normbordercolor[] = "#171717"; /* inactive window borders */
//static const char normbgcolor[]     = "#171717"; /* not selected tags bg, status bg */
//static const char normfgcolor[]     = "#AEAEAE"; /* not selected tags text and status text */
//static const char selbordercolor[]  = "#9A9C54"; /* active window border */
//static const char selbgcolor[]      = "#3C3C3C"; /* selected tags bg, taskbar bg */
//static const char selfgcolor[]      = "#AEAEAE"; /* selected tag text, taskbar text */
//static const char urgbordercolor[]  = "#A60000";


/* murrina lovegray */
//static const char normbordercolor[] = "#EEEEEE"; /* not active window borders */
//static const char normbgcolor[]     = "#EEEEEE"; /* not selected tags bg, status bg */
//static const char normfgcolor[]     = "#191919"; /* not selected tags text and status text */
//static const char selbordercolor[]  = "#9A9C54"; /* active window border */
//static const char selbgcolor[]      = "#C1C1C1"; /* selected tags bg, taskbar bg */
//static const char selfgcolor[]      = "#191919"; /* selected tag text, taskbar text */
//static const char urgbordercolor[]  = "#A60000";

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

#endif // _COLORS_H
