#include <ansi.h>
#include <combat.h>

#define MENG "「" HIW "如夢如幻" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg, wn;
        object weapon;
        int level;

        if( userp(me) && !query("can_perform/songshan-jian/meng", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(MENG "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" MENG "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("songshan-jian", 1) < 40)
                return notify_fail("你天絕刀法不夠嫻熟，難以施展" MENG "。\n");

        if (me->query_skill_mapped("sword") != "songshan-jian")
                return notify_fail("你沒有天絕刀法，難以施展" MENG "。\n");

        if( query("neili", me)<120 )
                return notify_fail("你現在的真氣不夠，難以施展" MENG "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        wn = weapon->name();
                           
        msg = HIC "\n$N" HIC "怒嘯一聲，施展出絕招「" HIW "如夢如幻" HIC "」"
              "手中" + wn + HIC "似攻非攻，欲進忽退，令人匪夷所思。\n"NOR;

        message_sort(msg, me, target);

        level = me->query_skill("songshan-jian", 1);

        addn("neili", -80, me);

        if (level + random(level) > target->query_skill("dodge"))
        {
                msg = HIY "$N" HIY "看不出$n" HIY "招式中的虛實，連忙"
                      "護住自己全身，一時竟無以應對！\n" NOR; 
                target->start_busy(2 + random(level / 26));
                me->start_busy(random(2));
        } else
        {
                msg = CYN "可是$N" CYN "鎮定自若，小心拆招，沒有被"
                      "$n" NOR + CYN "招式所困。\n" NOR;
                      
                me->start_busy(2);
        }
        message_vision(msg, target, me);

        return 1;
}