// Room: /yangzhou/changdi3.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short", "柳岸長堤");
        set("long", @LONG
長堤遍植楊柳，間以桃花。堤側是盈盈西湖水，草長鶯飛時節，紅
男綠女，相約其間，長堤柳絲拂水，風情萬種。北去是平山塢，南邊是
望春樓。
LONG );
        set("outdoors", "shouxihu");
        set("objects", ([
                "/d/village/npc/girl" : 2,
        ]));
        set("exits", ([
                "north" : __DIR__"pingshanwu",
                "south" : __DIR__"wangchunlou",
        ]));
        set("coor/x", -30);
        set("coor/y", 110);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}