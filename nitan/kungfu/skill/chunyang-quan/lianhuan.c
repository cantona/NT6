// Code of Shenzhou
///kungfu/skill/chunyang-quan/lianhuan.c 連環三招
// sdong 07/98
//
//【巫師】董曉(Sdong)：make lianhuan only add apply/attack
//【巫師】董曉(Sdong)：the style of qz perform should be high speed but not high damage
/*
**maco 補：連環本質應該是劍掌腿。**
尹志平左劍平刺，右掌正擊，同時左腿橫掃而出，正是全真派中的「三連環」絕招。趙志敬高縱丈餘，揮劍下削。尹志平長劍脱手，猛往對方擲去，跟著「嘿」的一聲，雙掌齊出。

楊過見這幾招凌厲變幻，已非己之所知，不禁手心人全是冷汗，眼見趙志敬身在半空，一個勢虛，一個勢實，看來這兩掌要打得他筋折骨斷。豈知趙志敬竟在這情勢危急異常之際忽然空中翻身，急退尋丈，輕輕巧巧的落了下來。
*/


#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
        int skill;
        string weapon;
        int damage;
        string *limb, type, result, str;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("連環三招只能對戰鬥中的對手使用。\n");


        if( objectp(query_temp("weapon", me)) )
                return notify_fail("連環三招需空手才能施展！\n");

        if( me->query_skill_mapped("cuff") != "chunyang-quan" )
                return notify_fail("你所用的並非純陽拳，不能施展連環三招！\n");

        if( me->query_skill_prepared("cuff") != "chunyang-quan" )
                return notify_fail("你所備的並非純陽拳，不能施展連環三招！\n");

        if( me->query_skill_mapped("force") != "xiantian-gong" )
                return notify_fail("你所用的並非玄門先天功，施展不出連環三招！\n");

        if( me->query_skill("force") < 140 )
                return notify_fail("你的玄門先天功火候未到，無法施展連環三招！\n");

        if( me->query_skill("cuff") < 135 )
                return notify_fail("連環三招需要精湛的純陽拳方能有效施展！\n");

        if( query("neili", me) <= 200 )
                return notify_fail("你的內力不夠使用連環三招！\n");
        if( query("jingli", me) <= 200 )
                return notify_fail("你的精力不夠使用連環三招！\n");


        message_vision(HIR "$N怒喝一聲，拚盡全力，突然閃電般攻出拳、掌、腿連環三招！\n\n" NOR, me, target);

        skill = me->query_skill("strike")/2 + me->query_skill("cuff") / 8;
        if(skill>300)skill=300;
        addn_temp("apply/attack", skill, me);
        set_temp("lianhuan", 1, me);

        if( me->query_skill_prepared("strike") == "sanhua-juding" ) {
                set_temp("restore", 1, me);
                me->prepare_skill("strike");
        }

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        if( query_temp("restore", me))me->prepare_skill("strike","sanhua-juding");
        if( me->query_skill_prepared("cuff") == "chunyang-quan" ) {
                set_temp("restore", 1, me);
                me->prepare_skill("cuff");
        }

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        if( query_temp("restore", me))me->prepare_skill("cuff","chunyang-quan");
        addn_temp("apply/attack", -skill, me);

        message_vision( "\n緊跟着$N突然騰空飛起，使出一招鴛鴦連環腿，兩腿風馳電掣連環踢向$n\n",me,target);
        if( random(query("combat_exp", me))>query("combat_exp", target)/3 )
        {
                if( ( target->query_skill("dodge")+target->query_skill("parry") ) < random((me->query_skill("cuff") + me->query_skill("force"))*2/3) )
                {
                        message_vision(HIR"只聽$N一聲慘叫，這連環二腿正中心口。但見$n一個身軀突然平平飛出，騰的一響，塵土飛揚，跌在丈許之外，直挺挺的躺在地下，再也不動。\n\n"NOR, target,target );
                        target->receive_wound("qi",query("qi", target)+1,me);
                        target->receive_damage("qi",query("qi", target)+1,me);
                        addn("neili", -query("jiali", me), me);
                        addn("jingli", -query("jiajin", me), me);
                }
                else
                {
                        damage=random((me->query_skill("cuff"))+query("jiali", me))*(1+random(query("jiajin", me)/5));
                        if(damage > 1500) damage = 1500;
                        if(damage < 300) damage = 300;
                        addn("neili", -query("jiali", me), me);
                        addn("jingli", -query("jiajin", me), me);

                        target->receive_damage("qi", damage,  me);
                        target->receive_wound("qi", (int)me->query_skill("strike"), me);

                        limb=query("limbs", target);
                        type = "瘀傷";
                        message_vision("只聽$N一聲慘叫，這連環二腿正中$P"+limb[random(sizeof(limb))]+"，結果把$P踢摔了個跟頭。\n",target);

                        str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                        message_vision("($N"+str+")\n", target);
                }
                me->start_busy(1+random(2));
        }
        else if( ( random( target->query_skill("dodge") ) >  me->query_skill("cuff")*2/3) && random(5) == 1 )
        {
                message_vision(HIR"$N猛覺得勁風罩來，心知不妙，慌忙閃開，結果$n踢了個空，白白自己重重跌了一跤。\n\n"NOR, target,me );
                me->receive_damage("qi", 30+random(50),  me);
                me->start_busy(1+random(3));
                str=COMBAT_D->status_msg(query("qi", me)*100/query("max_qi", me));
                message_vision("($N"+str+")\n", me);
        }
        else
        {
                message_vision( "$N眼見這一腿來勢兇猛，當下雙足一點，躍高四尺，躲開了$n這一招，不過也出了一身冷汗。\n\n" NOR,  target,me);
                me->start_busy(1);
        }

        delete_temp("lianhuan", me);

        addn("neili", -random(me->query_skill("cuff")/4)-100, me);
        addn("jingli", -100, me);
        me->start_busy( 1+random(2) );

        return 1;
}
