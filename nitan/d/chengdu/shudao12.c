#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蜀道");
        set("long", @LONG
你走在以險著稱天下的蜀道上，道路十分狹窄，這裡不時會有強
盜出沒，來往的人很少，舉目看去，方圓幾百裡內沒有人煙，你還是
加快步子走吧。
LONG );
        set("exits", ([
                  "east" : __DIR__"shudao11",
                  "west" : __DIR__"shudao13",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");

        set("coor/x", -15090);
	set("coor/y", -1830);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}