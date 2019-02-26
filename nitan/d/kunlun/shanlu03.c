// Room: /d/kunlun/shanlu03.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "盤山路");
        set("long",@long
這是一條盤山的路，山間穿來鳥鳴獸叫，路面似乎已很久沒有修整
了，顯得有些破舊，但是從遺留的痕跡依稀可以看出當年的輝煌。南面
是山下，北面山上是崑崙派的所在。
long);
        set("exits",([
                "southdown" : __DIR__"shanlu02",
                "northup"   : __DIR__"shanlu04",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "kunlun");
        set("coor/x", -119990);
        set("coor/y", 40020);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}