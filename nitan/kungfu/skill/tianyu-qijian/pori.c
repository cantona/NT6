// This program is a part of NITAN MudLIB
// pori.c 九弧破日

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string name() { return "九弧破日"; }

int perform(object me, object target)
{
        object weapon;
        int damage, p, i, wadd;
        string msg;
        int ap, dp;

        weapon=query_temp("weapon", me);

        if ( ! target )
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if ( ! target || ! me->is_fighting(target) )
                return notify_fail("「九弧破日」只能對戰鬥中的對手使用。\n");

        if( !weapon || query("skill_type", weapon) != "sword" )
                return notify_fail("你手裏沒有劍，無法使用「九弧破日」絕技！\n");

        if ( me->query_skill_mapped("sword") != "tianyu-qijian"
                || me->query_skill_mapped("parry") != "tianyu-qijian" )
                return notify_fail("你沒有用天羽奇劍，怎麼施展「九弧破日」絕技？\n");

        if( query("unique", weapon) )
                return notify_fail("你手中乃是一柄寶劍，無法用內力震碎！\n");

        if ( me->query_skill("tianyu-qijian", 1) < 160 )
                return notify_fail("你的天羽奇劍火候不足，使不出「九弧破日」絕技。\n");

        if ( me->query_skill("sword", 1) < 140 )
                return notify_fail("你的基本劍法還不夠嫻熟，使不出「九弧破日」絕技。\n");

        if( query("09g/ring", me) == "li" )
        {
                if ( me->query_skill("xiaowuxiang", 1) < 140 )
                        return notify_fail("你的小無相功修為不足，使不出「九弧破日」絕技。\n");
                if ( me->query_skill_mapped("force") != "bahuang-gong" )
                        return notify_fail("你沒有使用小無相功，無法使用「九弧破日」絕技。\n");
        }

        else
        {
                if ( me->query_skill("bahuang-gong", 1) < 140 )
                        return notify_fail("你的八荒六合惟我獨尊功修為不足，使不出「九弧破日」絕技。\n");
                if ( me->query_skill_mapped("force") != "bahuang-gong" )
                        return notify_fail("你沒有使用八荒六合惟我獨尊功，無法使用「九弧破日」絕技。\n");
        }

        if ( me->query_str() < 28 )
                return notify_fail("你的膂力還不夠強勁，使不出「九弧破日」絕技。\n");

        if ( me->query_dex() < 30 )
                return notify_fail("你的身法還不夠輕靈，無法施展「九弧破日」絕技。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力修為不足，無法使用「九弧破日」絕技。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你的內力不夠，無法震碎手中長劍。\n");


        msg = HIY"\n$N手腕一抖，手中"+weapon->name()+HIY"立時被內力震斷，無數碎片如雨點般激射向$n！\n"NOR;

        //Damage is also decided by how many times the player used this perform
        i=query("09g/pori", me);

        if ( i > me->query_skill("tianyu-qijian") )
                i = me->query_skill("tianyu-qijian");

        i-=query("age", me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");
        if( ap / 2 + random(ap) > dp )
        {
                me->start_busy(2);
                if( !target->is_busy() )
                        target->start_busy(1);
                addn("neili", -300, me);
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);
                damage+= i*20;

                //Damage is also decided by how strong the weapon is
                wadd=(query("weapon_prop/damage", weapon)+1);
                damage = damage+(random(wadd)+wadd)*2;

                if( query("neili", me)>query("neili", target)*2 )
                        damage += random(damage);

                if ( damage > 2000 )
                        damage = damage+random(me->query_skill("sword", 1));

                if ( damage < 200 )
                        damage = damage-random(target->query_skill("dodge", 1)/2);

                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/3);

                msg += HIR"\n結果$N手中射出的"+weapon->name()+
                       HIR"碎片盡數釘在了$n身上，一屢屢鮮血從傷口處湧出！\n"NOR;

                p=query("qi", target)*100/query("max_qi", target);
                msg = replace_string(msg, "$w", "碎片");
                msg = replace_string(msg, "$l", "周身多處");

                if ( me->query_skill("tianyu-qijian", 1) > 140
                && me->query_skill("sword") > 140 )
                        call_out("perform2", 0, me, target);
        }

        else
        {
                addn("neili", -100, me);

                me->start_busy(3);
                msg += HIC"\n$n眼見"+weapon->name()+
                       HIC"碎片已射至眼前，只得鋌而走險，運勁鼓起袍袖將碎片撥了開！\n"NOR;
        }

        message_combatd(msg, me, target);

        weapon->unequip();
        weapon->move(environment(me));
        set("name", "碎裂的"+query("name", weapon), weapon);
        set("value", 1, weapon);
        set("weapon_prop", 0, weapon);
        me->reset_action();
        addn("09g/pfm_pori", 1, me);

        return 1;
}

//If possible, also busy target
int perform2(object me, object target)
{
        string msg;

        if ( !me || !target || !living(target) )
                return 0;

        msg = MAG "\n不料，$N射出的碎片竟運上了陰柔內力，釘向了$n的周身要穴！\n\n"NOR;

        if( query("max_neili", me)>query("max_neili", target)*2/3 && random(10)<4 )
        {
                msg += HIR "結果$n只覺傷處氣血閉塞，真氣已經無法流轉，登時倒抽一口冷氣！\n" NOR;
                me->start_busy(3);
                target->start_busy(me->query_skill("force",1)/10);
                addn("neili", -(me->query_skill("force",1)/5), me);
        }

        else
        {
                addn("neili", -10, me);
                addn("neili", -10, target);
                me->start_busy(3);
                msg += HIC "\n$p只覺碎片上運有陰柔內力，意欲打穴封脈。幸而早有準備，沒有上當。\n" NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}

int help(object me)
{
        write(WHT"\n「九弧破日」\n\n"CYN+
                 " 　　這一式九弧破日乃是天羽奇劍的厲害招式，系以深厚內功震碎自己的\n"+
                 " 兵器，並以滿天花雨的手法拋向敵人，實是厲害不過。然而，此招需有深\n"+
                 " 厚內功作基礎，並需相當的劍法造詣才能得以施展。也正因手上勁道不好\n"+
                 " 掌握，因此這一招的威力及命中率需靠"HIY"經常地使用"CYN"來提高，招式的威力與\n"+
                 " 所使用的武器質量也有很大關係。不僅如此，當劍法的造詣達到一定境界\n"+
                 " 之時還會出現"HIG"附加功效"CYN"。\n\n"+

              WHT" 要求：八荒六合唯我獨尊功　"HIR"140"WHT" 級\n"+
              WHT" 　　　小無相功          　"HIR"140"WHT" 級\n"+
              WHT" 　　　天羽奇劍  　　　　　"HIR"160"WHT" 級\n"+
              WHT" 　　　基本劍法　　　　　　"HIR"140"WHT" 級\n"+
              WHT" 　　　縹緲心法  　　　　　"HIR" 80"WHT" 級\n"+
              WHT" 　　　後天膂力  　　　　  "HIR" 28"WHT" 點\n"+
              WHT" 　　　後天身法  　　　　  "HIR" 30"WHT" 點\n"+
              WHT" 　　　當前精力  　　　　 "HIR" 200"WHT" 點\n"+
              WHT" 　　　當前內力  　　　　 "HIR"1000"WHT" 點\n"+
              WHT" 　　　最大內力　　　　　 "HIR"2000"WHT" 點\n\n"+

              WHT" 戰鬥中使用。\n"NOR);

        return 1;
}
