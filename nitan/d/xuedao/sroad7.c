#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "大雪山口");
        set("long", @LONG
羣山環繞，四周積雪終年不化。南邊不遠處有一個山谷。
LONG );
        set("exits", ([
                "north"     : __DIR__"sroad6",
                "southdown" : __DIR__"sroad8",
        ]));
        set("objects", ([
                __DIR__"npc/caiyaoren": 1,
        ]));
        set("outdoors", "xuedao");
        setup();
}

int valid_leave(object me, string dir)
{
        if (! playerp(me))
                return ::valid_leave(me, dir);

        if (dir == "southup")
        {
                message_vision(HIW "\n突然間只聽得轟隆一聲巨響，$N" HIW
                               "腳下踏了個空，竟然是雪崩了！\n" NOR, me);

                if (me->query_dex() / 2 + random(me->query_dex()) < 13)
                {
                        me->receive_damage("qi", 70);
                        me->receive_wound("qi", 70);
                }

                tell_object(me, HIW "只見大片的積雪從山峯上奔騰而下，鋪"
                                "天蓋地撲來，沿途並夾\n帶了不少巖石。趕"
                                "緊逃命吧！\n\n" NOR);

                if (me->query_dex() / 2 + random(me->query_dex()) >= 15)
                {
                        me->move(__DIR__"sroad8");
                        return -1;
                } else 
                {
                        me->move(__DIR__"sroad5");
                        return -1;
                }
        }
        return ::valid_leave(me,dir);
}
