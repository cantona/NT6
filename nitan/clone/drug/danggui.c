// Code of ShenZhou
// danggui.c 當歸

#include <ansi.h>

inherit ITEM;

int cure_ob(string);

void init();

void create()
{
        set_name( GRN "當歸" NOR , ({"dang gui", "danggui"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "棵");
                set("long", "這是一棵百年的老當歸，雖然已經乾癟，但其養精鎮神的藥效甚佳。\n");
                set("value", 10000);
                set("no_sell", 1);
                set("medicine", 1);
        }
        setup();
}

int cure_ob(object me)
{
        if ( (int)me->query_condition("bonze_drug" ) > 0 ){
                addn("max_jingli", -1, me);
                addn("eff_jingli", -1, me);
                set("jingli", 0, me);
                me->apply_condition("bonze_drug", 30);
        message_vision(HIR "$N吃下一顆當歸，只覺得肝腸寸斷，五臟欲裂，原來服食太多藥物，藥效適得其反！\n" NOR, this_player());
                destruct(this_object());
        }
        addn("max_jingli", 1, me);
        addn("eff_jingli", 1, me);
        set("jingli",query("max_jingli",  me), me);
        me->apply_condition("bonze_drug", me->query_condition("bonze_drug")+25);
        message_vision(HIY "$N吃下一棵老當歸，一道熱線直上重樓，全身的精力都恢復了。\n" NOR, me);

        destruct(this_object());
        return 1;
}