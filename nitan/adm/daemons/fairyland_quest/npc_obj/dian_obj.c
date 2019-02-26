//                標準描述長度示例                                   |
// 電之國度物品
// by naihe  2002-10-27  於茂名

#include <ansi.h>

inherit ITEM;

string *names=({
    HIG"綠色寶石"NOR,
    HIR"紅色寶石"NOR,
    HIB"藍色寶石"NOR,
    HIG"三星之耀電石光"NOR,
    HIG"三星之耀電石光"NOR,
});

string *ids=({
    "lvse baoshi",
    "hongse baoshi",
    "lanse baoshi",
    "sxzy dsg",
    "sxzy dsg",
});

string *longs=({
    "這是一顆綠色的寶石，散發着迷人的幽幽光芒。\n看來還要和別的什麼部分組合(zuhe)起來才是完整的。\n它上面似乎刻着個細細的名字：",
    "這是一顆紅色的寶石，散發着迷人的幽幽光芒。\n它上面似乎刻着個細細的名字：",
    "這是一顆藍色的寶石，散發着迷人的幽幽光芒。\n它上面似乎刻着個細細的名字：",
    "這是一個電之國度的寶物——三星之耀電石光。但看起來似乎有些不對勁。",
    "這是一個電之國度的寶物——三星之耀電石光。\n它上面似乎刻着個細細的名字：",
});

string *units=({
    "顆",
    "顆",
    "顆",
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
my_mark="dian",my_color=""HIG"",my_msg="電之國度";

#include "fyld_obj.h"