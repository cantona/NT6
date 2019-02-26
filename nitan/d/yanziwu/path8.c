// Room: /d/yanziwu/path8.c
// Date: Jan.28 2000 by Winder

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "青泥小徑");
        set("long", @LONG
雲錦樓後，是一條青泥小徑，小徑兩側，林木幽深，十分清淨。小
徑在曲折中蜿蜒延伸，前面看不到亭院，後不見樓閣，唯聞清風扶柳，
低低吟唱。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "south"  : __DIR__"yunjin1",
                "east"   : __DIR__"path9",
        ]));
        set("coor/x", 1230);
        set("coor/y", -1250);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}