// Room: /d/kunlun/keting1.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "客餐廳");
        set("long",@long
這裏是待客餐廳，裏面簡單，只有一些椅子和桌子，桌子上擺着些
茶和點心供客人食用。不少江湖人士不遠千里來到這裏，往往先到這裏
歇息片刻，恢復一下。
long);
        set("exits",([
                "west" : __DIR__"elang02",
        ]));
        set("objects",([
                __DIR__"obj/rice" : 2,
                __DIR__"obj/xiangcha" : 1,
        ]));
        set("coor/x", -119960);
        set("coor/y", 40060);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}