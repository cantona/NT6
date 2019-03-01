// This program is a part of NITAN MudLIB
// bafang.c 威鎮八方

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "威鎮八方"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「威鎮八方」只能在戰鬥中對對手使用。\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必須空手才能使用「威鎮八方」！\n");

        if (me->query_skill("force") < 300)
                return notify_fail("你的內功的修為不夠，不能使用這一絕技！\n");

        if (me->query_skill("shenzhang-bada", 1) < 200)
                return notify_fail("你的神掌八打修為不夠，目前不能使用「威鎮八方」！\n");

        if( query("neili", me)<700 )
                return notify_fail("你的真氣不夠，無法使用「威鎮八方」！\n");

        if (me->query_skill_mapped("strike") != "shenzhang-bada")
                return notify_fail("你沒有激發神掌八打，不能使用「威鎮八方」！\n");

        msg = HIY "$N" HIY "深深的吸了一口氣，大喝一聲，全身衣袍無風自鼓，"
                   HIY "然後提氣往上一縱，居高臨下，雙掌奮力擊下，剎那間，內勁猶如旋風般"
                   "擊向$n" + HIY "！\n" NOR;

        ap=attack_power(me,"strike")+me->query_str()*20;
        dp=defense_power(target,"parry")+target->query_dex()*20;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                addn("neili", -350, me);

                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "看破了$N" CYN "的企圖，輕輕"
                       CYN "向後飄出數丈，躲過了這一致命的一擊！\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}