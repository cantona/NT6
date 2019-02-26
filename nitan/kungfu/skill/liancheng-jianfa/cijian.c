// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";

string name() { return "刺肩式"; }

string *limbs = ({
        "頭部", "頸部", "胸口", "後心", "左肩", "右肩", "左臂",
        "右臂", "左手", "右手", "腰間", "小腹", "左腿", "右腿",
        "左腳", "右腳", "左耳", "右耳", "左臉", "右臉",
});

void remove_effect(object target);
string *songs = ({"HIC", "HIR", "HIW", "HIY"});

int perform(object me, object target)
{

        int damage, p, ap, dp;
        object weapon;
        string msg, song, dodge_skill;

        song = songs[random(sizeof(songs))];

        if( !target ) target = offensive_target(me);

        weapon=query_temp("weapon", me);
        if( !target )
                target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「"HIM"刺肩式"NOR"」只能在戰鬥中對對手使用。\n");

        if (!weapon
                 || query("skill_type", weapon) != "sword"
                || me->query_skill_mapped("sword") != "liancheng-jianfa")
                return notify_fail("你手裏沒有劍，無法使用「"HIM"刺肩式"NOR"」！\n");

        if( (int)me->query_skill("liancheng-jianfa",1) < 150 )
                return notify_fail("你的連城劍法不夠嫻熟，不能使用「"HIM"刺肩式"NOR"」！\n");

        if( (int)me->query_skill("sword",1) < 150 )
                return notify_fail("你的基本劍法等級不夠，不能使用「"HIM"刺肩式"NOR"」！\n");

        if( (int)me->query_skill("force", 1) < 150 )
                return notify_fail("你的內功等級不夠，不能使用「"HIM"刺肩式"NOR"」！\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力太弱，不能使用「"HIM"刺肩式"NOR"」！\n");

        if( query("neili", me)<700 )
                return notify_fail("你的內力太少了，無法使用出！\n");

        msg = WHT "\n$N身子一晃，抽起"+weapon->name()+WHT"，猶如疾風驟雨般一陣猛攻，$n擋得幾招，發劍回攻，\n"
              "$N突然間"+weapon->name()+WHT"抖動，卟的一聲輕響，從不可思議的角度刺向了$n的肩頭\n"NOR;

        msg = replace_string( msg, "song", songs[random(sizeof(songs))] );

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                addn("neili", -140, me);

                damage = damage_power(me, "sword");

                // if (target->is_busy()) damage = damage * 2;

                if( query("shen", target)<0)damage=damage*3/2;

                if( query("neili", me)>query("neili", target)*2 )
                        damage += random(damage);

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                p=query("qi", target)*100/query("max_qi", target);
                msg += COMBAT_D->damage_msg(damage, "刺傷");
                msg += "( $n"+eff_status_msg(p)+" )\n";
                msg=replace_string(msg,"$w",query("name", weapon));
                msg = replace_string( msg, "$l", limbs[random(sizeof(limbs))] );
        }

        message_combatd(msg, me, target);

        msg = HIB "\n$n橫劍擋路，見$N"+weapon->name()+HIB"停滯不前，當即振劍反刺。那知$n劍尖只一抖間，"
              "$N的"+weapon->name()+HIB"如毒蛇暴起，向前一探，已點中了$n肩頭。！\n"NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp
                || target->is_busy())
        {
                me->start_busy(1);
                addn("neili", -150, me);
                damage = damage_power(me, "sword");
                // if(target->is_busy())damage=damage*2;
                if( query("shen", target)<0)damage=damage*3/2;

                if( query("neili", me)>query("neili", target)*2 )
                        damage += random(damage);

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                p=query("qi", target)*100/query("max_qi", target);
                msg += COMBAT_D->damage_msg(damage, "刺傷");
                msg += "( $n"+eff_status_msg(p)+" )\n";
                msg=replace_string(msg,"$w",query("name", weapon));
                msg = replace_string( msg, "$l", limbs[random(sizeof(limbs))] );
        }
        message_combatd(msg, me, target);

        msg = YEL "\n$N"+weapon->name()+YEL"左一刺，右一戳，每一劍都從無比怪異的方位刺出，"
              "點向$n的肩部，$n只要一出劍相攻，立時便可後發先至，刺中$n的肩頭。\n"NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp
                ||target->is_busy())
        {
                addn("neili", -160, me);

                damage = damage_power(me, "sword");

                // if(target->is_busy())damage=damage*2;
                if( query("shen", target)<0)damage=damage*3/2;

                if( query("neili", me)>query("neili", target)*2 )
                        damage += random(damage);

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                p=query("qi", target)*100/query("max_qi", target);
                msg += COMBAT_D->damage_msg(damage, "刺傷");
                msg += "( $n"+eff_status_msg(p)+" )\n";
                msg=replace_string(msg,"$w",query("name", weapon));
                msg = replace_string( msg, "$l", limbs[random(sizeof(limbs))] );
        }
        message_combatd(msg, me, target);

        return 1;
}