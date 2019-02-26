// /d/xingxiu/mogaoku.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "莫高窟");
        set("long", @LONG
這裏牆壁上繪製着與佛教相關的畫面，有仙女飛天，還有反彈琵琶。
洞中還有很多佛像和經書。你被這些瑰麗的文化之寶驚呆了。
LONG );
        set("exits", ([ 
             "out" : __DIR__"yueerquan",
        ]));
        set("objects", ([ 
                "/d/shaolin/obj/fojing1"+random(2) : random(2),
                "/d/shaolin/obj/fojing2"+random(2) : random(2),
        ]));
        set("coor/x", -20310);
        set("coor/y", 170);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}
