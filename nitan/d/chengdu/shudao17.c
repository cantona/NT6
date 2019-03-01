#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蜀道");
        set("long", @LONG
你走在以險著稱天下的蜀道上，道路由東上山，異常難行。由西
而下，然而上山容易下山難，也不見得好走，總之走在這樣的路上非
要格外小心，用盡全身氣力才行。不多一會兒，你就覺得筋疲力盡了。
LONG );
        set("exits", ([
                  "westup" :  __DIR__"shudao18",
                  "eastdown" : __DIR__"shudao16",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");

        set("coor/x", -15140);
	set("coor/y", -1830);
	set("coor/z", -10);
	setup();
}

int init()
{
        object me;
        int i;
        me = this_player();
    i=query("max_qi", me)/50;
        me->receive_damage("qi", i);
        tell_object(me, HIR "你費力的走在蜀道上，累的氣喘吁吁。\n" NOR);
}