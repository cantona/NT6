#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "東練武場");
	set("long", @LONG
這是露天練武場，好多人在這裏辛苦的練着，你走在場中
沒有人回頭看你一眼，都在聚精匯神的練着自己的功夫。
LONG);
        set("no_fight", 1);
        set("can_dazuo", 1);
	set("exits", ([
	       "north" : __DIR__"guofu_lang4",
	       "south" : __DIR__"guofu_wuchang2",
        ]));
	setup();
}
