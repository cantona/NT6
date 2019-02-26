// Room: /d/yanziwu/path9.c
// Date: Jan.28 2000 by Winder

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "青泥小徑");
        set("long", @LONG
一條青泥小徑蜿蜒延伸向前方。只見小徑兩側，花木扶疏，長草幽
深，十分清淨。前面看不到亭院，後不見樓閣，唯聞清風扶柳，在低低
吟唱。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "north"  : __DIR__"path10",
                "west"   : __DIR__"path8",
        ]));
        set("coor/x", 1240);
        set("coor/y", -1250);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}