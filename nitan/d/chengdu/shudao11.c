#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蜀道");
        set("long", @LONG
你走在以險著稱天下的蜀道上，從這裏向西越過高山，就可以進
入四川盆地了，東邊是去風景優美的三峽。道路十分崎嶇，時而左轉
時而上山，時而又要穿過森林。
LONG );
        set("exits", ([
                "east" : __DIR__"baidicheng",
                  "west" : __DIR__"shudao12",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");

        set("coor/x", -15080);
	set("coor/y", -1830);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}