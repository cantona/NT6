// zhenwu.c 真武除邪

#include <ansi.h>
#include <combat.h>

string name() { return "真武除邪"; }

inherit F_SSERVER;

string final(object me, object target, int damage);
int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("「" + name() + "」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if ((int)me->query_skill("taiji-jian", 1) < 250)
                return notify_fail("你的太極劍法不夠嫻熟，不會使用「" + name() + "」。\n");

        if ((int)me->query_skill("force", 1) < 250)
                return notify_fail("你的內功修為不夠高，難以運用「" + name() + "」。\n");

        if ((int)me->query_skill("taiji-shengong", 1) < 250)
                return notify_fail("你的太極神功修為不夠高，難以運用「" + name() + "」。\n");

        if( query("neili", me)<2000 )
                return notify_fail("你現在真氣不夠，不能使用「" + name() + "」。\n");

        if (me->query_skill_mapped("sword") != "taiji-jian")
                return notify_fail("你沒有激發太極劍法，不能使用「" + name() + "」。\n");

        msg = HIY "$N" HIY "閉目凝神，心如點轉，一招充滿太極劍意的「" HIW + name() +
              HIY "」緩緩使出，劍招返樸歸真，看似平淡無奇，\n實則匯集了天地之間的正氣，"
              HIY "由手中" + weapon->name()+ "幻化出無數太極劍圈，舖天蓋地的壓向$n！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");


        if( query("id", weapon) == "zhenwu jian") ap+=ap*(20+random(10))/100;
        if (target->is_bad()) ap += ap / 2;

        /*
        if (me->is_not_good()) ap = ap / 2;
        if (me->is_bad()) ap = ap / 3;
        if (target->is_good()) ap = ap * 4 / 5;
        */

        if( wizardp(me) && query("env/combat_test", me) )
        {
                tell_object(me, HIY "AP: " + ap + ". DP: " + dp + ".\n" NOR);
        }
        if (ap / 2 + random(ap*4/3) > dp)
        {
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);

                addn("neili", -500, me);
                //tell_object(me, HIC "DAMAGE: " + damage + ".\n" NOR);
                //msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 285,
                //                           HIR "\n$p" HIR "被$P的正氣所懾，竟然嚇得顧不上招架，"
                //                           "這一劍自胸口向小腹橫劃而過，\n頓時鮮血飛濺！\n" NOR);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 285,
                                           (: final, me, target, damage :));
                me->start_busy(2);
        } else
        {
                msg += HIG "可是$p" HIG "看破了$P" HIG "的企圖，鎮"
                       "定逾恆，全神應對自如。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 3, me);
        target->receive_wound("jing", damage / 6, me);
        return  HIY "結果$p" HIY "沒有把它放在心上，隨"
                "手應了一招，卻見$P" HIY "劍勢忽然一變"
                "，\n氣象萬千，變幻無窮，極具王者風范！\n"
                HIR "$p" HIR "驚慌失措，呆在當場，被$P"
                HIR "這一劍擊中要害！鮮血崩流，慘不忍睹！\n" NOR;
}
