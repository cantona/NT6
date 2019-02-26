#include <combat.h>
#include  <ansi.h>

#define HUI "「" WHT "分身" HIW "化影" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{

        int ap, dp;
        object env;

        if( userp(me) && !query("can_perform/kuihua-mogong/fenshen", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUI "只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("kuihua-mogong", 1) < 460)
                return notify_fail("你葵花魔功修為不夠，難以施展" HUI "。\n");

        if( query("max_neili", me)<6000 )
                return notify_fail("你內力修為不夠，難以施展" HUI "。\n");

          if( query("jingli", me)<1000 )
                return notify_fail("你精力不足，難以施展" HUI "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你內力不足，難以施展" HUI "。\n");
        
        if (me->is_busy())
                return notify_fail("你現在正忙！\n");

        if( query_temp("hiding_kuihua", me) )
                return notify_fail("你正在運功中！\n");

        ap=me->query_skill("dodge")+query("dex", me);
        dp=target->query_skill("dodge")+query("dex", target);

        env = environment(me);
        
         me->start_busy(1);
         addn("neili", -800, me);
         addn("jingli", -400, me);

        message_sort(HIY "\n$N冷笑一聲，施展出《葵花寶典》記載之絕學" + HUI + HIY + 
                     "，剎那間，" + env->short() + HIY + "幻化出無數$N的身影。\n" NOR, me);
        
        if (target->query_skill("count") > 100 && random(2))
        {
                message_sort(HIC "\n$N施展出陰陽八卦的絕學，將$n的" + HUI + HIC "化解。\n" NOR, target, me);
                return 1;
        }

        if (ap / 2 + random(ap) > dp)
        {
                message_sort(HIG "\n$N頓覺眼花繚亂，失去了方向！\n" NOR, target);
                target->remove_enemy(me);
                set_temp("hiding_kuihua", 1, me);
                addn("jingli", -200, me);
                target->start_busy(4 + random(4));
                call_out("del_hiding", 20 + random(me->query_skill("kuihua-mogong", 1) / 30), me);
        }
        else
        {
                message_sort(HIM "\n$N趕緊收攝住心神，小心的移動着腳步，將$n這招化解。\n" NOR, target, me);
        }
                
        return 1;
}

void del_hiding(object me)
{

        if (! objectp(me))return;

        delete_temp("hiding_kuihua", me);

        tell_object(me, HIG "你分身化影術施展完畢，將內力收回丹田。\n");

        return;
}