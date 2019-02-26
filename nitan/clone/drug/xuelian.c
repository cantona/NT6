// xuelian.c 雪蓮
// Modified by Dumbness, 2003-5-21 20:39

#include <ansi.h>;
#include <armor.h>

inherit HEAD;

void init();

void create()
{
        set_name(HIM"雪蓮"NOR, ({"xuelian", "lian", "lotus"}));
        set_weight(90);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", HIW"這是一朵晶瑩的雪蓮，她傲然於銀白色的雪山之巔綻放，清澈靈動，如清風\n般撫慰你的心田。\n"NOR);
                set("value", 20000);
                set("no_sell", 1);
                set("no_put",1);
                set("medicine", 1);
                set("only_do_effect", 1);
                set("armor_prop/per", 5);
                set("armor_prop/per", 2); 
                set("wear_msg",         
                        HIM"$N輕輕的戴上那朵傳説中的雪蓮花，自己彷彿也變成了一朵傲然綻放於雪山\n"
                        "之顛的雪蓮——不食人間煙火般的清澈，晶瑩剔透的眼波流轉，如一縷輕風\n"
                        "般的身影夜夜徘徊在情人的夢鄉……\n"NOR);
                set("remove_msg", WHT"$N輕輕地把$n"WHT"從頭上摘了下來，頓時黯然失色，不復婉轉靈動。\n"NOR); 
        }
        setup();
}

int do_effect(object me)
{
        if (me->query_condition("cool_drug") > 0)
        {
                addn("max_jingli", -5, me);
                addn("eff_jing", -5, me);
                message_vision(HIR "$N吃下一枚雪蓮，只覺得頭重腳輕，搖搖欲倒，原來服食太急太多，藥效適得其反！\n" NOR, me);
                destruct(this_object());
                return 1;
        }
        message_vision(HIM"$N吃下一支雪蓮，一股秋菊似的幽香沁入心肺，頓覺神清氣爽。\n"NOR, me);
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("jingli",query("max_jingli",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
        me->apply_condition("cool_drug", 30);

        if (random(3)==1)
        { 
                if( (me->query_jingli_limit()-query("max_jingli", me))>5 )
                {
                        addn("max_jingli", 5, me);
                        addn("eff_jing", 5, me);
                }
        }

        set("neili",query("max_neili",  me), me);
        set("jingli",query("max_jingli",  me), me);
        
        if ((int)me->query_condition("snake_poison") > 0) 
                me->apply_condition("snake_poison", 0);
  
        if ((int)me->query_condition("insect_poison") > 0) 
                me->apply_condition("insect_poison", 0);
 
        if ((int)me->query_condition("sl_poison") > 0) 
                me->apply_condition("sl_poison", 0);
   
        if ((int)me->query_condition("xx_poison") > 10 
                && (int)me->query_condition("xx_poison") < 50) 
                me->apply_condition("xx_poison", 0);
        destruct(this_object());
        return 1;
}
