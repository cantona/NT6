//Room: huanggong.c

inherit ROOM;

void create ()
{
        set ("short", "皇宮大殿");
        set("long", @LONG
皇宮大殿坐落全宮核心，左右是兩個偏殿，各有一條約二十丈長
的廊道相連，如兩邊飛出雁翼。兩個副殿，以左翼殿和右翼殿為名。
LONG );
        set("exits", ([
                "south"   : "/d/changan/bridge2",
                "north"   : "/d/changan/bridge1",
                "east"   : "/d/changan/fudian1",
                "west"   : "/d/changan/fudian2",
        ]));
        set("objects", ([
                "/d/changan/npc/shiwei" : 4,
                "/clone/npc/walker"  : 1, 
        ]));

        set("coor/x", -10720);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
}