// /d/beihai/qingxiao.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "慶宵樓");
        set("long", @LONG
這座慶霄樓為一踞山半之二層建築，歇山頂。上層四周挑廊，是冬
日觀冰嬉之所。站在這裏可以清楚的看見瓊島以西的景色。
LONG
        );
        set("exits", ([
                "southdown" : __DIR__"yuexin",
                "northdown" : __DIR__"yuegu",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -200);
        set("coor/y", 4090);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}