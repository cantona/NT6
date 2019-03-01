// bagua.c 八卦陣

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int i, ap, dp;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「八卦陣芒」只能對戰鬥中的對手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你的兵器不對。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力修為不夠。\n");

        if( query("neili", me)<400 )
                return notify_fail("你的真氣不夠！\n");

        if ((int)me->query_skill("force") < 220)
                return notify_fail("你的內功火候不夠！\n");

        if ((int)me->query_skill("zijinbagua-dao", 1) < 200)
                return notify_fail("你的紫金八卦刀還不到家，無法使用「八卦陣芒」！\n");

        if (me->query_skill_mapped("blade") != "zijinbagua-dao")
                return notify_fail("你沒有激發紫金八卦刀，無法使用「八卦陣芒」！\n");

        msg = MAG "$N" MAG "一聲暴喝，手中的" + weapon->name() +
              MAG "刀芒陡長，頓時只見萬股凌厲的刀芒按照八卦陣的"
              "方位直湧$n" MAG "！\n\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");
        
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "見來招實在是變幻莫測，不由得心"
                       "生懼意，招式登時出了破綻！\n" NOR;
                count = me->query_skill("zijinbagua-dao", 1) / 6;
        } else
        {
                msg += HIY "$n" HIY "心底微微一驚，打起精神小心接招。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn("neili", -300, me);
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 5 + random(3) ; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(6));
        return 1;
}