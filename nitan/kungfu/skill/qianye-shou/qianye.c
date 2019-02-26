// This program is a part of NITAN MudLIB
// qianye.c 千葉佛手

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "千葉佛手"; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「千葉佛手」只能在戰鬥中對對手使用。\n");

        skill = me->query_skill("qianye-shou", 1);

        if (skill < 120)
                return notify_fail("你的千葉手等級不夠，不會使用「千葉佛手」！\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠，無法運用「千葉佛手」！\n");

        if (me->query_skill_mapped("hand") != "qianye-shou")
                return notify_fail("你沒有激發千葉手，無法使用「千葉佛手」！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "倏的靠近$n" HIC "，伸手一晃，"
              "化出無數掌影，如同你有千百隻手一齊攻向" HIC
              "$n！\n" NOR;

        ap = attack_power(me, "hand") +
             me->query_skill("force");

        dp = defense_power(target, "parry") +
             target->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -100, me);
                damage = damage_power(me, "hand");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           HIR "$p" HIR "即不能招架，又無法躲避，結果被$P"
                                           HIR "連擊帶打，弄的暈頭轉向，身上也是傷痕累累。\n" NOR);
                me->start_busy(1 + random(2));
                if (ap / 3 + random(ap) > dp && ! target->is_busy())
                        target->start_busy(ap/120 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "的看破了$P" CYN
                       "的招式，連消帶打，全然化解了$P"
                       CYN "的攻勢。\n" NOR;
                addn("neili", -30, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
