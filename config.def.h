/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx        = 3;        /* border pixel of windows */
static unsigned int snap            = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static int smartgaps                = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int showbar                  = 1;        /* 0 means no bar */
static int topbar                   = 1;        /* 0 means bottom bar */ 
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 5;       /* horizontal padding of bar */
static const int refreshrate        = 60;       /* Update rate for drag and resize events, in updates (frames) per second */
static const int user_bh            = 10;       /* 2 is the default spacing around the bar's font */
static char font[]                  = "JetBrainsMono Nerd Font:size=16"; 
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=16" };

// Colors
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#dd0000";
static char selbgcolor[]            = "#dd0000";
static char *colors[][3] = {
       /*                      fg           bg           border   */
       [SchemeNorm]     = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]      = { selfgcolor,  selbgcolor,  selbordercolor  },
       [SchemeStatus]   = { normfgcolor, normbgcolor, "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
       [SchemeTagsSel]  = { selfgcolor,  selbgcolor,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
       [SchemeTagsNorm] = { normfgcolor, normbgcolor, "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
       [SchemeInfoSel]  = { selfgcolor,  selbgcolor,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
       [SchemeInfoNorm] = { normfgcolor, normbgcolor, "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
 };

static const char *tagsel[][3] = {
   /*   fg         bg    */
  { normfgcolor, normbgcolor }, /* norm */
  { selfgcolor,  selbgcolor  }, /* sel */
  { selbgcolor,  normbgcolor }, /* occ but not sel */
  { selbgcolor,  normfgcolor }, /* has pinned tag */
};

/* tagging;                     0    1     2     3     4     5     6     7 */
static const char *tags[] = { " ", " ", " ", " ", "󰠮 ", " ", " ", " "};

static const unsigned int ulinepad	= 3;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
  /* The command to search classes:  xprop | grep "CLASS" */
  /* class                                instance  title           tags mask         isfloating  isterminal  noswallow  monitor */
	{ "kitty",                              NULL,     NULL,           0,                 0,          1,           0,        -1 },
	{ "Alacritty",                          NULL,     NULL,           0,                 0,          1,           0,        -1 },
	{ "Chromium",                           NULL,     NULL,           1 << 1,            0,          0,           0,        -1 },
	{ "Thunar",                             NULL,     NULL,           1 << 2,            0,          0,           0,        -1 },
	{ "obsidian",                           NULL,     NULL,           1 << 4,            0,          0,           0,        -1 },
	{ "com.github.th_ch.youtube_music",     NULL,     NULL,           1 << 5,            0,          0,           0,        -1 },
	{ "Spotify",                            NULL,     NULL,           1 << 5,            0,          0,           0,        -1 },
	{ "euphonica",                          NULL,     NULL,           1 << 5,            0,          0,           0,        -1 },
	{ "discord",                            NULL,     NULL,           1 << 6,            0,          0,           0,        -1 },
	{ "todoist-nativefier-6c11dd",          NULL,     NULL,           1 << 6,            0,          0,           0,        -1 },
	{ "pavucontrol",                        NULL,     NULL,           1 << 7,            0,          0,           0,        -1 },
	{ "rog-control-center",                 NULL,     NULL,           1 << 7,            1,          0,           0,        -1 },
};

/* layout(s) */
static float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
#include "movestack.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask /* Super key */
#define ALTKEY Mod1Mask /* Alt key */
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* --- Diary apps --- */
static const char *terminal [] = { "alacritty", NULL };
static const char *subterm  [] = { "kitty", NULL };
static const char *filemg   [] = { "thunar", NULL };
static const char *browser  [] = { "chromium", NULL };
static const char *ytmusic  [] = { "youtube-music", NULL };  
static const char *screensh [] = { "flameshot", "gui", NULL}; 
static const char *xcolorpk [] = { "/home/s7/.config/suckless/scripts/apps/colorpicker.sh", NULL}; 
// static const char *music    [] = { "ncmpcpp", NULL };  

/* --- Rofi apps --- */
static const char *launcher [] = { "/home/s7/.config/suckless/scripts/rofi/launcher.sh", NULL };
static const char *windows  [] = { "rofi", "-show", "window", NULL };
static const char *emojis   [] = { "rofimoji", "-f", "all", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
  	{ "font",               STRING,  &font },
  	{ "normbgcolor",        STRING,  &normbgcolor },
  	{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
  	{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
  	{ "snap",          		  INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	  INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	    FLOAT,   &mfact },
};

/* --- Keybidings --- */
static const Key keys[] = {
	/* modifier                     key        function        argument */ 

// Basic apps 
	{ MODKEY,                       XK_space,  spawn,          {.v = launcher } },
	{ MODKEY,                       XK_period, spawn,          {.v = emojis   } },
	{ MODKEY,                       XK_Return, spawn,          {.v = terminal } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = subterm  } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = filemg   } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = browser  } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = ytmusic  } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = screensh } },
	{ MODKEY,                       XK_w,      spawn,          {.v = windows  } },
	{ MODKEY,                       XK_p,      spawn,          {.v = xcolorpk } },

// Windows management
	{ MODKEY,                       XK_f,      togglefullscr,  {0} }, /* fullscreen */
	{ ALTKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ ALTKEY,                       XK_d,      incnmaster,     {.i = -1 } }, 
  { MODKEY,                       XK_b,      togglebar,      {0} },  /* Hide the taskbar */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } }, 
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,      zoom,           {0} }, 
	{ MODKEY,                       XK_Tab,    view,           {0} }, 

// Gaps
	{ ALTKEY|ControlMask,           XK_u,      incrgaps,       {.i = +1 } },
	{ ALTKEY|ControlMask|ShiftMask, XK_u,      incrgaps,       {.i = -1 } },
	{ ALTKEY|ControlMask,           XK_i,      incrigaps,      {.i = +1 } },
	{ ALTKEY|ControlMask|ShiftMask, XK_i,      incrigaps,      {.i = -1 } },
	{ ALTKEY|ControlMask,           XK_o,      incrogaps,      {.i = +1 } },
	{ ALTKEY|ControlMask|ShiftMask, XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },

// My layouts
	{ ALTKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, /* tile layout        */
	{ ALTKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, /* monocle layout     */
	{ ALTKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, /* spiral layout      */
	{ ALTKEY|ControlMask,           XK_comma,  cyclelayout,    {.i = -1 } },
	{ ALTKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ ALTKEY|ShiftMask,             XK_space,  togglefloating, {0} },                /* floating layout    */
	{ ALTKEY,                       XK_space,  setlayout,      {0} },                /* last choose layout */
	{ ALTKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ ALTKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ ALTKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ ALTKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ ALTKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ ALTKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

// System
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} }, /* Restart */
	{ MODKEY,                       XK_q,      quit,           {1} }, /* Refresh */
	{ MODKEY,                       XK_c,      killclient,     {0} },

// Resize floating windows
	{ ALTKEY,                       XK_j,    moveresize,     {.v = "0x 25y 0w 0h" } },
	{ ALTKEY,                       XK_k,    moveresize,     {.v = "0x -25y 0w 0h" } },
	{ ALTKEY,                       XK_l,    moveresize,     {.v = "25x 0y 0w 0h" } },
	{ ALTKEY,                       XK_h,    moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ ALTKEY|ShiftMask,             XK_j,    moveresize,     {.v = "0x 0y 0w 25h" } },
	{ ALTKEY|ShiftMask,             XK_k,    moveresize,     {.v = "0x 0y 0w -25h" } },
	{ ALTKEY|ShiftMask,             XK_l,    moveresize,     {.v = "0x 0y 25w 0h" } },
	{ ALTKEY|ShiftMask,             XK_h,    moveresize,     {.v = "0x 0y -25w 0h" } },
	{ ALTKEY|ControlMask,           XK_k,    moveresizeedge, {.v = "t"} },
	{ ALTKEY|ControlMask,           XK_j,    moveresizeedge, {.v = "b"} },
	{ ALTKEY|ControlMask,           XK_h,    moveresizeedge, {.v = "l"} },
	{ ALTKEY|ControlMask,           XK_l,    moveresizeedge, {.v = "r"} },
	{ ALTKEY|ShiftMask,             XK_w,    moveresizeedge, {.v = "T"} },
	{ ALTKEY|ShiftMask,             XK_s,    moveresizeedge, {.v = "B"} },
	{ ALTKEY|ShiftMask,             XK_a,    moveresizeedge, {.v = "L"} },
	{ ALTKEY|ShiftMask,             XK_d,    moveresizeedge, {.v = "R"} },

// Tags
	{ ALTKEY|ShiftMask,             XK_Tab,  rotatetags,     {.i = -1 } },
	{ ALTKEY,                       XK_Tab,  rotatetags,     {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1) 
  TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = terminal } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

