//houyuan.c
inherit ROOM;
void create()
{
        set("short","後院");
        set("long", @LONG
這裡是華山派的後院，裡面是華山弟子的居室和練功房。華山派
總所倚山而建，地勢險峻，往東便是懸崖。西面是另一個小花院，有
假山小池，景色怡人，頗有江南林園的特色。
LONG );
        set("exits",([
                "northeast"  : __DIR__"garden",
                "west"       : __DIR__"jiashan",
                "east"       : __DIR__"xuanya",
        ]));
        set("outdoors", "huashan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
 