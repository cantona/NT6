//                標準描述長度示例                                   |
// 幻境﹒遙遠傳說之起緣﹒幽靈顯現 新增物品  各族的權杖(本物件不加入列表)
// 本物品配合 hj_room1.c 的搜集權杖JOB，並且僅由 hj_npc_kill.c 制造。
// by naihe  2003-10-21  于茂名
// naihe 05-9-8 7:57 V1.8 繼續更新。修正一個潛在隱患。

#include <ansi.h>

inherit ITEM;


string *names = ({
    "蠻野族權杖",
    "猛力族權杖",
    "矮妖族權杖",
    "山怪族權杖",
    "巨人族權杖",
});

string *ids=({
    "manye quanzhang",
    "mengli quanzhang",
    "aiyao quanzhang",
    "shanguai quanzhang",
    "juren quanzhang",
});

string *longs=({
    "這是一柄蠻野族的權杖，通體漆黑，只有巴掌長短，卻自有一股懾人心魄的氣勢。\n",
    "這是一柄猛力族的權杖，通體漆黑，只有巴掌長短，卻自有一股懾人心魄的氣勢。\n",
    "這是一柄矮妖族的權杖，通體漆黑，只有巴掌長短，卻自有一股懾人心魄的氣勢。\n",
    "這是一柄山怪族的權杖，通體漆黑，只有巴掌長短，卻自有一股懾人心魄的氣勢。\n",
    "這是一柄巨人族的權杖，通體漆黑，只有巴掌長短，卻自有一股懾人心魄的氣勢。\n",
});

void setme( int iii )
{
    if( iii == 99 || iii < 0 || iii >= sizeof(names) )
        iii = random(sizeof(names));
    set("iii", iii);
    set_name( names[ iii ], ({ ids[ iii ], "quan zhang", "zhang" }) );
    set_weight(100);
    if (clonep())
        set_default_object(__FILE__);

    set("long", longs[ iii ]);
    set("unit", "柄");
    set("hj_game/obj","the_gem_qz");
    set("no_refresh", 1); // 不被MUD刷掉

    set("value", 1);  // 該物件扔下後不會消失。
}

void create()
{
    setme(99);
    setup();
}