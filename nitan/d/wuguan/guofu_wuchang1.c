#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "西練武場");
	set("long", @LONG
這是間大大的房子，十分寬闊，不少人在這裏汗流浹背的
苦練着功夫，地上有一些練武用的工具。
LONG);
        set("no_fight", 1);
        set("can_dazuo", 1);
	set("exits", ([
	       "north" : __DIR__"guofu_wuchang3",
	       "east" : __DIR__"guofu_lang1",
        ]));
	setup();
}