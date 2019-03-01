// Room: /binghuo/xianjing.c
// Date: Oct.28 1999 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "陷阱");
        set("long", @LONG
深坑底窄口廣，深達五丈，坑底周圍插上削尖的木棒。更在坑邊
堆了不少大石，只待人落入坑中，便可投石砸打。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "up"   : __DIR__"inhole1",
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        if (random((int)me->query_skill("dodge")) <= 20)
        {
                me->receive_wound("qi",30);
                return notify_fail("你使勁兒一蹦，離頂還有數丈遠就掉了下來，摔的鼻青臉腫。\n");
        }
        if (random((int)me->query_skill("dodge")) <= 35) 
        {
                me->receive_wound("qi",20);
                return notify_fail("你奮力一躍，卻離頂還有一丈多遠，看來是白費力氣。\n");
        }
        if (random((int)me->query_skill("dodge")) <= 60)
        {
                me->receive_wound("qi",10);
                return notify_fail("你縱身而起，離頂只差一點點了，再加把勁。\n");
        }

        return ::valid_leave(me, dir);
}

