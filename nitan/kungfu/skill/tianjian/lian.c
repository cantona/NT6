#include <ansi.h>
#include <combat.h>

#define SHENG "「" HIW "連環決" NOR "」"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
                int i;
 
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHENG "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" SHENG "。\n");

        if (me->query_skill("tianjian", 1) < 20)
                return notify_fail("你的天劍修為不夠（要求天劍二十級），難以施展" SHENG "。\n");

        if (me->query_skill_mapped("sword") != "tianjian")
                return notify_fail("你沒有激發天劍，難以施展" SHENG "。\n");

        if( query("neili", me)<15 )
                return notify_fail("你現在真氣（要求15的內力）不夠，難以施展" SHENG "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了（對方已死亡），用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "身法忽快，手中" + weapon->name() +
              HIY "迴轉，突然「唰！唰！」數劍，連連刺向$n" HIY "。\n" NOR;

        message_combatd(msg, me, target);

                addn("neili", -10, me);

        me->start_busy(1 + random(2));
                addn_temp("apply/attack", me->query_skill("sword"), me);

                for (i = 0; i < 4; i++)
                {
                        if (! me->is_fighting(target))break;

                        if (random(2))target->start_busy(1);
                        
                        COMBAT_D->do_attack(me, target, weapon, 0);
                }

                addn_temp("apply/attack", -1*me->query_skill("sword"), me);

                if( query("newbie_quest/leixing", me) == "perform" )
                {
                                set("newbie_quest/completed", 1, me);
                                me->save();
                                tell_object(me, HIG "你已經學會了如何施展絕招，快回去找老村長領取獎勵吧！\n" NOR);
                }

        return 1;
}
