// /d/shenlong/shanqiu 山丘
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "山丘");
        set("long", @LONG
這是一片山丘地，地上滿是樹葉和黃土，由於剛下過雨，地面十分
泥濘，突然，你發現地上有許多蛇蟲爬行的痕跡，粗細不均，小的有如
筷子，大的確似車轍，你不由得渾身起了一層雞皮疙瘩。北面是一片果
園。
LONG
        );
        set("outdoors", "shenlong");
        set("exits", ([
                "north"     : __DIR__"guoyuan",
                "southwest" : __DIR__"shanlu2",
        ]));
        set("snaketype", ({"yinhuan"}));
        setup();
}

#include "snakeroom.h";
