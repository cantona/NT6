#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "風神訣" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon, weapon2;
        string w1, w2;
        int ap, dp;

        me = this_player();

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("你的武器不對，無法使用" + name() + "。\n");

        if (me->query_skill_mapped("whip") != "yinsuo-jinling")
                return notify_fail("你沒有激發回銀索金鈴，不能使用" + name() + "。\n");

        if ((int)me->query_skill("yinsuo-jinling", 1) < 140)
                return notify_fail("你的銀索金鈴不夠嫻熟，還使不出" + name() + "。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<400 )
               return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n"NOR);

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        w1 = weapon->name();
        damage = damage_power(me, "whip");
        ap = attack_power(me, "whip");
        dp = defense_power(target, "parry");

        msg = "\n" HIW "只見$N" HIW "手中" + w1
              + HIW "暮地一抖，幻出無數鞭影，霎"
              "時破風聲驟起，" + w1 + HIW "攜着"
              "風雷之勢掃向$n" HIW "！\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "$n" HIR "只覺鞭影重重，眼花繚亂"
                                           "，根本無法作出抵擋，一聲慘嚎，鮮血飛"
                                           "濺而出！\n" NOR);
        } else
        {
                msg += CYN "可是$p" CYN "鎮定自如，"
                       "絲毫不為這變幻莫測的招式所動"
                       "，凝神抵擋，化解開來！\n" NOR;
        }

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");

        msg += "\n" HIW "緊接着$N" HIW "一聲"
               "嬌喝，" + w1 + HIW "猛地向後"
               "一撤，" + w1 + HIW "頓時化作"
               "一道長虹，已從$n" HIW "背後"
               "襲出！\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "稍一遲疑，突然感到後背"
                                           "一陣" HIR "刮骨之痛，已被這招打得血"
                                           "肉模糊！\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "一聲冷哼，早預料$N"
                       CYN "有此一着，凝神聚氣，將這招輕"
                       "輕格開！\n" NOR;
        }

        if( objectp(weapon2=query_temp("weapon", target)) )
        {
                msg += "\n" HIW "$N" HIW "眉頭微皺，手"
                       "腕輕輕一振，只聽“颼”的一聲，"
                       "又攻出一招，" + w1 + HIW "如流"
                       "星般彈向$n" HIW "腕部！\n" NOR;

                ap = attack_power(me, "whip");
                dp = defense_power(target, "force");

                if (ap / 2 + random(ap) > dp)
                {
                        w2 = weapon2->name();
                        msg += HIR "只聽“當”的一聲，" + w1 +
                               HIR "正打在$p" + w2 + HIR "上，"
                               "$p" HIR "手腕一麻，" + w2 + HIR
                               "再也拿持不住，脱手掉在地上。\n"
                               NOR;
                        addn("neili", -50, me);
                        weapon2->unequip();
                        weapon2->move(environment(target));
                } else
                {
                        msg += CYN "可是$p" CYN "看破了$P" CYN
                               "的企圖，急忙斜跳躲開！\n" NOR;
                        addn("neili", -30, me);
                }
        }
        me->start_busy(2 + random(4));
        addn("neili", -300, me);
        message_combatd(msg, me, target);
        return 1;
}