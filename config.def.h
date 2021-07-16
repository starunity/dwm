/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx    = 0;        /* border pixel of windows */
static const unsigned int gappx       = 9;       /* gaps between windows */
static const unsigned int snap        = 32;       /* snap pixel */
static const int showbar              = 1;        /* 0 means no bar */
static const int topbar               = 1;        /* 0 means bottom bar */
static const int user_bh              = 42;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]            = { "Noto Sans CJK SC:style=Regular:size=12", "Symbols Nerd Font:style=2048-em:size=14" };
static const char dmenufont[]         = "Noto Sans CJK SC:style=Regular:size=12";
static const char col_gray1[]         = "#222222";
static const char col_gray2[]         = "#444444";
static const char col_gray3[]         = "#bbbbbb";
static const char col_gray4[]         = "#eeeeee";
static const char col_cyan[]          = "#444444";
static const unsigned int baralpha    = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]        = {
    /*                   fg         bg         border   */
    [SchemeNorm]     = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]      = { col_gray4, col_cyan,  col_cyan  },
    [SchemeStatus]   = { col_gray3, col_gray1, "#000000" }, // Statusbar right {text,background,not used but cannot be empty}
    [SchemeTagsSel]  = { col_gray4, col_cyan,  "#000000" }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm] = { col_gray3, col_gray1, "#000000" }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_gray4, col_gray1, "#000000" }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm] = { col_gray3, col_gray1, "#000000" }, // infobar middle  unselected {text,background,not used but cannot be empty}
};
static const unsigned int alphas[][3]      = {
    /*                   fg      bg        border     */
    [SchemeNorm]     = { OPAQUE, baralpha, borderalpha },
    [SchemeSel]      = { OPAQUE, baralpha, borderalpha },
    [SchemeStatus]   = { OPAQUE, baralpha, borderalpha }, // Statusbar right {text,background,not used but cannot be empty}
    [SchemeTagsSel]  = { OPAQUE, baralpha, borderalpha }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm] = { OPAQUE, baralpha, borderalpha }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { OPAQUE, baralpha, borderalpha }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm] = { OPAQUE, baralpha, borderalpha }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

static const char *const autostart[] = {
    "picom", NULL,
    "feh", "--bg-fill", "/home/star/.config/background/iss022e062672.jpg", NULL,
    "fcitx5", NULL,
    "amixer", "set", "Master", "mute", NULL,
    "/home/star/.config/dwm-scripts/dwm-statusbar-autorefresh.sh", NULL,
    "xss-lock", "--", "betterlockscreen", "-l", "dim", NULL,
    NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            1,           -1 },
    { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
    { NULL,       "qq.exe",   NULL,       0,            1,           -1 },
    { "flameshot",NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char  dmenumon[2]             = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]        = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]         = { "st", NULL };
static const char scratchpadname[]   = "scratchpad";
static const char *scratchpadcmd[]   = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static const char *volumetoggle[]    = { "/home/star/.config/dwm-scripts/dwm-volumetoggle.sh", NULL };
static const char *volumeup[]        = { "/home/star/.config/dwm-scripts/dwm-volumeup.sh", NULL };
static const char *volumedown[]      = { "/home/star/.config/dwm-scripts/dwm-volumedown.sh", NULL };

static const char *brightnessup[]    = { "xbacklight", "+5", NULL };
static const char *brightnessdown[]  = { "xbacklight", "-5", NULL };

static const char *trayertoggle[]    = { "/home/star/.config/dwm-scripts/dwm-trayertoggle.sh", NULL };
static const char *screenkeytoggle[] = { "/home/star/.config/dwm-scripts/dwm-screenkeytoggle.sh", NULL };

static const char *screenshot[]      = { "flameshot", "gui", NULL };

static const char *lockscreen[]      = { "loginctl", "lock-session", NULL };

static Key keys[] = {
    /* modifier                     key                       function        argument */
    { MODKEY,                       XK_p,                     spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return,                spawn,          {.v = termcmd } },
    { 0,                            XF86XK_AudioMute,         spawn,          {.v = volumetoggle } },
    { 0,                            XF86XK_AudioRaiseVolume,  spawn,          {.v = volumeup } },
    { 0,                            XF86XK_AudioLowerVolume,  spawn,          {.v = volumedown } },
    { 0,                            XF86XK_MonBrightnessUp,   spawn,          {.v = brightnessup } },
    { 0,                            XF86XK_MonBrightnessDown, spawn,          {.v = brightnessdown } },
    { MODKEY,                       XK_F12,                   spawn,          {.v = brightnessup } },
    { MODKEY,                       XK_F11,                   spawn,          {.v = brightnessdown } },
    { MODKEY|ShiftMask,             XK_t,                     spawn,          {.v = trayertoggle } },
    { MODKEY|ShiftMask,             XK_s,                     spawn,          {.v = screenkeytoggle } },
    { MODKEY|ShiftMask,             XK_a,                     spawn,          {.v = screenshot } },
    { MODKEY,                       XK_x,                     spawn,          {.v = lockscreen } },
    { MODKEY,                       XK_y,                     togglescratch,  {.v = scratchpadcmd } },
    { MODKEY,                       XK_b,                     togglebar,      {0} },
    { MODKEY|ShiftMask,             XK_j,                     rotatestack,    {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,                     rotatestack,    {.i = -1 } },
    { MODKEY,                       XK_j,                     focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,                     focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,                     incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,                     incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,                     setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,                     setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_Return,                zoom,           {0} },
    { MODKEY,                       XK_Tab,                   view,           {0} },
    { MODKEY|ShiftMask,             XK_q,                     killclient,     {0} },
    { MODKEY,                       XK_t,                     setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,                     setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,                     setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_space,                 setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,                 togglefloating, {0} },
    { MODKEY|ShiftMask,             XK_f,                     togglefullscr,  {0} },
    { MODKEY,                       XK_0,                     view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,                     tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,                 focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period,                focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,                 tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period,                tagmon,         {.i = +1 } },
    { MODKEY,                       XK_minus,                 setgaps,        {.i = -1 } },
    { MODKEY,                       XK_equal,                 setgaps,        {.i = +1 } },
    { MODKEY|ShiftMask,             XK_equal,                 setgaps,        {.i = 0  } },
    TAGKEYS(                        XK_1,                                     0)
    TAGKEYS(                        XK_2,                                     1)
    TAGKEYS(                        XK_3,                                     2)
    TAGKEYS(                        XK_4,                                     3)
    TAGKEYS(                        XK_5,                                     4)
    TAGKEYS(                        XK_6,                                     5)
    TAGKEYS(                        XK_7,                                     6)
    TAGKEYS(                        XK_8,                                     7)
    TAGKEYS(                        XK_9,                                     8)
    { MODKEY|ShiftMask,             XK_e,                     quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

