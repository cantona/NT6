#include <ansi.h>

inherit ROOM;

#define PLACE "xy"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "俠義盟襄陽總舵");
        set("long", @LONG
這裡是俠義盟在襄陽的總部大廳。這裡沒什麼豪華的裝飾，一切
清新素樸。正廳上方高高的懸掛著一塊大匾上書俠之大者四個金煌煌
的大字。匾下的太師椅上端坐著一位威嚴的中年男子，想必就是成中
岳，成大當家。他與郭靖一樣都是令世人景仰的大俠。牆上掛著一個
任務牌(paizi)，你可以在這裡領到各種任務。
LONG );

        set("objects", ([
               __DIR__"npc/boss-cheng"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "south" : __DIR__"xym_zb",
        ]));

        setup();
}
#include <bang_good.h>
