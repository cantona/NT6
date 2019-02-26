// Room: /d/songshan/cangku.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;
#include <room.h>

void create()
{
        set("short", "倉庫");
        set("long", @LONG
這是一個倉庫，四周密不透風。你一進門便聞到一股黴味，滿屋的
灰塵，成堆成堆的物品快堆滿了整間房間。
LONG );
        set("exits" , ([
                "north" : __DIR__"westting",
        ]) );
        set("objects" , ([
                ARMOR_DIR+"beixin" : 1,
                ARMOR_DIR+"huwan" : 1,
                ARMOR_DIR+"huxin" : 1,
                ARMOR_DIR+"huyao" : 1,
                ARMOR_DIR+"huzhi" : 1,
                ARMOR_DIR+"niupi" : 1,
                ARMOR_DIR+"shadai" : 1,
                ARMOR_DIR+"tengjia" : 1,
                ARMOR_DIR+"tiejia" : 1,
        ]) );
        set("no_clean_up", 0);
        set("coor/x", -40);
        set("coor/y", 890);
        set("coor/z", 90);
        setup();
        create_door("north" , "木門", "south" , DOOR_CLOSED);
}