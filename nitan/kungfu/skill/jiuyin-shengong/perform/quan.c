// quan 九陰神拳
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;

#define QUAN "「" HIW "九陰神拳" NOR "」"
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(QUAN "只能對戰鬥中的對手使用。\n");

        if (me->query_skill("jiuyin-shengong", 1) < 230)
                return notify_fail("你的九陰神功還不夠嫻熟，不能使用" QUAN "！\n");

        if (me->query_skill("cuff", 1) < 220)
                return notify_fail("你的基本拳法還不夠嫻熟，不能使用" QUAN "！\n");

        if( query("neili", me)<240 )
                return notify_fail("你的內力不夠，不能使用" QUAN "！\n");

        if( query_temp("weapon", me) )
                return notify_fail("此招只能空手施展！\n");

        if (me->query_skill_prepared("unarmed") != "jiuyin-shengong")
                return notify_fail("你沒有準備使用九陰神功，無法施展" QUAN "。\n");
 
       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "一聲冷哼，握拳擊出，招式雄渾，難擢其威！\n" NOR;
 
        ap = attack_power(me, "unarmed") + me->query_str();
        dp = defense_power(target, "dodge") + target->query_dex();

        me->start_busy(2);
        addn("neili", -50, me);
        if (ap / 2 + random(ap) < dp)
        {
                msg += HIG "只見$n" HIG "不慌不忙，輕輕一閃，躲過了$N" HIG "這一擊！\n"NOR;
        } else
        {
                addn("neili", -90, me);
                damage = damage_power(me, "unarmed");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 95 + random(5),
                                           HIR "$n" HIR "連忙格擋，可是這一拳力道何等之重，哪裏抵"
                                           "擋得住？只被打得吐血三尺，連退數步！\n" NOR);
        }

        message_combatd(msg, me, target);
        return 1;
}