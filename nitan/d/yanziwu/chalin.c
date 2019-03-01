// Room: /d/yanziwu/chalin.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "茶花林");
        set("long", @LONG
一眼望將出去，都是紅白繽紛的茶花，不見房屋。回望水邊，小船
居然不知道什麼時候已經撐走了。看來，只有免力入林，一尋出路了。
LONG );
        set("outdoors", "mantuo");
        set("exits", ([
                "north" : __DIR__"chalin1",
        ]));
        set("objects", ([
                "/d/dali/obj/shanchahua" : 1,
        ]));
        set("coor/x", 1210);
        set("coor/y", -1300);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
