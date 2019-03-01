
// jinwu.c 金烏墮地

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIR"金烏墮地"NOR; } 

int perform(object me,object target)
{
        string msg;
        object weapon;
        int ap, dp, qi_wound;
        int temp;
        string skill, fskill,bskill;

        if( !objectp(target) ) {target = offensive_target(me);}
        
        if( !target || !target->is_character() || target == me ||       
                !me->is_fighting(target) ||
                !living(target) )
                return notify_fail(name()+"只能對戰鬥中的對手使用。\n");

        if (!objectp(weapon = query_temp("weapon",me)) ||
                query("skill_type", weapon) != "blade")
                return notify_fail("你使用的武器不對。\n");
        
        skill  = "jingwu-blade";    
        fskill = "bingxue-xinfa";
        bskill = "blade";

        if( (int)me->query_skill(skill, 1) < 200 )
                return notify_fail("你的"+to_chinese(skill)+"等級不夠, 不能使用"+name()+"。\n");
                
        if( (int)me->query_skill(fskill, 1) < 100 )
                return notify_fail("你的"+to_chinese(fskill)+"等級不夠, 不能使用"+name()+"。\n");

        if( me->query("max_neili") < 1000 )
                return notify_fail("你的內力修為不夠，無法運用「"+HIR"金烏墮地"NOR+"」！\n");

        if( me->query("neili") < 400 )
                return notify_fail("你的內力不夠，無法運用「"+HIR"金烏墮地"NOR+"」！\n");

        msg = HIY"$N縱身躍起,使出"+HIR"「金烏墮地」"HIY"，揮舞"NOR+weapon->name()+HIY"從半空中揮刀直劈下來，\n"
              "刀鋒離地尚有數尺，地下已是塵沙飛揚，敗草落葉被刀風激得團團而舞，\n將$n逃遁退避的空隙封的嚴嚴實實。\n"NOR;
        message_combatd(msg, me, target);
        msg = "";

        ap = attack_power(me, "blade");
        dp = defense_power(target, "dodge");
        if (target->query_skill_mapped("parry") == "xueshan-sword")
        {
                msg += HIR "$n" HIR "慌忙中忙以"HIW"雪山劍法"HIR"作出抵擋，哪知$N"
                       HIR "刀法竟似雪山劍法克星般，\n" + weapon->name() +
                       HIR "刀芒霎時又暴漲數倍，完全封鎖$n" HIR "的所"
                       "有劍招！\n" NOR;
                ap = ap * 2;
                temp = 1;
        }       

        if( random(ap) + ap / 2 > dp )
        {
                if(userp(me)) me->add("neili",-250);
                msg += HIC"$n避無可避，只覺一股剛猛之極的勁風撲面而來，使人直欲窒息。\n"
                        "$n極力後退隔擋，卻只見"NOR""+weapon->name()+""HIC"刀光一閃，毫不停息，一刀正中面門。\n"NOR;
                qi_wound = damage_power(me, "blade")+me->query_str()*10;
                qi_wound *= 2;
                if (temp != 1) //對付非雪山門派
                {
                        qi_wound = random(qi_wound);
                        if(qi_wound > query("qi", target)) qi_wound = 100;
                }
                target->receive_damage("qi", qi_wound);
                target->receive_wound("qi", query("max_qi", target)/3);
                target->start_busy(2+random(1));
                me->start_busy(1+random(1)); 
        }
        else
        {
                if(userp(me)) me->add("neili",-100);
                msg += HIW"可是$n輕輕往旁邊一閃，避過了$N這必殺的一刀。\n"NOR;
                me->start_busy(2+random(2));
        }
        message_combatd(msg, me, target);
        return 1;
}

