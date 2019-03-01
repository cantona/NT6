#include <ansi.h> 

inherit ROOM;

void create()
{
        set("short", HIM "桃花峪" NOR);
        set("long", @LONG
你走在兩山相夾的峽谷中，山上山下全是無邊的野桃樹，一陣山
風吹來，落英繽紛。數百年落下的桃花，桃枝都堆積在地上，人走在
上面軟軟的。日近正午了，遠處的山林之間似乎飄盪著一股輕霧，越
來越濃。
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "east" : __DIR__"wdsl1",
                "northwest" : __DIR__"xiao3",
        ]));

        setup();
}

int valid_leave (object who, string dir)
{
        if (dir == "northwest")
                return ::valid_leave(who, dir);
        else
        {
                if (userp(who)
                    && query("family/family_name", who) != "五毒教" )
                {
                        if (! (present("xingjun san", who))
                            && query("max_neili", who)<1000 )
                        {
                                message_vision (HIM "只聞一陣濃鬱的香氣襲來……$N"
                                                HIM "頓時覺得頭重腳輕。\n" NOR, who);
                                who->receive_damage("qi", 50);
                                remove_call_out ("fall_down");
                                call_out ("fall_down", 1, who, environment(who));
                                who->start_busy(1, 1);
                                return notify_fail(HIR "你禁不住踉蹌了幾下，兩腿突然"
                                                   "一軟。\n\n" NOR);
                        } 
                }
                return 1;
        }
}

void fall_down (object who, object where)
{
        who->move(where);
        this_player()->unconcious();
}

void fall_down1 (object who, object where)
{
        this_player()->unconcious();
}
