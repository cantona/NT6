inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_drink", "drink");
}

void create()
{
        set_name(HIC "玄" HIW "冰" HIC "碧" HIR "火"
                 HIC "酒" NOR, ({ "xuanbing jiu", "xuanbing", "jiu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "壺");
                set("long", HIC "這是一壺珍貴之極的玄冰碧火酒。\n" NOR);
                set("value", 50000);
        }
        setup();
}

int do_drink(string arg)
{
        object me = this_player();

        if (! arg || ! id(arg))
                return notify_fail("你要喝什麼東西？\n");

        if (me->is_busy())
                return notify_fail("急什麼，小心別噎着了。\n");

        message_vision(HIC "$N" HIC "一仰頭，將整瓶" + name() +
                       HIC "喝了下去。\n" NOR, me);

        if( !query("skybook/item/xuanbingjiu", me) )
        {
                message_vision(HIB "突然間$N" HIB "臉色忽的一變，冷不丁打"
                               "了幾個寒戰。\n" NOR, me);
                me->apply_condition("xuanbing-jiu", 50 + random(50));

        } else
        {
                message_vision(HIW "$N" HIW "一聲長吁，體內陰陽真氣相互交"
                               "替，白霧蒸騰而起。\n" NOR, me);

                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 100000);

                if (me->query_skill_mapped("force") == "luohan-fumogong"
                   && me->can_improve_skill("luohan-fumogong"))
                        me->improve_skill("luohan-fumogong", 100000);

                addn("skybook/item/xuanbingjiu", 1, me);

                me->start_busy(6);
        }
        destruct(this_object());
        return 1;
}