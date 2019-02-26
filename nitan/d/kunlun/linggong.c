// Room: /d/kunlun/linggong.c
// Last Modified by winder on Jun. 29 2001

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIR"靈獒宮"NOR);
        set("long", @LONG
你來到一座大廳之外，只見廳上扁額上寫着“靈獒宮”三個血紅大
字。一進廳，你便吃了一驚，但見三十餘頭雄健猛惡的大犬，分成三排
蹲在地上，一個身穿白孤裘的女郎坐在一張虎皮椅上，她手執皮鞭，正
在指揮惡犬咬人。南邊是一個大院子。
LONG        );
        set("exits", ([ /* sizeof() == 1 */
                "south" : __DIR__"hmszhouyuan",
        ]));
        set("objects",([
                __DIR__"npc/goupu" :  1,
                __DIR__"npc/dog"   :  1,
                __DIR__"npc/dog1"  :  1,
                __DIR__"npc/dog2"  :  1,
                __DIR__"npc/dog3"  :  1,
        ]));
        set("coor/x", -90020);
        set("coor/y", 10030);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}