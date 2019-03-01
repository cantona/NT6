// /d/shenlong/shanpo1 山坡1
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "山坡");
        set("long", @LONG
這是一個山坡，通向北方的一座山峰，坡很陡，輕功不好的人爬起
來就更加費力。突然間，你看見樹上、草上、路上，東一條，西一條全
是毒蛇，可怕極了！北面是另一個山坡，往南是一條山路。
LONG
        );
        set("outdoors", "shenlong");
        set("exits", ([
                "northup"   : __DIR__"shanpo2",
                "southdown" : __DIR__"shanlu2",
        ]));
        set("snaketype", ({"jinhuan", "fushe"}));
        setup();
}

#include "snakeroom.h";
