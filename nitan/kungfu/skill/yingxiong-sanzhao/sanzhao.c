//sanzhao.c 奪命三連招

#include <combat.h>
#include <ansi.h>

inherit F_SSERVER;

string name() { return "奪命三連招"; }

string *limbs =
({
        "頭頂", "頸部", "胸口", "後心", "左肩", "右肩", "左臂",
        "右臂", "左手", "右手", "兩肋", "左臉", "腰間", "小腹",
        "左腿", "右腿", "右臉", "左腳", "右腳", "左耳", "右耳"
});
void chkpfm(object me, object target, int amount);
void remove_effect(object me, object target, int amount);
int perform(object me, object target)
{
        object weapon, weapon1;
        int lvl1, lvl2, amount;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("奪命三連招只能對戰鬥中的對手使用。\n");

        if (!living(target))
                return notify_fail("他已經暈倒了，你可以輕易地殺了他！\n");

        if( time()-query_temp("sxj-t", target)<30 )
                return notify_fail("他已經適應了你的招式，對他來説已經無效了！\n");

        if( me->query_skill_mapped("force") != "shenlong-xinfa" &&
            me->query_skill_mapped("force") != "busi-shenlong" )
                return notify_fail("你所用的並非神龍心法，無法施展奪命三連招！\n");

        if (me->query_skill_mapped("strike") != "yingxiong-sanzhao")
                return notify_fail("你沒有激發英雄三招，難以施展奪命三連招。\n");

        if (me->query_skill_prepared("strike") != "yingxiong-sanzhao")
                return notify_fail("你沒有準備英雄三招，難以施展奪命三連招。\n");

        if( (lvl1=me->query_skill("shenlong-xinfa", 1)) < 150 &&
            me->query_skill("busi-shenlong",1)< 150)
                return notify_fail("你的神龍心法火候未到，無法施展奪命三連招！\n");

        if( (lvl2=me->query_skill("strike")) < 200 )
                return notify_fail("你英雄三招修為不足，還不會使用奪命三連招！\n");

        if( (lvl2 - lvl1) < lvl2 / 4 && lvl1 < 200)
                return notify_fail("奪命三連招需要更精湛的武藝！\n");

        amount = (lvl1+lvl2) / 5;

        if ( amount < 60 ) amount = 60;
        if ( amount > 200 ) amount = 200;

        if( query("neili", me) <= amount*10 )
                return notify_fail("你的內力不夠使用奪命三連招！\n");

        if( query("jingli", me) <= amount*5 )
                return notify_fail("你的精力不夠使用奪命三連招！\n");

        if( !query_temp("sanxianjian", me)){
                addn_temp("apply/unarmed_damage", amount*2, me);
                addn_temp("apply/attack", amount, me);
                addn_temp("apply/dodge", amount, me);
                set_temp("sanxianjian", 1, me);
                me->start_busy(1);
                me->start_call_out( (: call_other, __FILE__, "remove_effect", me, target, amount:), amount/15);
        }

        message_combatd(HIW "$n抓住$N的後頸，一把提起。$N左手慢慢反轉，在$n左腋底搔了一把，\n$n身子軟了下來，$N左手拿住$n腋下，右手慢慢迴轉，抓住$n領口，緩緩\n舉起$n的身子，過了自己頭頂，向外摔出。\n"NOR, me, target);
        chkpfm(me, target, amount);
        message_combatd(HIW "$N俯伏地上，$n伸右足踏住$N的後腰，$N雙腿一縮，似欲跪拜，\n右臂卻慢慢橫掠而出，突然間一個筋斗，向$n的胯下鑽去，只一作勢\n左手已抓住$n右腳足踝，右手向$n小腹擊去。\n"NOR, me, target);
        chkpfm(me, target, amount);
        set_temp("sxj-c", 3, me);
        message_combatd(HIW"$N雙臂反在背後，突然雙手十指彎起，各成半球之形，身子向後一撞\n十指便抓向$n的胸部，$n向後一縮，$N突然一個倒翻筋斗，身子躍起\n雙腿一分，已跨在$n肩頭，同時雙手按指壓住$n太陽穴，食指按眉，中指按眼！\n"NOR, me, target);
        chkpfm(me, target, amount);



        if( query("eff_qi", target)*100/query("max_qi", target) <= 20
          && query("qi", target)*100/query("max_qi", target) <= 5
          && query_temp("sxj-c", me) == 3 )
        {
                message_combatd(HIR "\n$N"+HIR+"這招內勁所注，力道強橫之極，$n便如被凌空飛來的重錘掃到，當下噴出一口鮮血！！\n" NOR, me, target);
                target->die(me);
        }

        me->start_busy(2);
        return 1;
}
void chkpfm(object me, object target, int amount)
{
        object weapon2=query_temp("weapon", target);
        string attack_skill, dodge_skill, parry_skill, result, msg = "";
        int ap, dp, pp, damage, level;

        if( !me->is_fighting(target) || !living(target) )
                return;

        level = me->query_skill("yingxiong-sanzhao", 1);
        damage = amount+random(level)/2;
        ap = COMBAT_D->skill_power(me, "strike", SKILL_USAGE_ATTACK)/ 100;
        if( ap < 1) ap = 1;

        dp = COMBAT_D->skill_power(target, "dodge", SKILL_USAGE_DEFENSE)/ 100;
        if( target->is_busy() ) dp /= 3;
        if( dp < 1 ) dp = 1;
        if( random(ap + dp) < dp )
        {
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg();
        }
        else
        {
                pp = COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE)/100;
                if( target->is_busy() ) pp /= 2;
                if( pp < 1 ) pp = 1;

                if( random(ap + pp) < pp )
                {
                        parry_skill = target->query_skill_mapped("parry");
                        if( !parry_skill || !SKILL_D(parry_skill)->parry_available())
                                parry_skill = "parry";
                        msg += SKILL_D(parry_skill)->query_parry_msg(weapon2, target);
                }
                else
                {
                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage/3, me);
                        if( query_temp("sxj-c", me) == 3 )
                                result = COMBAT_D->damage_msg(damage, "瘀傷");
                        else result = COMBAT_D->damage_msg(damage, "瘀傷");
                        msg += result;
                        result=COMBAT_D->status_msg(query("qi", target)*100/
                                query("max_qi", target));
                        msg += "( $n"+result+" )\n";
                        target->start_busy(1);
                }
        }
        result = limbs[random(sizeof(limbs))];
        msg = replace_string( msg, "$l", result );
        message_combatd(msg, me, target);
}
void remove_effect(object me, object target, int amount)
{
        if (!me) return;
        delete_temp("sanxianjian", me);
        if( me->is_fighting() && living(target))
        {
                message_combatd(HIY "\n$n慢慢的適應了$P奪命三連招的威力。\n" NOR, me, target);
                set_temp("sxj-t", time(), target);
        }
        else message_combatd(HIY "\n$N收回內勁,招式也恢復了平常。\n" NOR, me);
        addn_temp("apply/unarmed_damage", -amount*2, me);
        addn_temp("apply/attack", -amount, me);
        addn_temp("apply/dodge", -amount, me);
}
