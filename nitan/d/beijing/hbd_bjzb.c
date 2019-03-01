//hbd_bjzb.c
#include <ansi.h>

inherit ROOM;

#define PLACE "bje"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", HIB"黑白道總壇"NOR);
        set("long", @LONG
這裡就是黑白道北京城東總壇，這裡居然是一間完全封閉的房間！
牆壁也異常的的奇怪，居然一半是黑色一半是白色，正中站著一個長
發怪人，黑白分明的身體，與周圍的環境搭配在一起，給人莫名其妙
的恐懼感。房間正中的台子上放著一個黑白令旗。對面的牆上掛著任
務牌(paizi)。
LONG );

        set("objects", ([ 
               "/d/beijing/npc/boss-heibai"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([ 
                "out"   : "/d/beijing/yancao",
        ]));

        setup();
}
#include <bang_bad.h>
