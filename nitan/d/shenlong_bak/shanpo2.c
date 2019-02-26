// /d/shenlong/shanpo2 山坡2
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "山坡");
        set("long", @LONG
這是一個山坡，通向北方的一座山峯，你已經爬的氣喘噓噓了，真
想停下來休息休息，突然間，你看見樹上、草上、路上，東一條，西一
條全是毒蛇，可怕極了！... 是非之地，不可久留，還是趕快離開吧。
北面是一個狹窄的山道，往南是一個山坡。
LONG
        );
        set("outdoors", "shenlong");
        set("exits", ([
                "northup"   : __DIR__"shandao",
                "southdown" : __DIR__"shanpo1",
        ]));
        set("snaketype", ({"jinhuan", "yinhuan"}));
        setup();
}

#include "snakeroom.h"
