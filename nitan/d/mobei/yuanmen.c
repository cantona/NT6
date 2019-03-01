// Room: /d/mobei/yuanmen.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "轅門");
        set("long", @LONG
轅門把兵營和居民帳篷分隔開來。原木的轅門邊有守衛監視通行的
每一個人。兩排旌旗迎風招展，一條直道向北通向鐵木真的營帳。
LONG);
        set("outdoors","mobei");
        set("no_clean_up", 0);
        set("exits", ([ /* sizeof() == 2 */
                "south" : __DIR__"buluo1",
                "north" : __DIR__"road1",
        ]));
        set("coor/x", -210);
        set("coor/y", 5230);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}