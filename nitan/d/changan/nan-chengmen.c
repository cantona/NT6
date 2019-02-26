//Room: nan-chengmen.c

inherit ROOM;

void create ()
{
        set ("short", "長安南城門");
        set("long", @LONG
長安城的南城門。這裏的護城河既深又闊，而且城高牆厚，有一
夫當關，萬夫莫開之勢，城內還駐紮了兩營士兵，遠看軍營延綿，旌
旗似海，頗具懾人之勢，仰望城樓，只見城樓高處滿布哨兵，劍拔駑
張，士氣昂揚，從這裏出去不遠就是兵家要地武功鎮。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "south" : "/d/changan/road5",
                "north" : "/d/changan/nanan-daokou",
        ]));
        set("objects", ([ //sizeof() == 3
                "/d/changan/npc/wujiang" : 1,
                "/d/changan/npc/guanbing": 2,
                "/clone/npc/walker"  : 1,
        ]));

        set("outdoors", "changan");
        set("coor/x", -10720);
	set("coor/y", 1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}