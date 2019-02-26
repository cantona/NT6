// Room: /d/kunlun/hmszhuang.c
// Last Modified by winder on Jun. 29 2001

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIR"紅梅莊門"NOR);
        set("long", @LONG
這是一座頗大的莊子。一眼看去就知道此間主人是當地的富豪，在
崑崙山中有這麼大的一座山莊確實非常少見。相傳，此間主人也是武林
中人，所以路過之人也不敢隨意的進入，當以江湖之禮求見。
LONG        );
        set("exits", ([ /* sizeof() == 2 */
                "north"    : __DIR__"hmszdating",
                "eastdown" : __DIR__"hmszroad2",
                "westdown" : __DIR__"shanxi",
        ]));
        set("objects",([
                __DIR__"npc/yao" : 1,
        ]));
        set("outdoors", "hongmei");
        set("coor/x", -90030);
        set("coor/y", 10010);
        set("coor/z", 50);

        setup();
        replace_program(ROOM);
}