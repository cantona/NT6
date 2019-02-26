#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",  "北大街" );
        set("long", @LONG
你走在北大街上，這裏來往的人很少，正北面一座雄偉的
大門，那就是平西王吳三桂的官邸了。路的兩旁整齊的種着大
樹，顯得十分漂亮。不時會有幾個衞兵來回走動。
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "south" : __DIR__"jinrilou",
                "north" : __DIR__"wangfu",
        ]));
        set("objects", ([
                "/d/beijing/npc/boy2" : 1,
        ]));
	set("coor/x", -16840);
	set("coor/y", -7200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
       
}