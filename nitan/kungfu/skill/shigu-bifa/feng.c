#include <ansi.h>
#include <combat.h>

#define FENG "「" HIR "神筆封穴" NOR "」"

inherit F_SSERVER;
 
int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, damage;

        if( userp(me) && !query("can_perform/shigu-bifa/feng", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(FENG "只能對戰鬥中的對手使用。\n");

        weapon=query_temp("weapon", me);

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "dagger" )
                return notify_fail("你所使用的武器不對，難以施展" FENG "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        skill = me->query_skill("shigu-bifa", 1);

        if (me->query_skill("force") < 150)
                return notify_fail("你的內功的修為不夠，難以施展" FENG "。\n");

        if (skill < 100)
                return notify_fail("你的石鼓打穴筆法修為有限，難以施展" FENG "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不足，難以施展" FENG "。\n");

        if (me->query_skill_mapped("dagger") != "shigu-bifa")
                return notify_fail("你沒有激發石鼓打穴筆法，難以施展" FENG "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "飛身一躍而起，貼至$n" HIR "跟前，手中" +
              weapon->name() + HIR "大起大落，氣勢恢弘，幻出一道閃電"
              "直射$n" HIR "要穴！\n" NOR;
 
        ap = me->query_skill("dagger");
        dp = target->query_skill("parry");
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -200, me);
                damage = 100 + ap / 5 + random(ap / 5);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$p" HIR "微微一楞，只覺胸口一麻，"
                                           "已被$N" HIR "點中要穴，整個上半身頓時"
                                           "癱軟無力，緩緩癱倒。\n" NOR);
                me->start_busy(1);
                if (ap / 3 + random(ap) > dp && ! target->is_busy())
                        target->start_busy(ap / 25 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "的看破了$P" CYN
                       "的招式，巧妙的一一拆解，沒露半點"
                       "破綻！\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}