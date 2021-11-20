/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx           = 2;    /* border pixel of windows */
static const unsigned int gappx              = 5;    /* gaps between windows */
static const unsigned int corner_radius      = 8;    /* rounded corner radius */
static const unsigned int round_non_floating = 0;
static const unsigned int snap               = 32;   /* snap pixel */
static const int swallowfloating             = 0;    /* 1 means swallow floating windows by default */
static const int showbar                     = 1;    /* 0 means no bar */
static const int topbar                      = 1;    /* 0 means bottom bar */
static const int singlegap                   = 0;    /* 1 means gap with one window open*/
static const int horizpadbar                 = 6;    /* horizontal padding for statusbar */
static const int vertpadbar                  = 0;    /* vertical padding for statusbar */
static const int vertpad                     = 0;    /* vertical padding of bar */
static const int sidepad                     = 0;    /* horizontal padding of bar */
static const char *fonts[]                   = { "monospace:size=8", "JoyPixels:pixelsize=10:antialias=true:autohint=true" };
static const char dmenufont[]                = "monospace:size=8 JoyPixels:pixelsize=10:antialias=true:autohint=true";
static const char normbgcolor[]              = "#1d1f21";
static const char normfgcolor[]              = "#c5c8c6";
static const char normbordercolor[]          = "#1d1f21";
static const char selfgcolor[]               = "#cc6666";
static const char selbgcolor[]               = "#1d1f21";
static const char selbordercolor[]           = "#cc6666";

static const char dmenuselfgcolor[]          = "#1d1f21";
static const char dmenuselbgcolor[]          = "#cc6666";
static const char dmenunormfghcolor[]        = "#f0c674";
static const char dmenunormbghcolor[]        = "#1d1f21";
static const char dmenuselfghcolor[]         = "#f0c674";
static const char dmenuselbghcolor[]         = "#cc6666";

static const char dmenuheight[]              = "18";

static const unsigned int baralpha           = 0xd8;
static const unsigned int borderalpha        = OPAQUE;

static const char *colors[][3]               = {
	/*               fg           bg           border      */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor   },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor    },
};
static const unsigned int alphas[][3] = {
	/*                  fg          bg          border      */
	[SchemeNorm] = {    OPAQUE,     baralpha,   borderalpha },
	[SchemeSel]  = {    OPAQUE,     baralpha,   borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *  WM_CLASS(STRING) = instance, class
	 *  WM_NAME(STRING) = title
	 */
	/* class            instance    title           tags mask   iscentered  isfloating  isterminal  noswallow   width       height  monitor */
	{ "floatw",         NULL,       NULL,           0,          1,          1,          0,          -1,         1280,       720,    -1 },
	{ "Nitrogen",       NULL,       NULL,           0,          1,          1,          0,          -1,         1280,       720,    -1 },
	{ "Lxappearance",   NULL,       NULL,           0,          1,          1,          0,          -1,         1280,       720,    -1 },
	{ "Steam",          NULL,       "Steam - News", 0,          1,          1,          0,          -1,         1280,       720,    -1 },
	{ "Steam",          NULL,       "Friends List", 0,          1,          1,          0,          -1,         1280,       720,    -1 },
	{ "firefox",        NULL,       "Library",      0,          1,          1,          0,          -1,         1280,       720,    -1 },
	{ "nextcloud",      NULL,       NULL,           1 << 8,     1,          1,          0,          -1,         0,          0,      -1 },
	{ "st",             NULL,       NULL,           0,          0,          0,          1,          -1,         0,          0,      -1 },
	{ NULL,             NULL,       "Event Tester", 0,          0,          1,          0,           1,         0,          0,      -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */


#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define DMODKEY (MODKEY|ShiftMask)
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,       {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview, {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,        {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,  {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define DMENU_OPTS "-m", dmenumon, "-fn", dmenufont, "-h", dmenuheight, "-nb", \
                   normbgcolor, "-nf", normfgcolor, "-sb", dmenuselbgcolor,    \
                   "-sf", dmenuselfgcolor, "-nbh", dmenunormbghcolor, "-nfh",  \
                   dmenunormfghcolor, "-sbh", dmenuselbghcolor, "-sfh",        \
                   dmenuselfghcolor

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]       = { "dmenu_run", "-i" , DMENU_OPTS, NULL };
static const char *termcmd[]        = { "kitty", NULL };

static const char *volup[]          = { "pactl", "--", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *voldown[]        = { "pactl", "--", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *voltoggle[]      = { "pactl", "--", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };

static const char *sptplay[]         = { "spt", "playback", "--toggle", NULL };
static const char *sptprev[]         = { "spt", "playback", "--previous", NULL };
static const char *sptnext[]         = { "spt", "playback", "--next", NULL };

static const char *exitdwm[]        = { "rdq", "Are you sure you want to exit dwm?", "dwmc quit", DMENU_OPTS, NULL };
static const char *shutdowncmd[]    = { "rdq", "Are you sure you want to shutdown?", "shutdown -h now", DMENU_OPTS, NULL };
static const char *rebootcmd[]      = { "rdq", "Are you sure you want to reboot?", "reboot", DMENU_OPTS, NULL };
static const char *suspend[]        = { "rdq", "Are you sure you want to suspend?", "systemctl suspend", DMENU_OPTS, NULL };
static const char *lock[]           = { "slock", NULL };

static const char *clipmenu[]       = { "clipmenu", DMENU_OPTS, NULL };
static const char *newsboat[]       = { "st", "-c", "floatw", "-e", "newsboat", NULL };
static const char *neomutt[]        = { "st", "-c", "floatw", "-e", "neomutt", NULL };
static const char *pulse[]          = { "st", "-c", "floatw", "-e", "pulsemixer", NULL };
static const char *calculator[]     = { "st", "-c", "floatw", "-e", "R", "-q", "--save", NULL };
static const char *screenshot[]     = { "flameshot", "gui", NULL };

static const char *dmenuunicode[]   = { "dmenuunicode", "-i", DMENU_OPTS, NULL };

static Key keys[] = {
	/* modifier             key                     function            argument */
	{ MODKEY,               XK_d,                   spawn,              {.v = dmenucmd } },
	{ MODKEY,               XK_Return,              spawn,              {.v = termcmd } },
	{ MODKEY,               XK_b,                   togglebar,          {0} },
	{ MODKEY|ShiftMask,     XK_j,                   rotatestack,        {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_k,                   rotatestack,        {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_Down,                rotatestack,        {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_Up,                  rotatestack,        {.i = -1 } },
	{ MODKEY,               XK_j,                   focusstack,         {.i = +1 } },
	{ MODKEY,               XK_k,                   focusstack,         {.i = -1 } },
	{ MODKEY,               XK_Down,                focusstack,         {.i = +1 } },
	{ MODKEY,               XK_Up,                  focusstack,         {.i = -1 } },
	{ MODKEY,               XK_i,                   incnmaster,         {.i = +1 } },
	{ MODKEY,               XK_o,                   incnmaster,         {.i = -1 } },
	{ MODKEY,               XK_h,                   setmfact,           {.f = -0.05} },
	{ MODKEY,               XK_l,                   setmfact,           {.f = +0.05} },
	{ MODKEY,               XK_Left,                setmfact,           {.f = -0.05} },
	{ MODKEY,               XK_Right,               setmfact,           {.f = +0.05} },
	{ MODKEY|ShiftMask,     XK_Return,              zoom,               {0} },
	{ MODKEY,               XK_Tab,                 view,               {0} },
	{ MODKEY|ShiftMask,     XK_q,                   killclient,         {0} },
	{ MODKEY|ControlMask,   XK_comma,               cyclelayout,        {.i = -1 } },
	{ MODKEY|ControlMask,   XK_period,              cyclelayout,        {.i = +1 } },
	{ MODKEY,               XK_f,                   togglefullscreen,   {0} },
	{ MODKEY,               XK_c,                   setcentered,        {0} },
	{ MODKEY,               XK_space,               setlayout,          {0} },
	{ MODKEY|ShiftMask,     XK_space,               togglefloating,     {0} },
	{ MODKEY,               XK_0,                   view,               {.ui = ~0 } },
	{ MODKEY|ShiftMask,     XK_0,                   tag,                {.ui = ~0 } },
	{ MODKEY,               XK_comma,               focusmon,           {.i = -1 } },
	{ MODKEY,               XK_period,              focusmon,           {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_comma,               tagmon,             {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_period,              tagmon,             {.i = +1 } },
	{ MODKEY,               XK_minus,               setgaps,            {.i = -1 } },
	{ MODKEY,               XK_plus,                setgaps,            {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_plus,                setgaps,            {.i = 0  } },
	TAGKEYS(                XK_1,                                       0)
	TAGKEYS(                XK_2,                                       1)
	TAGKEYS(                XK_3,                                       2)
	TAGKEYS(                XK_4,                                       3)
	TAGKEYS(                XK_5,                                       4)
	TAGKEYS(                XK_6,                                       5)
	TAGKEYS(                XK_7,                                       6)
	TAGKEYS(                XK_8,                                       7)
	TAGKEYS(                XK_9,                                       8)

	{ DMODKEY,              XK_e,                   spawn,              {.v = exitdwm } },
	{ DMODKEY,              XK_x,                   spawn,              {.v = shutdowncmd } },
	{ DMODKEY,              XK_y,                   spawn,              {.v = suspend } },
	{ MODKEY,               XK_y,                   spawn,              {.v = lock} },
	{ DMODKEY,              XK_Escape,              spawn,              {.v = rebootcmd } },

	{ 0,                    XF86XK_AudioRaiseVolume,spawn,              {.v = volup } },
	{ 0,                    XF86XK_AudioLowerVolume,spawn,              {.v = voldown } },
	{ 0,                    XF86XK_AudioMute,       spawn,              {.v = voltoggle } },

	{ 0,                    XF86XK_AudioPlay,       spawn,              {.v = sptplay } },
	{ 0,                    XF86XK_AudioPause,      spawn,              {.v = sptplay } },
	{ 0,                    XF86XK_AudioStop,       spawn,              {.v = sptplay } },
	{ 0,                    XF86XK_AudioPrev,       spawn,              {.v = sptprev } },
	{ 0,                    XF86XK_AudioNext,       spawn,              {.v = sptnext } },

	{ MODKEY,               XK_v,                   spawn,              {.v = clipmenu } },

	{ MODKEY,               XK_n,                   spawn,              {.v = newsboat } },
	{ MODKEY,               XK_m,                   spawn,              {.v = neomutt } },
	{ MODKEY|ShiftMask,     XK_m,                   spawn,              {.v = pulse } },
	{ MODKEY,               XK_g,                   spawn,              {.v = calculator } },

	{ MODKEY,               XK_Print,               spawn,              {.v = screenshot} },
	{ MODKEY|ShiftMask,     XK_acute,               spawn,              {.v = dmenuunicode} }
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click            event mask  button      function        argument */
	{ ClkLtSymbol,      0,          Button1,    setlayout,      {0} },
	{ ClkLtSymbol,      0,          Button3,    setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,      0,          Button2,    zoom,           {0} },
	{ ClkStatusText,    0,          Button2,    spawn,          {.v = termcmd } },
	{ ClkClientWin,     MODKEY,     Button1,    movemouse,      {0} },
	{ ClkClientWin,     MODKEY,     Button2,    togglefloating, {0} },
	{ ClkClientWin,     MODKEY,     Button3,    resizemouse,    {0} },
	{ ClkTagBar,        0,          Button1,    view,           {0} },
	{ ClkTagBar,        0,          Button3,    toggleview,     {0} },
	{ ClkTagBar,        MODKEY,     Button1,    tag,            {0} },
	{ ClkTagBar,        MODKEY,     Button3,    toggletag,      {0} },
};

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "incnmaster",     incnmaster },
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
};
