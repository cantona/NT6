inherit ROOM;

void create()
{
        set("short", "科舉試場");
        set("long", @LONG
洛陽的科舉試場是天下最熱鬧的一所考場，每月初一，全國各地的士
子都來此處趕考。院門兩邊由士兵看守，要想夾帶可不行，圍牆上有張新
貼的告示。
LONG);
        set("objects", ([
                "/d/kaifeng/npc/zhukao3" : 1,
                "/d/beijing/npc/shusheng1" : 2,
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"nroad3",
        ]));

	set("coor/x", -7000);
	set("coor/y", 2210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}