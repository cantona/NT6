#include <ansi.h>
#include <weapon.h>

inherit STAFF;

void create()
{
        set_name(YEL "水煙筒" NOR, ({"yan tong", "yan", "tong"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "這是一支雲南人喜愛的水煙筒。你可"
                            "以用(fire)來吸煙。\n" NOR);
                set("unit", "個");
                set("value", 100);
                set("material", "steel");
                set("wield_msg", "$N從身後抽出$n握在手中當做武器。\n");
                set("unwield_msg", "$N將手中的$n放了回去。\n");
        }
        init_staff(10);
        setup();
}

int init()
{
        add_action("do_fire", "fire");
}

int do_fire(string arg)
{        
        object me = this_player();
        object ob = present("shui yan", me);

        if (arg != "yan" || ! arg)
                return notify_fail("你要幹什麼？\n");

        if (me->is_busy())
                return notify_fail("慢慢吸，小心別嗆著了。\n");

        if (! objectp(ob))
                return notify_fail("你已經沒有煙了。\n");

        message_vision(HIW "$N" HIW "拿起水煙筒咕咕的吸了幾口，緩緩"
                       "的吐出煙霧，只覺的精神好多了。\n" NOR, me);
        addn("jing", 50, me);
        if( query("jing", me)>query("max_jing", me)*2 )
        set("jing",query("max_jing",  me)*2, me);
        me->start_busy(2);
        destruct(ob);

        return 1;
}

        