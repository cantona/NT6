// Room: /d/shaolin/xiaowu.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "小土屋");
        set("long", @LONG
土屋中間掛著一張大竹席，將後邊的那半間隔作了臥房。地上放
了架木制的紡車，上面已經積滿了灰塵，看來是好久沒人用了。地面
上的塵土上留有幾行散亂的足跡，通向席後的臥房。
LONG );
        set("exits", ([
                "south" : __DIR__"houshan",
                "north" : __DIR__"woshi",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
