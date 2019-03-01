// /d/shenlong/shanlu1 山路
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
腳下踏著細沙，聞到林中飄來的陣陣花香，真覺到了仙境。沿著山
間小路前行，耳邊傳來陣陣鳥叫，甚是清靜，你宛若置身于空明之中。
西面是海灘，北面是通向峰頂的山路，東南有條山溪。
LONG
        );
        set("outdoors", "shenlong");
        set("exits", ([
                "west"      : __DIR__"haitan",
                "north"     : __DIR__"shanlu2",
                "southeast" : __DIR__"shanxi",
        ]));
        set("snaketype", ({"yinhuan", "zsnake"}));
        setup();
}

#include "snakeroom.h";
