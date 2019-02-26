#include <ansi.h>

inherit ROOM;

#define PLACE "hz"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "小刀會");
        set("long", @LONG
這裏就是小刀會設在杭州的分舵，這裏看起來混亂無比，一隻破
木箱上擺着幾樣粗製的賭具，地上亂扔着些雞骨頭，空氣中有一股雞
香、酒香和汗臭混雜在一起的味道。一看就知道是地痞流氓的聚集地。
側面的牆上掛着任務牌（paizi）。
LONG );

        set("objects", ([
                __DIR__"npc/boss-ma"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "out" : __DIR__"guozhuang",
        ]));

        setup();
}
#include <bang_bad.h>
