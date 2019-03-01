// Room: /d/kunlun/hmsznuange.c
// Last Modified by winder on Jun. 29 2001

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"暖閣"NOR);
        set("long", @LONG
昆侖山中一向極為寒冷，但在此暖閣之中卻溫暖如春，可又不見何
處生著炭火，此間取暖方法當真巧妙無比。閣中陳設輝煌燦爛，榻上椅
上都舖著錦緞軟墊，極是富麗豪華。南邊是大廳。
LONG        );
        set("exits", ([ /* sizeof() == 1 */
                "south" : __DIR__"hmszdating",
        ]));
        set("objects",([
                __DIR__"npc/zhu1"   : 1,
                __DIR__"npc/yahuan" : 1,
        ]));
        set("coor/x", -90030);
        set("coor/y", 10030);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}