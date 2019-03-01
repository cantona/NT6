#include <ansi.h>

inherit F_SSERVER;

#define DIAN "「" HIG "隔空點穴" NOR "」"

int perform(object me, object target)
{
        object weapon;
        string msg;
        int time;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/yinsuo-jinling/dian", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(DIAN "點穴攻擊只能對戰鬥中的對手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "whip" )
                return notify_fail("你的武器不對，無法施展" DIAN "！\n");

        if (me->query_skill("yinsuo-jinling", 1) < 80)
                return notify_fail("你的銀索金鈴級別不夠，無法施展" DIAN "！\n");

        if (me->query_skill("force") < 100)
                return notify_fail("你的內功修為不夠，無法施展" DIAN "！\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在真氣不夠，無法施展" DIAN "！\n");

        if (me->query_skill_mapped("whip") != "yinsuo-jinling")
                return notify_fail("你沒有激發銀索金鈴，無法施展" DIAN "！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "\n$N" HIY "單手一抖，手中" + weapon->name() +
              HIY "疾顫三下，分點$n" HIY "臉上「迎香」、「承泣"
              "」、「人中」三個穴道，這三下點穴出手之快、認位之"
              "準，實是武林罕見！" NOR;

        me->start_busy(1 + random(2));

        message_sort(msg, me, target);

        if( random(query("combat_exp", me))>query("combat_exp", target)/2 )
        {
                msg = HIR "$n" HIR "只聽$N" + weapon->name() +
                      HIR "發出玎玎聲響，聲雖不大，卻是"
                      "十分怪異，入耳盪心搖魄，一不\n留神"
                      "，被這招點個正著，全身癱軟無力，動"
                      "彈不得！\n" NOR;
                time = (int)me->query_skill("yinsuo-jinling") / 25;
                time = 2 + random(time);
                if (time > 13) time = 13;
                target->start_busy(time);
        } else
        {
                msg = CYN "可是$p" CYN "看破了$P"
                      CYN "的企圖，斜跳躲閃開來。\n" NOR;
        }
        addn("neili", -120, me);
        message_combatd(msg, me, target);

        return 1;
}