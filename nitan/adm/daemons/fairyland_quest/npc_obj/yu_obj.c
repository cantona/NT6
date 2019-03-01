//                標準描述長度示例                                   |
// 雨之國度物品
// by naihe  2002-10-26  于茂名

#include <ansi.h>

inherit ITEM;

string *names=({
    MAG"晶瑩之淚"NOR,
    MAG"敏慧之心"NOR,
    MAG"靈巧之手"NOR,
    MAG"心靈手巧善之淚"NOR,  // 這是假的
    MAG"心靈手巧善之淚"NOR,
});

string *ids=({
    "jy lei",
    "mh xin",
    "lq shou",
    "xlsq szl",
    "xlsq szl",
});

string *longs=({
    "它猶如一顆凝結的淚珠模樣，十分美麗。\n看來還要和別的什麼部分組合(zuhe)起來才是完整的。\n它上面似乎刻著個細細的名字：",
    "這是一顆紅心模樣的東西，十分美麗。\n它上面似乎刻著個細細的名字：",
    "這是一只手掌模樣的東西，線條美麗，似是女子手掌一般。\n它上面似乎刻著個細細的名字：",
    "這是一個雨之國度的寶物──心靈手巧善之淚。但看起來似乎有些不對勁。",
    "這是一個雨之國度的寶物──心靈手巧善之淚。\n它上面似乎刻著個細細的名字：",
});

string *units=({
    "顆",
    "顆",
    "只",
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
my_mark="yu",my_color=""MAG"",my_msg="雨之國度";

#include "fyld_obj.h"