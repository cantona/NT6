// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string name() { return "天外狂龍"; }

int perform(object me, object target)
{
        string msg;
        int extra, damage, ap, dp;
        object weapon;

        if (! target) target = offensive_target(me);
        if (! target
        ||  ! target->is_character()
        ||  ! me->is_fighting(target))
                return notify_fail("［天外狂龍］只能對戰鬥中的對手使用。\n");

        if( !weapon=query_temp("weapon", me) )
                return notify_fail("你沒裝兵器怎麼打！\n");

        if( query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的兵器不對！\n");

        if ((int)me->query_skill("kuangfeng-jian", 1) < 100)
                return notify_fail("你的狂風快劍不夠熟練，使不出 [ 天外狂龍 ] 。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的內力不夠！\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的劍法不夠嫻熟，使不出 [ 天外狂龍 ] 的絕招！\n");

        extra = me->query_skill("kuangfeng-jian", 1);

        msg = HIY "$N" HIY "劍斜斜刺出，激起股股劍氣，拔劍，收劍。在那一瞬間，天地變幻，人影竟似已縮小，\n"
              "但見劍夾雜着風，風裏含着劍影！那劍氣幻作無數條金黃色的龍鋪天蓋地襲向$n！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -200, me);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "只覺得腦中轟的一下，"
                                           "身子往後倒飛出去，跌倒在地，不禁“哇”的吐了一口鮮血！\n" NOR);
                me->start_busy(2);
        } else
        {
                addn("neili", -100, me);
                msg += CYN "可是$p" CYN "看破了$P" CYN "的狠毒企圖，向旁跳開數步，躲開了$P" CYN "的這一波可怕的攻擊！\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}