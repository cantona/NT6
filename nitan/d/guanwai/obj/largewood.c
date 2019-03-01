// largewood.c

#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(WHT "大木材" NOR, ({ "large wood", "wood" }));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "批");
                set("long", "這是伐自長白山的上好的大木料。\n");
                set("base_value", 2000);
                set("base_unit", "根");
                set("base_weight", 50000);
        }
        set_amount(1);
}

int fire(object me, object ob)
{
        object fire;

        if (query_amount() < 1)
                return 0;

        if( query_temp("warm", environment()) >= 40 )
                return notify_fail("這裡已經太熱了，你還是換個地方點火吧。\n");

        message_vision("$N費了好大勁，總算用" + ob->name() + "把" + name() +
                       "點著了，一片紅紅的火光映紅了四周。\n", me);

        fire = new("/clone/misc/needfire");
        fire->move(environment(me));
        fire->set_light_time(100);

        add_amount(-1);
        return 1;
}