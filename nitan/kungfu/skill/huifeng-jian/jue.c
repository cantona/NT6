// jue.c  迴風拂柳劍法「絕劍」

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "絕劍" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        string wname;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，無法施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "huifeng-jian")
                return notify_fail("你沒有激發迴風拂柳劍法，無法施展" + name() + "。\n");

        if ((int)me->query_skill("huifeng-jian", 1) < 120)
                return notify_fail("你迴風拂柳劍法不夠嫻熟，無法施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你內功火候不夠，無法施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在真氣不夠，無法施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        wname = weapon->name();

        damage = damage_power(me, "sword");

        // 第一招
        ap = attack_power(me, "sword") + me->query_str();
        dp = defense_power(target, "parry") + target->query_str();
        msg = HIC "$N" HIC "一聲暴喝，手中的" + wname + HIC "對準$n" HIC "直劈而"
              "下，正是迴風拂柳劍「" NOR + HIW "絕劍" NOR + HIC "」絕技。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$p" HIR "奮力抵擋，卻哪裏招架得住，被$P"
                                           HIR "這一劍劈下，登時鮮血迸流！\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "嘿的一聲，硬聲聲將$P"
                       CYN "這一劍架開，絲毫無損。\n" NOR;
        }

        // 第二招
        ap = attack_power(me, "sword") + me->query_int();
        dp = defense_power(target, "parry") + target->query_int();
        msg += "\n" HIC "$N" HIC "隨即一聲冷笑，手中的" + wname +
               HIC "伸伸縮縮，吞吞吐吐，變幻莫測，層層劍光籠罩$n" HIC "。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$p" HIR "大惑不解，一時難以勘透其"
                                           "中奧妙，一連中了幾招，身披數創！\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "淡淡一笑，渾然不將$P"
                CYN "玄妙的招數放在眼中，隨意將之架開。\n" NOR;
        }

        // 第三招
        ap = attack_power(me, "sword") + me->query_con();
        dp = defense_power(target, "force") + target->query_con();
        msg += "\n" HIC "$N" HIC "深深吸了一口氣，手中的" + wname +
               HIC "幻化出一層淺淺的光芒，人劍合一撲向$n" HIC "而去。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$p" HIR "運氣抵擋，只覺得一股透體涼意"
                                           "襲了上來，一個激凌，丹田立刻變得空空蕩蕩！\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "一口氣自丹田運了上來，$P"
                CYN "附體劍芒雖然厲害，卻未能傷$p" CYN "分毫。\n" NOR;
        }

        // 第四招
        ap = attack_power(me, "sword") + me->query_dex();
        dp = defense_power(target, "dodge") + target->query_dex();
        msg += "\n" HIC "$N" HIC "腳步一晃，忽然近上身來，身法奇快，手中的" + wname +
               HIC "應聲而起，刺向$n" HIC "。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "$p" HIR "只是慢了一步，登時被$P"
                                           HIR "這一劍刺了個正中，鮮血四處飛射！\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "身法卻是更快，只是一退，讓$P"
                CYN "這一招堪勘不能奏效。\n" NOR;
        }

        // 第五招
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");
        msg += "\n" HIC "$N" HIC "一聲長歎，眼神變得寒冷無情，" + wname +
               HIC "悠悠而轉，猶如輕風拂柳，説不清的纏綿之意。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           HIR "$p" HIR "只覺得沐浴在風中一般，對這招竟然是無可抵擋，被"
                                           HIR "劍光削了個血肉模糊！\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "冷靜非凡，絲毫不為這奇幻的招數"
                       "所動，凝神抵擋，不漏半點破綻！\n" NOR;
        }

        me->start_busy(3 + random(5));
        addn("neili", -400-random(100), me);
        message_combatd(msg, me, target);
        return 1;
}
