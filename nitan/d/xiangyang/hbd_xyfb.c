//hbd_xyfb.c
#include <ansi.h>

inherit ROOM;

#define PLACE "xy"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", HIB"黑白道襄陽分壇"NOR);
        set("long", @LONG
這裏就是黑幫組織黑白道的襄陽分壇了，牆壁是奇特的黑白兩色，
地上卻鋪着華麗的地毯，正中的太師椅上的白虎皮也顯示出這裏的主
人必定愛慕榮華富貴。牆上掛着個牌子（paizi）。
LONG );

        set("objects", ([ 
               __DIR__"npc/hbd_jiabj"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([ 
                "out"   :  __DIR__"hutong2",
        ]));

        setup();
}
#include <bang_bad.h>
