/* See LICENSE file for copyright and license details. */

#define XF86AudioMute           0x1008ff12
#define XF86AudioLowerVolume    0x1008ff11
#define XF86AudioRaiseVolume    0x1008ff13

/* appearance */
static const unsigned int borderpx           = 2;    /* border pixel of windows */
static const unsigned int gappx              = 7;    /* gaps between windows */
static const unsigned int corner_radius      = 8;    /* rounded corner radius */
static const unsigned int round_non_floating = 0;
static const unsigned int snap               = 32;   /* snap pixel */
static const int showbar                     = 1;    /* 0 means no bar */
static const int topbar                      = 1;    /* 0 means bottom bar */
static const int horizpadbar                 = 6;    /* horizontal padding for statusbar */
static const int vertpadbar                  = 0;    /* vertical padding for statusbar */
static const char *fonts[]                   = { "monospace:size=17" };
static const char dmenufont[]                = "monospace:size=17";
static const char normbgcolor[]              = "#1c1b19";
static const char normfgcolor[]              = "#fce8c3";
static const char normbordercolor[]          = "#1c1b19";
static const char selfgcolor[]               = "#519f50";
static const char selbgcolor[]               = "#1c1b19";
static const char selbordercolor[]           = "#519f50";

static const unsigned int baralpha           = 0xf9;
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
	/* class            instance    title       tags mask   iscentered  isfloating  width       height  monitor */
	{ "floatw",         NULL,       NULL,       0,          1,          1,          2000,       1000,   -1 },
	{ "Nitrogen",       NULL,       NULL,       0,          1,          1,          2000,       1000,   -1 },
	{ "Lxappearance",   NULL,       NULL,       0,          1,          1,          2000,       1000,   -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

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

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]       = { "dmenu_run", "-i" , "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]        = { "st", NULL };
static const char *volup[]          = { "volman", "-i", NULL };
static const char *voldown[]        = { "volman", "-d", NULL };
static const char *voltoggle[]      = { "volman", "-t", NULL };
static const char *exitdwm[]        = { "rdq", "Are you sure you want to exit dwm?", "xsetroot -name fsignal:1", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *shutdowncmd[]    = { "rdq", "Are you sure you want to shutdown?", "shutdown -h now", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *rebootcmd[]      = { "rdq", "Are you sure you want to reboot?", "reboot", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *lock[]           = { "lock", NULL };
static const char *clipmenu[]       = { "clipmenu", NULL };
static const char *nnn[]            = { "st", "-c", "floatw", "-e", "nnn", NULL };
static const char *newsboat[]       = { "st", "-c", "floatw", "-e", "newsboat", NULL };
static const char *neomutt[]        = { "st", "-c", "floatw", "-e", "neomutt", NULL };
static const char *slack[]          = { "st", "-c", "floatw", "-e", "weechat", NULL };
static const char *pulse[]          = { "st", "-c", "floatw", "-e", "pulsemixer", NULL };

static Key keys[] = {
	/* modifier             key                     function    argument */
	{ MODKEY,               XK_d,                   spawn,          {.v = dmenucmd } },
	{ MODKEY,               XK_Return,              spawn,          {.v = termcmd } },
	{ MODKEY,               XK_b,                   togglebar,      {0} },
	{ MODKEY|ShiftMask,     XK_j,                   rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_k,                   rotatestack,    {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_Down,                rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_Up,                  rotatestack,    {.i = -1 } },
	{ MODKEY,               XK_j,                   focusstack,     {.i = +1 } },
	{ MODKEY,               XK_k,                   focusstack,     {.i = -1 } },
	{ MODKEY,               XK_Down,                focusstack,     {.i = +1 } },
	{ MODKEY,               XK_Up,                  focusstack,     {.i = -1 } },
	{ MODKEY,               XK_i,                   incnmaster,     {.i = +1 } },
	{ MODKEY,               XK_o,                   incnmaster,     {.i = -1 } },
	{ MODKEY,               XK_h,                   setmfact,       {.f = -0.05} },
	{ MODKEY,               XK_l,                   setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,     XK_Return,              zoom,           {0} },
	{ MODKEY,               XK_Tab,                 view,           {0} },
	{ MODKEY|ShiftMask,     XK_q,                   killclient,     {0} },
	{ MODKEY|ControlMask,   XK_comma,               cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,   XK_period,              cyclelayout,    {.i = +1 } },
	{ MODKEY,               XK_space,               setlayout,      {0} },
	{ MODKEY|ShiftMask,     XK_space,               togglefloating, {0} },
	{ MODKEY,               XK_0,                   view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,     XK_0,                   tag,            {.ui = ~0 } },
	{ MODKEY,               XK_comma,               focusmon,       {.i = -1 } },
	{ MODKEY,               XK_period,              focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_comma,               tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_period,              tagmon,         {.i = +1 } },
	{ MODKEY,               XK_minus,               setgaps,        {.i = -1 } },
	{ MODKEY,               XK_plus,                setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_plus,                setgaps,        {.i = 0  } },
	TAGKEYS(                XK_1,                                   0)
	TAGKEYS(                XK_2,                                   1)
	TAGKEYS(                XK_3,                                   2)
	TAGKEYS(                XK_4,                                   3)
	TAGKEYS(                XK_5,                                   4)
	TAGKEYS(                XK_6,                                   5)
	TAGKEYS(                XK_7,                                   6)
	TAGKEYS(                XK_8,                                   7)
	TAGKEYS(                XK_9,                                   8)

	{ DMODKEY,              XK_e,                   spawn,          {.v = exitdwm } },
	{ DMODKEY,              XK_x,                   spawn,          {.v = shutdowncmd } },
	{ DMODKEY,              XK_y,                   spawn,          {.v = lock} },
	{ DMODKEY,              XK_Escape,              spawn,          {.v = rebootcmd } },
	{ 0,                    XF86AudioRaiseVolume,   spawn,          {.v = volup } },
	{ 0,                    XF86AudioLowerVolume,   spawn,          {.v = voldown } },
	{ 0,                    XF86AudioMute,          spawn,          {.v = voltoggle } },

	{ MODKEY,               XK_v,                   spawn,          {.v = clipmenu } },

	{ MODKEY,               XK_z,                   spawn,          {.v = nnn } },
	{ MODKEY,               XK_n,                   spawn,          {.v = newsboat } },
	{ MODKEY,               XK_m,                   spawn,          {.v = neomutt } },
	{ MODKEY,               XK_p,                   spawn,          {.v = slack } },
	{ MODKEY|ShiftMask,     XK_m,                   spawn,          {.v = pulse } },

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

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signum>"` */
static Signal signals[] = {
	/* signum       function        argument  */
	{ 1,            quit,           {0} },
};
