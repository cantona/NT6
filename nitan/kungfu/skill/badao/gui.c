#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define LONG "「" HIY "歸海一刀" NOR "」"

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LONG "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對！\n");

        if ((int)me->query_skill("badao", 1) < 500)
                return notify_fail("你霸刀不夠嫻熟，無法施展" LONG "。\n");

        if ((int)me->query_skill("force") < 700)
                return notify_fail("你內功火候不夠，無法施展" LONG "。\n");

        if( query("neili", me)<2000 )
                return notify_fail("你現在真氣不夠，無法施展" LONG "！\n");

        if (me->query_skill_mapped("blade") != "badao")
                return notify_fail("你沒有激發霸刀，無法施展" LONG "。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIC "\n$N" HIC "面露苦色，舉手一刀，自上而下，剎那間，天地哭嚎，萬千刀氣猶如潮水海"
              "浪般壯觀，舖天蓋地的向前卷進，忽然，無數刀氣化為一道刀芒，猶如閃電般劈向$n" HIC "。\n" NOR;

        ap=me->query_skill("blade")+me->query_skill("martial-cognize",1);
        dp=target->query_skill("dodge")+target->query_skill("martial-cognize",1);
        if (ap * 4 / 5 + random(ap) > dp)
        {
                me->start_busy(3);
                damage = ap * 3 + random(ap * 3);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 300 + random(100),
                                           HIR "但見那兇猛無比的刀氣勢如破竹般的從$n" HIR "胸口透射而過，令人毛骨悚然！\n" NOR);
                addn("neili", -1800, me);
        } else
        {
                me->start_busy(3);
                msg += CYN "然而$n" CYN "輕輕一笑，左避右閃，竟將此招化解。\n" NOR;
                addn("neili", -120, me);
        }

        message_combatd(sort_msg(msg), me, target);
        
        return 1;
}
