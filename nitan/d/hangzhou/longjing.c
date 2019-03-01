// longjing.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "龍井");
        set("long", @LONG
只見井(jing)水澈可見底而且清冷異常。龍井原名龍泓澗，傳說
此井與海相通，其中必定有龍，祈禱必雨，故名“龍井”。蘇東坡曾
有詩“人言山佳水亦佳，下有萬古蛟龍潭”。井旁建有茶室。往南便
回大路。
  蒙面人(Mengmian ren)
LONG);
        set("exits", ([
                "east"     : __DIR__"chashi",
                "south"    : __DIR__"shanlu5",
        ]));
        set("item_desc", ([
            "jing" : "井水清澈見底，井底部有一些豆狀小顆粒疊起的小堆。\n",
        ]));
        set("resource/water", 1);
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
	set("coor/x", 770);
	set("coor/y", -2100);
	set("coor/z", 40);
	setup();
        replace_program(ROOM);
}