// This program is a part of NT MudLIB

#include <ansi.h>

inherit F_SSERVER;

string name() { return "怒海驚濤"; }

int perform(object me, object target)
{
        object weapon;
        int myexp, targexp, damage, skill, merand, targrand, targneili,time,i;
        string str,*limb,type;
        mapping myfam;
        int tmp_jiali,dmg;
        int num,ap,dp;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「怒海驚濤」只能對戰鬥中的對手使用。\n");

        if( (!(myfam=query("family", me)) || myfam["family_name"] != "古墓派") )
                  return notify_fail("只有古墓弟子才能用「怒海驚濤」。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("空手才能施展「怒海驚濤」！\n");

        if( me->query_skill_mapped("force") != "surge-force" )
                return notify_fail("你所用內功的並非怒海狂濤，使不出「怒海驚濤」！\n");

        if( (int)me->query_skill("surge-force",1) < 150 )
                return notify_fail("你內功修為太差，不能運用「怒海驚濤」！\n");

        if( me->query_skill("sad-strike",1) < 150 )
                return notify_fail("你黯然銷魂掌修為太差，不能運用「怒海驚濤」！\n");

        if( (string)me->query_skill_mapped("unarmed") != "sad-strike")
                return notify_fail("你並沒有激發黯然銷魂掌作為掌法。\n");

        if( (string)me->query_skill_prepared("unarmed") != "sad-strike")
                return notify_fail("你並沒有準備黯然銷魂掌。\n");

        if ( !living(target))
               return notify_fail("現在不沒必要用「怒海驚濤」吧！\n");

        if( query("neili", me) <= 1000 )
                return notify_fail("你的內力不夠使用「怒海驚濤」！\n");

        ap = attack_power(me,"unarmed")+query("jiali", me);
        dp = defense_power(target, "parry") + target->query_skill("force");
        damage = damage_power(me, "unarmed");
        damage+= query("jiali", me);

        skill=me->query_skill("sad-strike",1);

        message_combatd(HIW"\n$N的掌風隱隱帶着潮湧之聲，掌風鼓盪，竟似有狂潮湧來，這正是神鵰大俠當年在海邊練出的絕技。 \n\n"NOR,me,target);

        if (ap/2 + random(ap) > dp)
        {
                message_combatd(HIR"$n哪裏躲避得開，大驚下已經給$N的掌風印上胸口，一口鮮血狂噴而出！\n\n",me,target);
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2,me);
                if (! target->is_busy())
                        target->start_busy(1);
        } else
        {
                message_combatd(HIY"$n見狀不妙，立刻就地一個打滾，雖然姿勢難看以及，不過總算避開了$N這一掌。\n\n"NOR,me,target);
        }

        message_combatd(HIW"\n$N在掌風達到頂峯之時，跟着“魂不守舍”、“倒行逆施”、“若有所失”，連出三招。\n\n"NOR,me,target);

        dp = defense_power(target, "dodge") + target->query_skill("force");
        if (ap/2 + random(ap) > dp)
        {
                message_combatd(HIR"$n驚魂未定，正喘氣之際，不提防又一陣猛烈的氣浪撲面衝來，復遭$N掌風重創！\n\n",me,target);
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2,me);
                if (! target->is_busy())
                        target->start_busy(1);
        } else
        {
                message_combatd(HIY"$n顧不得反擊，急身後退三丈，臉頰給$N的掌風掃到，微微發紅，不過總算避開了$N這三掌。\n\n"NOR,me,target);
        }

        message_combatd(HIW"跟着$N騰身而起，一招“行屍走肉”，閃電般踢出一腳。\n\n"NOR,me);

        dp = defense_power(target, "force") + target->query_skill("force");
        if (ap/2 + random(ap) > dp)
        {
                message_combatd(HIR"$n眼看着這霸氣沖天的一腳，已然放棄了抵抗，整個臉部給$N重重踹上，牙齒皆碎，面目血色猙獰！\n\n",me,target);
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2,me);
                if (! target->is_busy())
                        target->start_busy(1);
        } else
        {
                message_combatd(HIY"$n雙足點地，拔天而起，從$N的頭頂掠過，腳下勁氣呼嘯而過，真是險之又險！\n\n"NOR,me,target);
        }

        addn("neili", -600, me);
        me->start_busy(2+random(2));

        return 1;
}
