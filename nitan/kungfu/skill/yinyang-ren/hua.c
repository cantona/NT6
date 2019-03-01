#include <ansi.h>
#include <combat.h>

#define HUA "「" HIY "日月無華" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int level;

        if( userp(me) && !query("can_perform/yinyang-ren/hua", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUA "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" HUA "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        level = me->query_skill("yinyang-ren", 1);

        if (level < 180)
                return notify_fail("你陰陽刃法不夠嫻熟，難以施展" HUA "。\n");

        if (me->query_skill_mapped("sword") != "yinyang-ren"
            && me->query_skill_mapped("blade") != "yinyang-ren")
                return notify_fail("你沒有激發陰陽刃法，難以施展" HUA "。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不足，難以施展" HUA "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在的真氣不夠，難以施展" HUA "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");


        msg = HIG "\n$N" HIG "使出陰陽刃法「" HIY "日月無華" HIG "」，手"
              "中" + weapon->name() + HIG "光芒瀑漲，刺眼眩目，日月為"
              "之失輝，剎那間光芒已蓋向$n" HIG "。" NOR;
        message_sort(msg, me, target);

        addn("neili", -120, me);
        if (level / 2 + random(level) > target->query_skill("dodge", 1))
        {
                msg = HIR "$n" HIR "被耀眼的光芒所惑，心中驚"
                      "疑不定，一時間不知如何應對！\n" NOR; 
                target->start_busy(level / 24 + 2);
                me->start_busy(1);
        } else
        {
                msg = CYN "可是$n" CYN "看破了$N"
                      CYN "的企圖，一絲不亂，應對自若。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}