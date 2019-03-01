// wood.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(WHT "木材" NOR, ({ "wood", "mu cai", "mu", "cai" }) );
        set_weight(5000);
        if (clonep())
        {
                set_default_object(__FILE__);
        } else
        {
                set("value", 10);
                set("unit", "捆");
                set("long", "這是一小捆木材。\n");
        }
        setup();
}

int fire(object me, object ob)
{
        object fire;

        if( query_temp("warm", environment()) >= 40 )
                return notify_fail("這裡已經夠熱的了，你還是換個地方點火吧。\n");

        message_vision("$N用" + ob->name() + "點燃了" + name() +
                       "，一片紅紅的火光映紅了四周。\n", me);

        fire = new("/clone/misc/needfire");
        fire->move(environment(me));

        destruct(this_object());
        return 1;
}