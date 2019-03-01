// Room: /d/yanziwu/hongxia2.c
// Date: Jan.28 2000 by Winder

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", HIR"紅霞二樓"NOR);
        set("long", @LONG
紅霞樓上陳設淡雅有致。一幅中堂繪的是一叢盛開的茶花，兩旁一
副木聯，寫的是：“春溝水動茶花白，夏谷雲生荔枝紅”。
LONG );
        set("exits", ([
                "down"     : __DIR__"hongxia1",
        ]));
        set("objects", ([
                __DIR__"obj/chahua14" :1,
                __DIR__"npc/xiaoming" :1,
        ]));
        set("coor/x", 1250);
        set("coor/y", -1250);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}