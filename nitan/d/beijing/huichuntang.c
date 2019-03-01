#include <room.h>
inherit ROOM;

void create()
{
        set("short", "回春堂藥店");
        set("long", @LONG
回春堂藥店是整個北京城裡最大最有名氣的藥舖。你還沒走進這
裡，便聞到一股濃濃的藥材氣味，那是從藥櫃上的幾百個小抽屜裡散
發出來的。一位伙計在櫃台後站著，堆著笑臉招呼著客人。
LONG );
       set("exits", ([
                "west" : "/d/beijing/xi_2",
                "east" : "/d/beijing/liandan_neiting",
        ]));
        set("objects", ([
                "/d/beijing/npc/kid1" : 1,
                "/d/beijing/npc/yaopuhuoji" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2810);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}