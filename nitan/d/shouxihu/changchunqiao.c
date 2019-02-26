// Room: /yangzhou/changchunqiao.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","長春橋");
        set("long",@LONG
長春橋以青石塊堆砌，橋身亞於大虹橋，而形制相似，距虹橋約裏
許，置短板立柱橋欄。二橋南北相望，為陸行上蜀岡要道。
LONG );
        set("outdoors", "shouxihu");
        set("exits", ([
                "west"     : __DIR__"shuiyun",
                "eastup"   : __DIR__"changchunling",
        ]));
        set("objects", ([
                "/d/city/npc/popo" : 1,
        ]));
        set("coor/x", 0);
        set("coor/y", 110);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}