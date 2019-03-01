#include <ansi.h>
#include "pill.h"

void create()
{
        set_name(HIC "養生丹" NOR, ({ "yangsheng dan", "yangsheng", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "以名貴藥材精煉而成，乃是高麗國的貢物。\n" NOR);
                set("base_unit", "粒");
                set("base_value", 10000);
                set("base_weight", 55);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        int na, un, limit1, limit2;

        na = query("name");
        un = query("base_unit");

        limit1 = me->max_food_capacity();
        limit2 = me->max_water_capacity();

        message_vision(HIC "$N" HIC "一仰脖，吞下了一" + un + na + HIW "。\n" NOR, me);

        if( query("food", me)<limit1*3 || query("water", me)<limit2*3 )
        {
                       tell_object(me, HIY "你只感疲勞一掃而空，再也不覺得饑餓。\n" NOR);

                if( query("food", me)<limit1*3 )
                        set("food", limit1*3, me);

                if( query("water", me)<limit2*3 )
                        set("water", limit2*3, me);
        } else
        {
                       tell_object(me, HIR "你只覺肚子「咕咕咕」叫個不停，隨後放了個奇臭"
                                "無比的屁。\n" NOR);

                if( query("food", me)>limit1/10 )
                        set("food", limit1/10, me);

                if( query("water", me)>limit2/10 )
                        set("water", limit2/10, me);
        }
        me->start_busy(random(1) + 1);
        add_amount(-1);

        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}