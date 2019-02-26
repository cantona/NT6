// /d/shenlong/houshan 後山
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "後山");
        set("long", @LONG
這裏是後山，人跡罕至，雜草叢生，前面的路越來越小，路上還有
什麼動物爬過的痕跡，你越走越害怕，不時回頭。突然，你看見草堆中
似乎有一個洞，但是又看不太清楚。
LONG
        );
        set("outdoors", "shenlong");
        set("exits", ([
                "southdown" : __DIR__"kongdi",
                "northdown" : __DIR__"luanshi",
        ]));
        set("snaketype", ({"mangshe"}));
        setup();
}

#include "snakeroom.h";
