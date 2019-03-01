// Room: /d/yanping/xiaoshuimen.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "東門");
        set("long", @LONG
東門慣稱“小水門”。因為東門下便是碼頭，百姓稱之“小水門”
是相對延津渡上延福門那個“大水門”而言的。延平城依山傍水，碼頭
都是大塊的花崗巖砌就，城牆就是大塊的青磚壘起來的了。東門外，一
座浮橋橫跨兩岸。
LONG );
        set("exits", ([
                "north"    : __DIR__"fengguanyan",
                "south"    : __DIR__"road1",
                "westup"   : __DIR__"meishanpo",
                "eastdown" : __DIR__"fuqiao1",
        ]));
        set("objects", ([
                "/d/city/npc/bing" : 1,
        ]));
        set("outdoors", "yanping");
        set("coor/x", 1520);
        set("coor/y", -6170);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}