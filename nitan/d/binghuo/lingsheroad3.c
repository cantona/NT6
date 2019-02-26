// Room: /binghuo/lingsheroad3.c
// Date: Oct.28 1999 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
你走在樹林中的小路上，四周僻靜得讓你感到窒息般的異常。密
密層層的樹林遮天蔽日，你甚至聽不到一點蟲鳴。山頂有座小屋島。
LONG );
        set("outdoors", "lingshe");
        set("no_clean_up", 0);
        set("exits", ([
                "westdown"  : __DIR__"lingsheroad2",
                "northup"   : __DIR__"lingshetop",
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        if (random(2) == 1)
        {
                me->receive_damage("qi", 10);
tell_object(me, HIR"忽然一陣刺痛，"NOR"你一腳踩在鋼針上了，不禁破口大罵：
“他媽的！哪個王八蛋乾的？！”\n");
        }
        return ::valid_leave(me, dir);
}
