inherit ROOM;

void create()
{
        set("short", "林蔭道");
        set("long", @LONG
這是一條安靜的林蔭道，地上鋪着奇奇怪怪五顏六色的石子，向
東西兩頭延伸。東面就是熱鬧的南大街了。西邊有幾個小孩在玩耍，
安靜，和諧，微風吹來，使人忘卻了江湖上的生死情仇。
LONG );
        set("outdoors", "jingzhou");
        set("objects", ([
                "/d/beijing/npc/kid1" : 2,
        ]));
        set("exits", ([
                "eastup" : __DIR__"nandajie2",
                "west" : __DIR__"lydao3",
        ]));

        set("coor/x", -7110);
	set("coor/y", -2070);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}