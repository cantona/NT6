#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + WHT "幹柴" NOR, ({ "gan chai", "gan", "chai" }));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "捆");
                set("long", WHT "這是一捆木柴。\n" NOR);
                set("value", 10);
                set("material", "wood");
        }
}

int fire(object me, object ob)
{
        object fire;

        if( query_temp("warm", environment()) >= 40 )
                return notify_fail("這裡已經夠熱的了，你還是換個"
                                   "地方點火吧。\n");

        message_vision("$N用" + ob->name() + "點燃了" + name() +
                       "，一片紅紅的火光映紅了四周。\n", me);

        fire = new("/clone/misc/needfire");
        fire->move(environment(me));

        destruct(this_object());
        return 1;
}