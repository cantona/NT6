// Room: /d/songshan/taishique.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "太室闕");
        set("long", @LONG
嵩山古稱方外，又稱崇山，為五嶽中的中嶽，由太室少室二山沿綿
而成。漢武帝時稱“嵩高”，取自詩經“嵩嶽維高，峻極於天”，道教
以之為第六小洞天。闋高丈餘，南面刻“中嶽太室陽城”六字，篆文古
樸，蒼勁有力。向西就是去少室山少林寺的路。向北一里許便是中嶽廟
了。
LONG );
        set("exits", ([
                "north" : __DIR__"tianzhongge",
		"south" : "/d/kaifeng/shanlu2",
                "east"  : "/d/ruzhou/ximen",
                "west"  : "/d/shaolin/shijie1",
        ]));
        set("outdoors", "songshan");
        set("objects", ([
                __DIR__"npc/dizi" : 1,
                __DIR__"npc/seller" : 1,
                "/clone/npc/walker" : 1,
        ]));
        set("coor/x", 0);
        set("coor/y", 700);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
