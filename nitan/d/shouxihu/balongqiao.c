// Room: /yangzhou/balongqiao.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","八龍橋");
        set("long",@LONG
吹台和小金山之間是一段柳岸長堤，長堤中段架有兩側雕塑八龍頭
花崗巖橋，這就是八龍橋。
LONG );
        set("outdoors", "shouxihu");

        set("exits", ([
                "north"   : __DIR__"chuitai",
                "southup" : __DIR__"changchunling",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 0);
        set("coor/y", 120);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}