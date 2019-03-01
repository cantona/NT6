// Room: /d/yanping/road3.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "石街");
        set("long", @LONG
這是一條青石舖就的長街。延平府依山傍水而建，這條石街便也起
伏跌宕不休。北邊是西山，爬上高高的石街，便是州學所在了。東邊通
往府衙，西邊便是西門。南邊緊鄰高厚冰冷的青磚城牆。
LONG );
        set("exits", ([
                "west"    : __DIR__"ximen",
                "east"    : __DIR__"road2",
                "northup" : __DIR__"xishan",
        ]));
        set("objects", ([
                "/d/village/npc/kid" : 1,
        ]));
        set("outdoors", "yanping");
        set("coor/x", 1450);
        set("coor/y", -6190);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}