#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "林間小道");
        set("long", @LONG
你走在一條頗為陰暗的林間小道上，兩旁是陰森森的密樹林。向
南不遠便可到達日月神教下第一大堂風雷堂的大門，這裡不時有風雷
堂的弟子走動。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
                "north" : __DIR__"linjxd2",
                "south" : __DIR__"fenggate",
        ]));
        set("objects", ([
                __DIR__"npc/dizi3" : 1,
        ]));
        setup();
        replace_program(ROOM);
}