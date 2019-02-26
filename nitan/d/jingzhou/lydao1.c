inherit ROOM;

void create()
{
        set("short", "林蔭道");
        set("long", @LONG
這是一條安靜的林蔭道，地上鋪着奇奇怪怪五顏六色的石子，向
南北兩頭延伸。北邊是熱鬧的西大街，南邊遠處有幾個孩童在玩耍。
西面是高大的荊州城牆。
LONG );
        set("outdoors", "jingzhou");
        set("objects", ([
                "/d/beijing/npc/kid1" : 1,
        ]));
        set("exits", ([
                "north" : __DIR__"xidajie2",
                "south" : __DIR__"lydao2",
        ]));

        set("coor/x", -7120);
	set("coor/y", -2060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}