// Room: /d/wanjiegu/wlshan.c

inherit ROOM;

void create()
{
        set("short", "無量山");
        set("long", @LONG
這裏就是無量山區。山上樹木叢生，很少有人走動，你都無法找
到一條能夠上山的路。沿着山腳有一條蜿蜒的小路。
LONG );
        set("outdoors", "wanjiegu");
        set("exits", ([ /* sizeof() == 2 */
                "northwest" : __DIR__"wlroad1",
                "southeast" : __DIR__"riverside4",
        ]));

        setup();
        replace_program(ROOM);
}