#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "黃土路");
        set("long", @LONG
你走在一條蜿蜒的小路上。南邊翻個一個小高崗可以回到京城。
LONG );
        set("exits", ([
                "east" : __DIR__"road2",
        ]));

        set("outdoors", "beijing");
        setup();
}
void init()
{
        object me = this_player();
        message_vision(HIB "夜已經深了，翻過南邊的小高崗可以由小路返回京城。\n"NOR, me);
        remove_call_out("mes");
        call_out("mes",3,this_player());
        set_temp("want_leave", 1, this_player());
        add_action("do_leave", "leave");
}

void mes(object me)
{
        message_vision(HIR "你是否願意離開(leave)萬安寺？\n"NOR, me);
}

int do_leave()
{
        object me = this_player();
        if( query_temp("want_leave", me) )
        {
                tell_object(me, HIR "你決定離開萬安寺。\n" NOR);
                me->move("/d/heimuya/road3");
        }
        return 1;
}
