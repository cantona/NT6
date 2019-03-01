// Room: /d/yanziwu/path17.c
// Date: Jan.28 2000 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "黃泥小路");
        set("long", @LONG
這是條黃泥小路，路邊植著一列鮮嫩的青草，路東南是蓮韻塘，路
北隔著柳叢，可以看到煙波太湖上的漁帆。白色漁帆下，赤腳漁子撒網
捕魚，漁歌飄來，動聽入耳。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "southwest" : __DIR__"ouxiang1",
                "east"      : __DIR__"path16",
        ]));
        set("coor/x", 1210);
        set("coor/y", -1220);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}