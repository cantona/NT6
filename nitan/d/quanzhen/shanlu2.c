// shanlu2.c 山路
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
前面好像有一個大山谷，走到這裏，樹木多了些，全都是柏樹。
西面是一條彎曲的山路，隱藏在山間，要在夜裏還真看不出來。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "southwest" : __DIR__"shanlu1",
                "northup"   : __DIR__"cuipinggu",
        ]));
        set("objects", ([
                "/clone/medicine/vegetable/badou" : random(2),
        ]));

        set("coor/x", -3140);
        set("coor/y", 10);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}