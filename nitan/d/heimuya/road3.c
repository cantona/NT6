// road3.c
// by Xiang

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "黃土路");
        set("long", @LONG
你走在一條黃土路上。西面望去，隱隱可以看到平定州。望東，
北京城快到了。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
                "east" : "/d/beijing/ximenwai",
                "west" : __DIR__"pingdingzhou",
        ]));
        setup();
}

void init()
{
        object me = this_player();
        if (!objectp(me) || !userp(me)) return;
        message_vision(HIB "夜已經深了，翻過北邊的小高崗可以由小路到萬安寺。\n"NOR, me);
        remove_call_out("mes");
        call_out("mes",3,this_player());
        set_temp("want_enter", 1, this_player());
        add_action("do_enter", "enter");
}

void mes(object me)
{
        if (!me) return;
        if (environment(me) == this_object())
        message_vision(HIR "你是否願意進入(enter)萬安寺？\n"NOR, me);
} 

int do_enter()
{
        object me = this_player();
        if( query_temp("want_enter", me) )
        {
                tell_object(me, HIR "你決定進入萬安寺。\n" NOR);
                me->move("/d/tulong/yitian/was_damen");
        }
        return 1;
}