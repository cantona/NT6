// Room: /d/mobei/boershu.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "博爾術營帳");
        set("long", @LONG
博爾術勇力過人，被稱為蒙古人中的英雄，年輕時曾同鐵木真一起
追殺馬盜，他的營帳中只是幾條氈子隨便堆放，一杆長槍，一把鐵胎弓，
外加九壺鐵箭，博爾術箭法神通，上陣帶箭之多，無人可及。
LONG
        );
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/boerhu" : 1,
        ]));
        set("exits", ([ /* sizeof() == 1 */
                "north" : __DIR__"road3",
        ]));

        set("coor/x", -220);
        set("coor/y", 5230);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}