// This program is a part of NITAN MudLIB
// cui.c 摧心斷腸

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "摧心斷腸"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        string skill;
        int ap, fp, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("「摧心斷腸」只能對戰鬥中的對手使用。\n");

        if (me->query_skill("shedao-qigong", 1) < 120)
                return notify_fail("你的蛇島奇功修為有限，不能使用「摧心斷腸」！\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真氣不夠，無法運用「摧心斷腸」！\n");

        if( objectp(weapon=query_temp("weapon", me)) &&
            query("skill_type", weapon) != "staff" &&
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的兵器不對，怎麼使用「摧心斷腸」！\n");

        if (weapon)
                skill=query("skill_type", weapon);
        else
                skill = "unarmed";

        if (me->query_skill_mapped(skill) != "shedao-qigong")
                return notify_fail("你沒有將" + (string)to_chinese(skill)[4..<1] +
                                   "激發為蛇島奇功, 不能使用「摧心斷腸」！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        switch (skill)
        {
        case "unarmed":
                msg = HIW "$N" HIW "一聲暴喝，雙掌一起擊出，霎時間飛砂走石，$n"
                      HIW "只覺得幾乎窒息。\n" NOR;
                break;

        case "sword":
                msg = HIW "$N" HIW "一聲暴喝，手中" + weapon->name() +
                      HIW "直劈而下，只聽呼嘯聲大作，地上的塵土受內力所激紛紛飛揚而起。\n" NOR;
                break;

        case "staff":
                msg = HIW "$N" HIW "一聲暴喝，手中" + weapon->name() +
                      HIW "橫掃蕩出，一時間塵土飛揚，$n"
                      HIW "登時覺得呼吸不暢。\n" NOR;
                break;
        }

        ap = attack_power(me, skill);
        fp = defense_power(target, "force");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) < fp)
        {
                addn("neili", -200, me);
                msg += CYN "可是$n" CYN "內功深厚，奮力接下$N"
                       CYN "這一招，絲毫無損。\n" NOR;
                me->start_busy(2);
        } else
        if (ap / 2 + random(ap) < dp)
        {
                addn("neili", -50, me);
                msg += CYN "$n" CYN "哈哈一笑，飄身躍開，讓$N"
                       CYN "這一招全然落空。\n" NOR;
                me->start_busy(3);
        } else
        {
                addn("neili", -220, me);
                me->start_busy(2);
                damage = damage_power(me, skill);
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 60,
                                           HIR "$n" HIR "只覺得$N" HIR "內力猶如"
                                           "排山倒海一般，怎能抵擋？“哇”的一下吐出一大口鮮血。\n" NOR);
        }
        message_combatd(msg, me, target);

        return 1;
}


