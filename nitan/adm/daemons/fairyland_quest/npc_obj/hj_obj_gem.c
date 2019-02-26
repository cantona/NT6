//                標準描述長度示例                                   |
// 幻境內物品  各族的寶物(本物件不加入列表)
// （需要此類物品，方可獲得要尋找的寶物的最重要組合部分）
// by naihe  2002-10-28  於茂名
// naihe 05-9-8 7:57 V1.8 繼續更新。修正一個潛在隱患。

#include <ansi.h>

inherit ITEM;


string *names=({
    "蠻野族寶物",
    "猛力族寶物",
    "矮妖族寶物",
    "山怪族寶物",
    "巨人族寶物",
});

string *ids=({
    "manye baowu",
    "mengli baowu",
    "aiyao baowu",
    "shanguai baowu",
    "juren baowu",
});

string *longs=({
    "這是一個蠻野族的寶物，黑呼呼的一團不知道是什麼，也不知道有什麼用。\n",
    "這是一個猛力族的寶物，黑呼呼的一團不知道是什麼，也不知道有什麼用。\n",
    "這是一個矮妖族的寶物，黑呼呼的一團不知道是什麼，也不知道有什麼用。\n",
    "這是一個山怪族的寶物，黑呼呼的一團不知道是什麼，也不知道有什麼用。\n",
    "這是一個巨人族的寶物，黑呼呼的一團不知道是什麼，也不知道有什麼用。\n",
});

void setme( int iii )
{
    if( iii == 99 || iii < 0 || iii >= sizeof(names) )
        iii = random(sizeof(names));
    set("iii", iii);
    set_name( names[ iii ], ({ ids[ iii ], "baowu" }) );
    set_weight(100);
    if (clonep())
        set_default_object(__FILE__);

    set("long", longs[ iii ]);
    set("unit", "個");
    set("hj_game/obj","the_gem");
    set("no_refresh", 1); // 不被MUD刷掉

    set("value", 1);  // 該物件扔下後不會消失。
}

void create()
{
    setme(99);
    setup();
}