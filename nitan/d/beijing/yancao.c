#include <room.h>
inherit ROOM;

void create()
{
        set("short", "煙草店");
        set("long", @LONG
從雲南運來的煙土在這裏可以説是最佳的商品，他的利潤是成百
成千倍的翻了上去，北京現在最流行的送禮的方式就送煙。但是永遠
記住吸煙是有害健康的，所以這裏的老闆被雞蛋打在頭上。發昧心財
的人總是被人唾罵的。
LONG );
       set("exits", ([
                "north" : "/d/beijing/caroad_e2",
        ]));
        set("objects", ([
                "/d/beijing/npc/old2" : 1,
        ]));
        set("outdoors", "beijing");
        set("no_fight",1);
	set("coor/x", -2770);
	set("coor/y", 7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}