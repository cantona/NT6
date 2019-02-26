#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "棧道");
        set("long", @LONG
自古有云：蜀道難，難於上青天，嗚呼。無怪大詩人李白如此寫。
路到了這裏真可謂驚險無比，一邊是滔滔的江水，一邊是如刀切般的
峭壁，朝西已無路可走，只有峭壁上有一些石窩，可以攀登而上，向
東，卻是搖搖晃晃的棧道。 
LONG );
        set("exits", ([
                "east" : __DIR__"shudao6",
                "westup" : __DIR__"shudao8",
        ]));
        set("objects", ([
                "/d/beijing/npc/tangzi" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("coor/x", -15050);
	set("coor/y", -1830);
	set("coor/z", -60);
	setup();
        replace_program(ROOM);
}