// Room: /d/kunlun/houyuan.c
// Last Modified by winder on Nov. 14 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "後院");
        set("long",@long
由于這裡一向少有人來，漸漸被人忘記，也就很久沒有被打掃過了。
落葉滿地，踩上去軟綿綿的。牆壁已有些殘破，檐下結滿了蜘蛛網，角
落裡的一扇小門因為日曬雨淋，開始朽爛。
long);
        set("exits",([
                "out"   : __DIR__"fufengshan",
                "south" : __DIR__"shanlin2",
        ]));
        set("no_clean_up", 0);
        create_door("out", "小門", "enter", DOOR_CLOSED);
        set("outdoors", "kunlun");
        set("coor/x", -119980);
        set("coor/y", 40160);
        set("coor/z", 90);
        setup();
}
