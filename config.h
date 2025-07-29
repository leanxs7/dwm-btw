/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=16" };
static const char color1[]       = "#222222";
static const char color2[]       = "#444444";
static const char color3[]       = "#bbbbbb";
static const char color4[]       = "#eeeeee";
static const char color5[]       = "#dd0000"; /* red  */

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]     = { color3, color1,  color2     },
	[SchemeSel]      = { color4, color5,  color5     },
	[SchemeStatus]   = { color3, color1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { color4, color5,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm] = { color3, color1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
	[SchemeInfoSel]  = { color4, color5,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm] = { color3, color4,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging;                     0    1     2     3     4     5     6     7 */
static const char *tags[] = { " ", " ", "🗁", " ", "📝", " ", " ", " "};

static const Rule rules[] = {
/* The command to search classes:  xprop | grep "CLASS" */
	/* class                                  instance    title       tags mask     isfloating   monitor */
	{ "Chromium",                             NULL,       NULL,        1 << 1,          0,           -1 },
	{ "Thunar",                               NULL,       NULL,        1 << 2,          0,           -1 },
	{ "nvim",                                 NULL,       NULL,        1 << 3,          0,           -1 },
	{ "obsidian",                             NULL,       NULL,        1 << 4,          0,           -1 },
	{ "com.github.th_ch.youtube_music",       NULL,       NULL,        1 << 5,          0,           -1 },
	{ "pavucontrol",                          NULL,       NULL,        1 << 7,          0,           -1 },
//{ "Spotify",                              NULL,       NULL,  (1 << 5) | (1 << 6),   0,           -1 },  // Will show in tags 6 and 7
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
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
// static const char *music    [] = { "ncmpcpp", NULL };  

/* --- Rofi apps --- */
static const char *launcher [] = { "rofi", "-show", "drun", "-show-icons", NULL };
static const char *windows  [] = { "rofi", "-show", "window", NULL };
static const char *emojis   [] = { "rofimoji", NULL };

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
	{ MODKEY,                       XK_w,      spawn,          {.v = windows  } },

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
	{ MODKEY|ShiftMask,             XK_h,      view,           {0} }, 

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

// Tags
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
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = terminal } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
