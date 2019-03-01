// xuanhuang.c 玄黃紫箐丹

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "玄黃紫箐丹" NOR, ({ "xuanhuang dan", "xuanhuang", "dan" }) );
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIM "一顆紫中泛黃的精致奇丹，具有著神話般的功效，傳\n"
                                "說吃了之後能平增數十年的功力，乃是練武之人夢寐\n"
                                "以求的神丹妙藥。本物品第一次吃效果最佳！\n" NOR);
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

        log_file("static/using", sprintf("%s(%s) eat 玄黃紫箐丹 at %s.\n",
                 me->name(1),query("id", me),ctime(time())));

        effect = 0;

        if( query("skybook/item/xuanhuang", me) )
        {
                /*
                message_vision(HIR "$N" HIR "一仰脖，吞下了一顆玄黃紫箐丹，卻聽$P"
                               HIR "一聲尖哮，噴出一口鮮血。\n" NOR, me);

                me->set_temp("die_reason","貪吃玄黃紫箐丹，結果弄得全身筋脈盡斷"
                                           "而亡");
                me->die();
                */ 
                me->improve_neili(500);
                addn("skybook/item/xuanhuang", 1, me);
                message_vision(HIW "$N" HIW "一仰脖，吞下了一顆玄黃紫箐丹，只見$P"
                               HIW "渾身一顫，七竅都冒出白煙來。\n" NOR, me);
        } else
        {
                message_vision(HIW "$N" HIW "一仰脖，吞下了一顆玄黃紫箐丹，只見$P"
                               HIW "渾身一顫，七竅都冒出白煙來。\n" NOR, me);

                //addn("combat_exp", 100000+random(50000), me);
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
                set("skybook/item/xuanhuang", 1, me);
        }
        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}
