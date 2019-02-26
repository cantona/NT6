// This program is a part of NITAN MudLIB
// xian.c 神龍再現

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "神龍再現"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        string skill;
        int ap, pp, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("「神龍再現」只能對戰鬥中的對手使用。\n");

        if (me->query_skill("shedao-qigong", 1) < 120)
                return notify_fail("你的蛇島奇功修為有限，不能使用「神龍再現」！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，無法運用「神龍再現」！\n");

        if( objectp(weapon=query_temp("weapon", me)) &&
            query("skill_type", weapon) != "staff" &&
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的兵器不對，怎麼使用「神龍再現」！\n");

        if (weapon)
                skill=query("skill_type", weapon);
        else
                skill = "unarmed";

        if (me->query_skill_mapped(skill) != "shedao-qigong")
                return notify_fail("你沒有將" + (string)to_chinese(skill)[4..<1] +
                                   "激發為蛇島奇功, 不能使用「神龍再現」！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        switch (skill)
        {
        case "unarmed":
                msg = HIW "$N" HIW "輕身一躍，已然逼近$n" HIW "隨即一掌向$p"
                      HIW "肩頭按去，虛虛實實，暗藏千百變化。\n" NOR;
                break;

        case "sword":
                msg = HIW "$N" HIW "足不點地，飄然欺身上前，一劍刺出，" +
                      weapon->name() + HIW "直指$n" HIW "腰間。" NOR;
                break;

        case "staff":
                msg = HIW "$N" HIW "手中" + weapon->name() +
                      HIW "吞吞吐吐，虛虛實實，化作一團光影，斜斜掃向$n"
                      HIW "腰間。\n" NOR;
                break;
        }

        ap = attack_power(me, skill);
        pp = defense_power(target, "parry");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > pp)
        {
                addn("neili", -150, me);
                me->start_busy(2);
                damage = damage_power(me, skill);
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50,
                                           HIR "$n" HIR "欲架不能，欲躲不得，一個閃失"
                                           "，被$P" HIR "打了個正中，鮮血迸流。\n" NOR);
        } else
        if (ap / 3 + random(ap) > dp)
        {
                addn("neili", -180, me);
                me->start_busy(2);
                damage = damage_power(me, skill);
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 55,
                                           HIR "$n" HIR "見$P" HIR "這招極為精妙，不敢"
                                           "抵擋，慌忙後退躍開，卻見$P" HIR "招式一變，竟然料敵在先，\n"
                                           "一招正中$p" HIR "，直打了個鮮血四下飛濺。\n" NOR);
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "$n" CYN "不敢怠慢，見招拆招，接連破去$P"
                       CYN "後續三十六道變化，不漏半點破綻。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}


