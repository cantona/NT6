#include <ansi.h>

inherit ROOM;

#define PLACE "dl"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "小刀會");
        set("long", @LONG
這裡就是小刀會設在大理的分舵，這裡看起來混亂無比，一只破
木箱上擺著幾樣粗制的賭具，地上亂扔著些雞骨頭，空氣中有一股雞
香、酒香和汗臭混雜在一起的味道。一看就知道是地痞流氓的聚集地。
側面的牆上掛著任務牌（paizi）。
LONG );

        set("objects", ([
               "/d/dali/npc/boss-long"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "up" : "/d/dali/baiyiminju",
        ]));

        setup();
}
#include <bang_bad.h>
