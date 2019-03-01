//hbd_cafb.c
#include <ansi.h>

inherit ROOM;

#define PLACE "ca"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", HIB"黑白道長安分壇"NOR);
        set("long", @LONG
這裡就是黑幫組織黑白道的長安分壇了。牆壁是奇特的黑白兩色。
房間正中的台子上擺著一把劍一把刀，可以看出此處的分壇主必定是
個痴迷武學之人。牆上掛著一個牌子（paizi）。
LONG );

        set("objects", ([ 
               __DIR__"npc/hbd_chengwu"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([ 
                "out"   :  __DIR__"miao",
        ]));

        setup();
}
#include <bang_bad.h>
