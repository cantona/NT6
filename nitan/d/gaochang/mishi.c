// Room: /d/gaochang/shulin13.c
// Last Modified by Winder on Jul. 15 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "高昌後殿");
        set("long", @LONG
大廳裏有幾具白骨骷髏。只見大半宮室已然毀圯，殿堂中堆滿了黃
沙。往北邊似乎還有路，在陰暗處站有一人正好擋住了去路。
LONG   
        );

        set("outdoors", "gaochang");
        set("exits", ([
                "south" : __DIR__"zoulangc",
                "north" : __DIR__"mishi2"
        ]));
        set("no_clean_up", 0);
        set("coor/x", -36510);
        set("coor/y", 10100);
        set("coor/z", 30);
        setup();
}

void init()
{
        object ob, room;
        ob = this_player();
        room = this_object();

        if( query("id", ob) == "ghost" || !living(ob))return ;
        else if( present("map", ob))
                {
message_vision(HIW"\n突然之間，前面一個陰森森的聲音説道：
「果然是有膽之士!怎麼你有高昌迷宮的地圖,難道是天意？
高昌迷宮真的有敵國的財富嗎？哈。。哈哈。。」 
笑聲中透着無限的淒涼和悲狀。\n\n" NOR, ob);
                }
                else
                {
message_vision(HIW"\n突然之間，前面一個陰森森的聲音説道：
擅闖高昌迷宮者死! 只見一點光向你襲來，你想躲也躲不開了.
原來是一根毒針插入你的身體。\n\n" NOR, ob);
                        ob->die();
                }
}