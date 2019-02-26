#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", HIY"十三皇陵"NOR);
        set("long", @LONG
這裏就是著名的明十三皇陵，相當的宏偉壯觀。十三皇陵坐落於
紫禁城的西郊，在這裏遊玩觀賞的遊人甚多。
LONG );
        set("exits", ([
                "south" : "/d/beijing/guandao_2",
        ]));
        set("objects", ([
                "/d/beijing/npc/youren" : 2,
               "/clone/npc/walker"  : 1, 
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}