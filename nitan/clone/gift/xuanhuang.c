// xuanhuang.c 玄黃紫清丹

#include <ansi.h>
#include "gift.h"

void create()
{
        set_name(HIM "玄黃紫清丹" NOR, ({ "xuanhuang dan", "dan" }) );
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一顆紫中泛黃的精致奇丹，具有這神話般的功效，"
                            "是練武人夢寐以求的妙藥。\n");
                set("base_value", 250000);
                set("base_weight", 100);
                set("base_unit", "粒");
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        int effect;
        int neili;

        effect = 0;
        message_vision(HIW "$N" HIW "一仰脖，吞下了一顆" +
                       this_object()->name() + HIW "，只見$N"
                       HIW "渾身一顫，七竅都冒出白煙來。\n" NOR, me);
        if( query("gift/xuanhuang", me) <= 20 )
        {                        
                message_vision(HIW "只見$N" HIW "渾身一顫，七竅都冒出白煙來。\n", me);
                //addn("combat_exp", 150000, me);
                me->improve_skill("force", 250000);
                me->improve_skill("parry", 250000);
                me->improve_skill("dodge", 250000);
        }
        neili=query("max_neili", me)+500;
        if (neili > me->query_current_neili_limit())
        {
                neili = me->query_current_neili_limit();
                /*
                if( me->query_neili_limit()>query("max_neili", me) )
                        neili = me->query_neili_limit();
                else
                        neili=query("max_neili", me);
                */
        }
        set("max_neili", neili, me);
        addn("gift/xuanhuang", 1, me);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());
                
        return 1;
}


