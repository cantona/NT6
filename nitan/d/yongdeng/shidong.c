// Room: /huanghe/shidong.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "石洞");
        set("long", @LONG
這是沙漠中天然形成的一個石洞，洞中光線昏暗，但卻十分幹燥，
地下舖著幾堆稻草，似乎是供人睡臥之用，靜心凝聽，洞中仿佛有陣陣
水聲。洞的一角放著數堆人頭骨(skulls)。
LONG );
        set("exits", ([
                "out" : __DIR__"shamo1",
        ]));
        set("item_desc", ([
                "skulls" : "一堆整整齊齊的骷髏頭，上一中三下五，不多不少，恰是
九顆白骨骷髏頭。\n",
        ]));
        set("objects", ([
                CLASS_D("taohua") + "/chen": 1,
                CLASS_D("taohua") + "/mei": 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -16071);
	set("coor/y", 4229);
	set("coor/z", -1);
	setup();
//        replace_program(ROOM);
}
void init()
{
        delete_temp("shamo/steps", this_player());
}
