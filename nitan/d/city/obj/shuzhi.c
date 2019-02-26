// shuzhi.c

#include <weapon.h>
#include <ansi.h>

inherit STAFF;

void create()
{
        set_name(GRN"大樹枝"NOR, ({ "shu zhi"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
        set("long", "這是一根爬山用的樹枝。\n");
        set("value", 50);
                set("material", "wood");
                set("wield_msg", "$N拿出一根$n，握在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }

        init_staff(5);
        setup();
}

int fire(object me, object ob)
{
        object fire;

        if( query_temp("warm", environment()) >= 40 )
                return notify_fail("這裏已經夠熱的了，你還是換個地方點火吧。\n");

        message_vision("$N用" + ob->name() + "點燃了" + name() +
                       "，一片紅紅的火光映紅了四周。\n", me);

        fire = new("/clone/misc/needfire");
        fire->move(environment(me));

        destruct(this_object());
        return 1;
}