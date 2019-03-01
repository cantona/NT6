#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIC "江中鐵索" NOR);
        set("long", @LONG
你站在一江水之中的一條鐵索上，鐵索隨水起伏不停，你站在這
裡，若沒頂尖的輕功，是堅持不了多久的。從這裡向江中看去，更覺
得氣勢宏大，江水奔流，向江心看去，好象水低有一些古怪的東西。
LONG );
        setup();
} 

void init()
{
        add_action("do_jump", "jump");
}

int do_jump (string arg)
{
         object me = this_player();
        if (! arg || arg == "") return 0;
        if (arg == "down")
        {
                if(! random(10)) 
                {
                        set_temp("die_reason", "跳河死了", me);
                        me->die();
                } else
                {
                        tell_object(me, "你奮不顧身的跳進了江中，一陣江水湧來……\n");
                        me->move(__DIR__"river");
                         me->unconcious();}
                        return 1;
                }        
        else
        return notify_fail("你要做什麼？\n");
}