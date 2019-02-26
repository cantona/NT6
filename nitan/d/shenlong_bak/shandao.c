// 山道 /d/shenlong/shandao
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "山道");
        set("long", @LONG
轉過兩個山坡，你已行走在一個山道之中，山道的北面是峯頂，向
下是山坡。抬頭遙見峯頂建着幾座大竹屋，耳邊隱隱約約傳來「鏘鏘」
的刀劍撞擊聲和有人高聲喧譁的聲音，看來離山頂不遠了。山道狹窄，
只能容一人通過。
LONG
        );
        set("outdoors", "shenlong");
        set("exits", ([
                "northup"   : __DIR__"fengding",
                "southdown" : __DIR__"shanpo2",
        ]));
        set("objects", ([
                __DIR__"npc/old" : 1,
        ]));
        set("snaketype", ({"snake", "fushe"}));
        setup();
}

#include "snakeroom.h";
