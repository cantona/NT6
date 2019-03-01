// zhua.c 九陰白骨爪 - 九陰神抓

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "九陰神爪" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        string pmsg;
        string *limbs;
        string  limb;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用九陰神抓！\n");

        if ((int)me->query_skill("jiuyin-baiguzhao", 1) < 120)
                return notify_fail("你的九陰白骨爪還不夠嫻熟，不能使用"+name()+"。\n");

        if (me->query_skill_prepared("claw") != "jiuyin-baiguzhao")
                return notify_fail("你沒有準備九陰白骨爪，無法使用"+name()+"。\n");

        if( query("neili", me)<240 )
                return notify_fail("你現在內力太弱，不能使用九陰神抓。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "冷笑一聲，眼露兇光，右手成爪，三盤兩旋虛虛"
              "實實的向$n" HIR "的頭頂抓了下來。\n" NOR;

        addn("neili", -50, me);

        me->want_kill(target);
        ap = attack_power(me, "claw");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                addn("neili", -180, me);
                damage = 0;

                if( query("max_neili", me)<query("max_neili", target)*4/5 &&
                    me->query_skill("force") < target->query_skill("force"))
                        msg += HIY "“啪”的一聲$N" HIY "正抓在$n" HIY "的天靈蓋上，"
                               "結果震得“哇哇”怪叫了兩聲！\n" NOR;
                else
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg += HIY "“撲哧”一聲，$N" HIY "五指正插入$n" HIY "的天靈"
                               "蓋，$n" HIY "一聲慘叫，軟綿綿的癱了下去。\n" NOR;
                        damage = -1;
                } else
                {
                        if (!target->is_busy())
                        target->start_busy(1 + random(3));

                        damage = damage_power(me, "claw");

                        if( arrayp(limbs=query("limbs", target)) )
                                limb = limbs[random(sizeof(limbs))];
                        else
                                limb = "要害";
                        pmsg = HIC "$n連忙騰挪躲閃，然而“撲哧”一聲，$N"
                               HIC "五指正插入$n" HIC "的" + limb + "，$n"
                               HIC "一聲慘叫，血射五步。\n" NOR;
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 95, pmsg);
                }
        } else
        {
                me->start_busy(2);
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的企圖，身形急動，躲開了這一抓。\n" NOR;
        }

        message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);
        else
        if (! target->is_killing(me))
                target->kill_ob(me);

        return 1;
}
