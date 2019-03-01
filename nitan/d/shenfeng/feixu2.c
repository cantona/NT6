inherit ROOM;

#include "langqun.h"

void create()
{
        set("short", "高昌廢墟");
        set("long", @LONG
站在這裡一眼望去，高高矮矮的房子櫛比鱗次，可是聲息
全無，甚至雀鳥啾鳴之聲亦絲毫不聞。如此可怖的景象，寂靜
的氣勢使人連大氣也不敢喘上一口。一片寂靜之中，遠處忽然
傳來隱隱的狼嗥。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([ 
                "east" : __DIR__"feixu1",
                "west" : __DIR__"pendi",
                "north" : __DIR__"xiaowu",
        ]));

        setup();
}