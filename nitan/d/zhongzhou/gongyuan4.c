inherit ROOM;

void create()
{
        set("short", "中州貢院");
        set("long", @LONG
中州貢院是天下最熱鬧的一所考場，每月初一，全國各地
的士子都來此處趕考。院門兩邊由士兵看守，要想夾帶可不行
圍牆上有張新貼的告示。
LONG);
        set("objects", ([
                  "/d/kaifeng/npc/zhukao3" : 1,
        ]));
        set("no_clean_up", 0);

        set("exits", ([
                  "south" : __DIR__"yanling2",
        ]));

        set("outdoors", "zhongzhou");
        set("coor/x", -9070);
	set("coor/y", -990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}