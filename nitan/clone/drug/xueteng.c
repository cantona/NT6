// Code of ShenZhou
// xueteng.c 大血籐

#include <ansi.h>

inherit ITEM;

int cure_ob(string);
void init();

void create()
{
        set_name( GRN "大血籐" NOR , ({"da xueteng", "xueteng"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "棵");
                set("long", "這是一棵南詘特產的大血籐，看起來是黑乎乎的枯木，但有補血振氣的神效。\n");
                set("value", 10000);
                set("no_sell", 1);
                set("medicine", 1);
        }
        setup();
}

int cure_ob(object me)
{
        if ( (int)me->query_condition("bonze_drug" ) > 0 ){
                addn("max_neili", -1, me);
                set("neili", 0, me);
                me->apply_condition("bonze_drug", 30);
        message_vision(HIR "$N吃下一顆大血籐，只覺得肝腸寸斷，五臟欲裂，原來服食太多藥物，藥效適得其反！\n" NOR, this_player());
                destruct(this_object());
        }
        
        set("qi",query("max_qi",  me), me);
        addn("max_neili", 1, me);
        set("neili",query("max_neili",  me), me);
        me->apply_condition("bonze_drug", me->query_condition("bonze_drug")+20);
        message_vision(HIY "$N吃下一棵大血籐，頓時血氣翻湧血脈膨脹，氣力大長。\n" NOR, me);

        destruct(this_object());
        return 1;
}