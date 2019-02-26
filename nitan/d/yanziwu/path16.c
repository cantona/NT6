// Room: /d/yanziwu/path16.c
// Date: Jan.28 2000 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "黃泥小路");
        set("long", @LONG
這是條黃泥小路，路邊植着一列鮮嫩的青草，路南是蓮韻塘，路北
隔着柳叢，可以看到煙波太湖上的漁帆。白色漁帆下，赤腳漁子撒網捕
魚，漁歌飄來，動聽入耳。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "south" : __DIR__"bridge3",
                "west"  : __DIR__"path17",
                "east"  : __DIR__"bridge2",
        ]));
        set("coor/x", 1220);
        set("coor/y", -1220);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}