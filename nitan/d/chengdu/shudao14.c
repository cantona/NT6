#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蜀道");
        set("long", @LONG
你走在以險著稱天下的蜀道上，道路十分狹窄，西邊不遠有一座
高山。要去成都的話，必須翻過這座高山。四周一片荒涼，渺無人煙。
LONG );
        set("exits", ([
                  "westup" : __DIR__"shudao15",
                  "east" : __DIR__"shudao13",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");

        set("coor/x", -15110);
	set("coor/y", -1830);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}