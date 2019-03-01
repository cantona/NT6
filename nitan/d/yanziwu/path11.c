// Room: /d/yanziwu/path11.c
// Date: Jan.28 2000 by Winder

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "青泥小徑");
        set("long", @LONG
一條青泥小徑蜿蜒延伸向前方。只見小徑兩側，花木扶疏，長草幽
深，十分清凈。前面看不到亭院，後不見樓閣，唯聞清風扶柳，在低低
吟唱。
LONG );
        set("outdoors", "mantuo");
        set("exits", ([
                "south"  : __DIR__"bridge1",
                "north"  : __DIR__"mingzhu",
                "east"   : __DIR__"path12",
                "west"   : __DIR__"bridge2",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoshi" : 1,
        ]));
        set("coor/x", 1240);
        set("coor/y", -1220);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}