// zhao.c 八卦掌「罩」字訣
// Create by Haiyan 2002

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int level;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("八卦掌「罩」字訣只能對戰鬥中的對手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧！\n");
                
        if ((level = me->query_skill("bagua-zhang", 1)) < 100)
                return notify_fail("你的八卦掌不夠嫻熟，不會使用「罩」字訣。\n");

        if( query("neili", me)<60 )
                return notify_fail("你現在真氣不夠，無法使用「罩」字訣。\n");

        msg = HIG "$N" HIG "腳下步伐加快，使出八卦掌「罩」字訣，雙掌"
              "舞出漫天掌影，將$n" HIG "籠罩在當中。\n" NOR;

        addn("neili", -30, me);
        if (random(level) > (int)target->query_skill("parry", 1) / 2)
        {
                msg += HIR "$p" HIR "只覺無數掌影向自己襲來，手忙腳亂，"
                       "呆在當地，不知該如何應對！\n" NOR;
                target->start_busy(level / 30);
        } else
        {
                msg += CYN "然而$p" CYN "看破了$P" CYN "的企圖，縱身一躍，"
                       "已跳出了$P" CYN "的掌勢。\n" NOR;
                me->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}