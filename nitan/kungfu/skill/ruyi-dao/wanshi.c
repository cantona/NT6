// ruyi.c 萬事如意

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "萬事如意"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, ap, dp, level, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「萬事如意」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("刀都沒有，使什麼「萬事如意」？\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠！\n");

        if ((int)me->query_skill("xiaowuxiang", 1) < 100
                && (int)me->query_skill("lingjiu-xinfa", 1) < 100
                && (int)me->query_skill("xiaoyao-xinfa", 1) < 100
                && (int)me->query_skill("bahuang-gong", 1) < 100
                && (int)me->query_skill("beiming-shengong", 1) < 100)
                return notify_fail("你的所用內功心法不正確，或者功力不夠，不能使用萬事如意！\n");

        if ( me->query_skill_mapped("force") != "xiaowuxiang"
                && me->query_skill_mapped("force") != "bahuang-gong"
                && me->query_skill_mapped("force") != "lingjiu-xinfa"
                && me->query_skill_mapped("force") != "xiaoyao-xinfa"
                && me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("你沒有運用逍遙派系列內功！\n");

        if (me->query_skill("blade") < 100)
                return notify_fail("你的如意刀法還不到家，無法使用「萬事如意」！\n");

        if (me->query_skill_mapped("blade") != "ruyi-dao")
                return notify_fail("你沒有激發如意刀法，無法使用「完事如意」！\n");

        msg=HIC"$N"HIC"抽身長笑，隨手揮出"+query("name", weapon)+HIC"，只見刀光流轉，刀氣縱橫無孔不如，直將$n整個籠罩進去！\n"NOR;
        message_combatd(msg, me, target);

        level = me->query_skill("blade");
        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");
        if (ap/2 + random(ap) > dp || !living(target))
        {
                addn("neili", -level, me);
                damage = damage_power(me, "balde");
                if (me->query_skill_mapped("force") == "xiaowuxiang") damage += me->query_skill("xiaowuxiang",1);
                if( me->query_skill_mapped("force") == "beiming-shengong" && query("neili", target)>me->query_skill("force")*2 )
                        addn("neili", -100, target);

                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                        HIR "$p" HIR "眼見着刀光飛泄過來卻手足無措，結果被$P"
                        HIR "一刀正中胸口，悶哼一聲，鮮血飛濺而出！\n" NOR);
                me->start_busy(2);
                target->start_busy(1+random(2));
        }
        else
        {
                msg = HIY "$p" HIY "眼見着刀光飛泄過來，慌忙間就地一個打滾，總算避開了$P"
                      HIY "這招萬事如意！\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}
