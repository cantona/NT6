// Room: /d/gumu/tree.c
// Last Modifyed by Winder on Jan. 14 2002
 
#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", HIG"樹上"NOR);
        set("long", @LONG 
這裏是樹上，你突然發現樹葉中有些動靜，哇。。。。。。！！！
毛骨悚然！一條碗口粗細的巨蟒倒懸在樹幹上，張開大口，正要向你撲
來！
LONG        );
        set("outdoors", "gumu");
        set("objects",([
                __DIR__"npc/dumang" : 1,
        ]));
        set("exits", ([ 
                "down" : __DIR__"xuanya",
        ]));
        set("coor/x", -3220);
        set("coor/y", 40);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}
