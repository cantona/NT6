#include <ansi.h>
inherit RIVER;

void create()
{
        set("short", "船廠");
        set("long", @LONG
這裡是古鎮船廠。船廠是位于關外大平原中部的一個古老
的小鎮，此鎮西、南、北、三面是以高牆壘築利于堅守。東面
臨鬆花江天成天險，乃兵家必爭的要地。鬆花江 (river)在冬
春時結冰可通行，夏秋化凍你只好找船家幫忙了。
LONG);
        //set("arrive_room", "/d/guanwai/damenkan");
        set("to", "/d/guanwai/damenkan");
        set("need_dodge", 200);       
        set("exits", ([
                "south" : __DIR__"xuedi3",
        ]));
        set("objects", ([
                __DIR__"npc/chuanfu" : 1,
        ]));
        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

        set("outdoors", "guanwai");
        set("coor/x", 4030);
	set("coor/y", 9260);
	set("coor/z", 0);
	setup();
        replace_program(RIVER);
}
