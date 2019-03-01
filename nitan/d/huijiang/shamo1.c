// Room: /d/huijiang/shamo1.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set ("short", "沙漠");
        set ("long", @LONG
淡黃色的沙堆連綿，在這死寂一片的世界中，天上不見飛鳥，地上
不見走獸。只有沙漠中倒斃的駱駝屍骨提醒你，曾經有過生命的痕跡。
遠處出現了一抹崗巒。
LONG);
        set("outdoors", "huijiang");
        set("exits", ([ /* sizeof() == 2 */
                "east"  : __FILE__,
                "west"  : __FILE__,
                "south" : __FILE__,
                "north" : __DIR__"shamo2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50010);
        set("coor/y", 9000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}