//                標準描述長度示例                                   |
// 風之國度物品
// by naihe  2002-10-25  於茂名

#include <ansi.h>

inherit ITEM;

string *names=({
    HIW"天馬之身"NOR,
    HIW"伸展之左翼"NOR,
    HIW"伸展之右翼"NOR,
    HIW"天馬翔空御雲風"NOR,  // 這是假的
    HIW"天馬翔空御雲風"NOR,
});

string *ids=({
    "tm shen",
    "sz zuoyi",
    "sz youyi",
    "tmxk yyf",
    "tmxk yyf",
});

string *longs=({
    "這是一個不知什麼質地的馬狀物品，卻和平日所見之馬不大相同。\n看來還要和別的什麼部分組合(zuhe)起來才是完整的。\n它上面似乎刻着個細細的名字：",
    "這是一個翅膀模樣的東西，卻似是個左翼，感覺甚為奇怪。\n它上面似乎刻着個細細的名字：",
    "這是一個翅膀模樣的東西，卻似是個右翼，感覺甚為奇怪。\n它上面似乎刻着個細細的名字：",
    "這是一個風之國度的寶物——天馬翔空御雲風。但看起來似乎有些不對勁。",
    "這是一個風之國度的寶物——天馬翔空御雲風。\n它上面似乎刻着個細細的名字：",
});

string *pivotal=({   // a.樞軸的 關鍵的
    "yes",
    "no",
    "no",
    "no",
    "no",
});

string *units=({
    "個",
    "只",
    "只",
    "個",
    "個",
});

string my_mark,my_color,my_msg,
my_mark="feng",my_color=""HIW"",my_msg="風之國度";

#include "fyld_obj.h"