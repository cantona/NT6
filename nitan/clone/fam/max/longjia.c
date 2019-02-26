// longjia.c 子午龍甲丹

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "子午龍甲丹" NOR, ({ "longjia dan", "longjia", "dan" }) );
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIR "靈藥中的神品，服用後不但可以醫治任何內傷，而且\n"
                                "可平增一個甲子以上的功力。更有相傳説此丹散發出\n"
                                "的異香可繚繞周圍數十萬方圓。本物品第一次吃效果最佳！\n" NOR);
                set("value", 100000);
                set("no_sell", 1);
                set("unit", "顆");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        string mapsk;
        int effect;
        int neili;

        log_file("static/using", sprintf("%s(%s) eat 子午龍甲丹 at %s.\n",
                 me->name(1),query("id", me),ctime(time())));

        effect = 0;

        if( query("skybook/item/longjia", me) )
        {
                /*
                message_vision(HIR "$N" HIR "一仰脖，吞下了一顆子午龍甲丹，卻聽$P"
                               HIR "一聲尖哮，噴出一口鮮血。\n" NOR, me);
                
                me->set_temp("die_reason","貪吃子午龍甲丹，結果弄得全身筋脈盡斷"
                                           "而亡");
                me->die();
                */ 
                me->improve_neili(500);
                addn("skybook/item/longjia", 1, me);
                message_vision(HIW "$N" HIW "一仰脖，吞下了一顆子午龍甲丹，只見$P"
                               HIW "渾身一顫，七竅都冒出白煙來。\n" NOR, me);
        } else
        {
                message_vision(HIW "$N" HIW "一仰脖，吞下了一顆子午龍甲丹，只見$P"
                               HIW "渾身一顫，七竅都冒出白煙來。\n" NOR, me);

                //addn("combat_exp", 1000000+random(500000), me);
                addn("potential", 10000, me);

                mapsk = me->query_skill_mapped("force");
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);

                mapsk = me->query_skill_mapped("parry");
                if (me->can_improve_skill("parry"))
                        me->improve_skill("parry", 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);

                mapsk = me->query_skill_mapped("dodge");
                if (me->can_improve_skill("dodge"))
                        me->improve_skill("dodge", 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);

                me->improve_neili(500);
                set("skybook/item/longjia", 1, me);
        }
        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}
