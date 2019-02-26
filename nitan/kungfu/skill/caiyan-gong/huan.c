#include <ansi.h>
#include <combat.h>

#define HUAN "「" HIM "雲霞幻生" NOR "」"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon, weapon2;
        int skill, ap, dp, damage;
        string wn, msg;

        if( userp(me) && !query("can_perform/caiyan-gong/huan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUAN "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "club" )
                return notify_fail("你使用的武器不對，難以施展" HUAN "。\n");

        skill = me->query_skill("caiyan-gong", 1);

        if (skill < 120)
                return notify_fail("你採燕功等級不夠，難以施展" HUAN "。\n");

        if (me->query_skill("dodge") < 180)
                return notify_fail("你的輕功火候不夠，難以施展" HUAN "。\n");
 
        if (me->query_skill_mapped("club") != "caiyan-gong")
                return notify_fail("你沒有激發採燕功，難以施展" HUAN "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" HUAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        wn = weapon->name();

        message_sort(HIM "\n$N" HIM "驀地施出「" HIW "雲霞幻生"
                     HIM "」絕技，手中" + wn + HIM "由一變二，"
                     "由二變四，由四變八，由八變十六……竟幻出"
                     "無數根" + wn + HIM "。棍影層層疊疊朝四周"
                     "疾刺而出，企圖封鎖$n" HIM "的退路。\n" NOR,
                     me, target);

        ap = me->query_skill("club");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap * 4 / 3) > dp)
        {
                addn("neili", -80, me);
                damage = 50 + ap / 6 + random(ap / 6);
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           (: final, me, target, damage :));

                me->start_busy(2);
        } else
        {
                msg = CYN "$n" CYN "大驚之下急忙躍開數步，方才擺脱$N"
                      CYN "棍影的範圍。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_vision(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        string msg;

        msg = HIR "$p大驚失色之下接連被$P擊中數棍"
              "，當即疼痛難當，";

        if (random(3) >= 1 && ! target->is_busy())
        {
                target->start_busy(damage / 15);
                msg += "無暇反擊。\n" NOR;
        } else
                msg += "急聲長呼。\n" NOR;

        return  msg;
}