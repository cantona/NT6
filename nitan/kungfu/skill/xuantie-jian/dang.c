// This program is a part of NITAN MudLIB
// 力盪群魔

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return RED"力盪群魔"NOR; }

int perform(object me, object target)
{
        int damage, ap, dp;
        object weapon;
        string msg, pmsg;

        if (! target) target = offensive_target(me);

        if (! target
        ||  ! target->is_character()
        ||  ! me->is_fighting(target))
                return notify_fail(
                        "「"RED"力盪群魔"NOR"」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，加緊攻擊吧□\n");

        if((int)me->query_skill("xuantie-jian", 1) < 120)
                return notify_fail(
                        "你的玄鐵劍法不夠嫻熟，不會使用「"RED"力盪群魔"NOR"」。\n");

        if ((int)me->query_skill("surge-force", 1) < 120
        &&  (int)me->query_skill("surge-force", 1) < 120)
                return notify_fail(
                        "你的古墓內功修為太淺，不會使用「"RED"力盪群魔"NOR"」。\n");

        if (me->query_str() < 40)
                return notify_fail(
                        "你的臂力不夠，使用「"RED"力盪群魔"NOR"」過于艱難。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的內力不夠！\n");

        msg=HIB"驟然間，$N手中"NOR+query("name", weapon)+HIB"發出一陣轟鳴，帶著隆隆"+
              "的風雷之聲，挾雷霆萬均之勢，\n一式「"NOR+BLINK+RED"力盪群魔"NOR+HIB"」，" +
              "手中"NOR+query("name", weapon)+HIB"朝$n當頭直壓下去！\n";

        ap = attack_power(me, "sword") + me->query_str()*10;
        dp = defense_power(target, "parry") + target->query_str()*10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);
                addn("neili", -200, me);

                pmsg = HIR "$n無力招架，登時被$N這記重招壓得氣血翻騰，禁不住「哇」地吐出一口鮮血！\n" NOR;
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80, pmsg);
                me->start_busy(1);
                if( !target->is_busy() )
                        target->start_busy(2);
        } else
        {
                addn("neili", -100, me);
                msg += HIW"$p連忙全力一擋，「砰」地一聲巨響，$P這記重招居然被$p接了下來！\n" NOR;
                me->start_busy(2);
        }

        message_combatd(msg, me, target);

        return 1;
}

