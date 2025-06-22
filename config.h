/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=16" };
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#dd0000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/*  tagging are in binaries     1     2     4     8    16    32    64   128 */
static const char *tags[] = { " ", " ", "🗁", " ", "📝", " ", " ", " " };

static const Rule rules[] = {
	/* class                                  instance    title       tags mask     isfloating   monitor */
	{ "Chromium",                             NULL,       NULL,           2,            0,           -1 },
	{ "thunar",                               NULL,       NULL,           4,            0,           -1 },
	{ "nvim",                                 NULL,       NULL,           8,            0,           -1 },
	{ "obsidian",                             NULL,       NULL,          16,            0,           -1 },
	{ "com.github.th_ch.youtube_music",       NULL,       NULL,          32,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask /* Super Key */
#define ALTKEY Mod1Mask /* Alt Key */
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
	/* Terminals */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/local/bin/st", "-c", cmd, NULL } }


/* ---- Commands ---- */
	/* Apps */
static const char *terminal [] = { "alacritty", NULL };
static const char *subterm  [] = { "st", NULL };
static const char *filemgr  [] = { "thunar", NULL };
static const char *browser  [] = { "chromium", NULL };
static const char *ytmusic  [] = { "youtube-music", NULL };  

	/* Rofi apps */
static const char *launcher [] = { "rofi", "-show", "drun", "-show-icons", NULL };
static const char *windows  [] = { "rofi", "-show", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = launcher } },
	{ MODKEY,                       XK_w,      spawn,          {.v = windows  } },
	{ MODKEY,                       XK_Return, spawn,          {.v = terminal } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = subterm  } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = filemgr  } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = browser  } },
	{ MODKEY,             		XK_m,      spawn,          {.v = ytmusic  } },
	{ MODKEY,                       XK_q,      togglebar,      {0} },  /* hide taskbar */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ ALTKEY,             		XK_p,      zoom,           {0} },
	{ ALTKEY,                       XK_Tab,    view,           {0} },
	{ ALTKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ ALTKEY,                       XK_r,      setlayout,      {.v = &layouts[1]} },
	{ ALTKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ ALTKEY,                       XK_space,  setlayout,      {0} },  /* {0} } significa regresar al ultimo */
	{ ALTKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = terminal} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

