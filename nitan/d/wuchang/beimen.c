// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create ()
{
        set ("short",GRN"北門"NOR);
        set ("long", @LONG
這裏是武漢的北門。這裏地處繁華地帶。東南邊就是碼頭。來來往
往有很多行人和商人，所以熱鬧得很。許多小商小販推着車從這裏走過，
叫賣着自己的商品。有幾個官兵正在這裏檢查着來往的行人。
LONG);

        set("exits", ([
                "south":__DIR__"hzjie1",
        ]));
        set("objects",([
                "/d/city/npc/bing":2,
        ]));
        set("outdoors", "wuchang");

	set("coor/x", -5090);
	set("coor/y", -1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}