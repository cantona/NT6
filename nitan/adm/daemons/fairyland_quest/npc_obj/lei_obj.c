//                標準描述長度示例                                   |
// 雷之國度物品
// by naihe  2002-10-27  于茂名

#include <ansi.h>

inherit ITEM;

string *names=({
    HIC"神力之劍"NOR,
    HIC"點綴之石"NOR,
    HIC"容忍之鞘"NOR,
    HIC"完美的神力之劍"NOR,
    HIC"完美的神力之劍"NOR,
});

string *ids=({
    "sl jian",
    "dz shi",
    "rr shao",
    "wm slzj",
    "wm slzj",
});

string *longs=({
    "這是一把小小的劍，看起來不似是武器。劍柄上還刻有兩字：神力。\n看來還要和別的什麼部分組合(zuhe)起來才是完整的。\n它上面似乎刻著個細細的名字：",
    "這是一顆光滑的小圓石子，十分美麗。\n它上面似乎刻著個細細的名字：",
    "這是一把空劍鞘，在口子邊上刻有兩字：容忍。\n它上面似乎刻著個細細的名字：",
    "這是一個雷之國度的寶物──完美的神力之劍。但看起來似乎有些不對勁。",
    "這是一個雷之國度的寶物──完美的神力之劍。\n它上面似乎刻著個細細的名字：",
});

string *units=({
    "把",
    "顆",
    "把",
    "個",
    "個",
});

string *pivotal=({   // a.樞軸的 關鍵的
    "yes",
    "no",
    "no",
    "no",
    "no",
});

string my_mark,my_color,my_msg,
my_mark="lei",my_color=""HIC"",my_msg="雷之國度";

#include "fyld_obj.h"