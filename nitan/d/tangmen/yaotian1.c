//yaotian1
#include <ansi.h>
inherit ROOM;

int do_zhao(string arg);

void create ()
{
        set ("short", "藥圃");
        set ("long", @LONG
這裏是唐門毒藥房的藥圃。這裏的空氣中飄蕩着一股異香，聞到
這種氣味，你只覺得頭有一些發昏，採完藥還是趕快離開吧。
LONG);
        set("area","tangmen");
        set("outdoors", "tangmen");
        set("exits", ([
                "north" : __DIR__"yaotian4",
                "east" : __DIR__"yaotian2",
        ]));
        set("yao", 5);
        setup();
}

void init()
{
        add_action("do_zhao","zhao");
}

int do_zhao(string arg)
{
        object me;
        int jingli_cost;

        me = this_player();
        jingli_cost = (-1) * (5 + random(15));

        if ( !arg || ( arg != "yao" ) )
                return notify_fail("你想幹什麼？\n");

        if( query_temp("find", me) )
                return notify_fail("你已經找到了一株草藥，可以交差了！\n");

        if( query("jingli", me) <= (-jingli_cost) )
                return notify_fail("你太疲勞了，沒有精力再找藥了。\n");

        if ( (int)query("yao") >= 1 )
        {
                message_vision(YEL"$N蹲下身來，小心翼翼的在花圃中尋找着藥草。\n"NOR, me);
                if( random(1+query("kar", me)-10) >= 3 )
                {
                        message_vision(HIG"$N不斷的撥動着花圃中的草藥，終於找到了一株。\n$N將這株藥草小心的收在懷中。\n"NOR, me);
                        new(__DIR__"obj/caoyao")->move(me);
                        set_temp("find", 1, me);
                }

                addn("jingli", jingli_cost, me);
                addn("yao",-1);
        }
        else
                return notify_fail("這裏都已經被翻遍了，沒有什麼可找的了。\n");

        return 1;
}