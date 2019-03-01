// This program is a part of NT MudLIB
// jiutian.c  鳳舞九天

#include <ansi.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "鳳舞九天"; }

void remove_effect(object me, object target, int dodge, int damage, int parry);

int perform(object me, object target)
{
        object weapon, weapon1 ;
        string msg;
        int extra, dodge, speed, parry ,damage;

        if (!target) target = offensive_target(me);

        if (me->query_skill_mapped("force") != "kurong-changong" &&
            me->query_skill_mapped("force") != "duanshi-xinfa")
                return notify_fail(HIW"你所用得內功心法不對，無法躍起身形。\n" NOR);

        if (!target
        ||      !target->is_character()
        ||      !me->is_fighting(target))
                return notify_fail( HIW "「鳳舞九天」只能在戰鬥中使用。\n" NOR);

        if( query_temp("jiutian", me) )
                return notify_fail( HIW "你正在舞「鳳舞九天」！\n" NOR);

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");

        if ((int)me->query_skill("kurong-changong", 1) < 130 &&
            (int)me->query_skill("duanshi-xinfa",1) < 130)
                return notify_fail( HIW "你的內功修為未到，無法施展「鳳舞九天」。\n" NOR);

        if ((int)me->query_skill("feifeng-whip", 1) < 150)
                return notify_fail( HIW "你的飛鳳鞭法修為還不夠，尚未領悟到「鳳舞九天」。\n" NOR);

        if( query("max_neili", me) <= 1000 )
                return notify_fail( HIW "你的內力修為不足，勁力不足以施展「鳳舞九天」！\n" NOR);

        if( query("neili", me)<500 )
                return notify_fail( HIW "你現在內力不夠，勁力不足以施展「鳳舞九天」！\n" NOR);

        if( query("jingli", me) <= 300 )
                return notify_fail( HIW "你的精力不足，無法施展「鳳舞九天」！\n" NOR);

        if( query("gender", me) != "女性" )
                return notify_fail( HIW "「鳳舞九天」只有女性能舞！\n" NOR);

        if (! living(target))
                return notify_fail( HIW "對方都已經這樣了，還舞給誰看啊！\n" NOR);

        message_vision(MAG"$N向後縱身一躍，翩翩起舞，手中的"NOR+weapon->name()+NOR+MAG"響起陣陣鳳鳴，舞姿奇詭莫測，變化無端，宛如鳳凰一般剎是好看。\n\n" NOR, me);

        if( random(query("per", me))+8>20 )
        {
                message_vision(HIR"突然$n一個失神，被$N的動作所吸引，頓感心曠神怡，心猿意馬，被$N的舞姿迷的神魂顛倒！\n\n"NOR, me, target);
                target->start_busy(random(5)+5);

                if( query_temp("weapon", target)){
                        weapon1=query_temp("weapon", target);
                        if( query("combat_exp", me)<random(query("combat_exp", target)*8/5)){
                                message_vision(HIW"$n手指一鬆，"NOR+weapon1->name()+NOR HIW"險些脫手！\n" NOR, me, target);
                        }
                        else {
                                message_vision(HIW"$n手上一鬆，不由自主的丟下了"NOR+weapon1->name()+NOR HIW"！\n" NOR, me, target);
                                weapon1->unequip();
                                weapon1->move(environment(target));
                                target->reset_action();
                        }
                }
                extra = (int)me->query_skill("feifeng-whip",1);
                dodge = extra*3/4 + random(extra/2);
                damage = extra/3 + random(extra/2);
                parry = extra*3/4 + random(extra/5);

                addn_temp("apply/dodge", dodge, me);
                addn_temp("apply/damage", damage, me);
                addn_temp("apply/parry", -parry, target);

                set_temp("jiutian", 25+extra/6, me);
                call_out("checking", 1, me, target, weapon, dodge, damage, parry);

                me->start_busy(1+random(2));
                addn("neili", -250, me);
                addn("jing", -50, me);
        }
        else
        {
                message_vision(RED"就看$n收斂心神，心如明鏡，全神貫注，並未被$N的舞姿所迷。\n"NOR, me, target);
                me->start_busy(random(5)+2);
        }
        return 1;
}

void checking(object me, object target, object weapon, int dodge, int damage, int parry)
{
        if (!living(me) || me->is_ghost())
        {
                remove_effect(me, target, dodge, damage, parry);
                return ;
        }
        if( query_temp("jiutian", me)){
        if( !me->is_fighting() )
        {
                message_vision(HIY"\n$N向後一跳，收起了步伐。\n"NOR, me);
                remove_effect(me, target, dodge, damage, parry);
                tell_object(me, HIM"\n你身形一止，速度慢了下來。\n\n"NOR);
                return;
        }
        else if( environment(weapon) != me || weapon != query_temp("weapon", me) )
        {
                message_vision(HIY"\n$N腳步一頓，停止了舞蹈。\n"NOR, me);
                remove_effect(me, target, dodge, damage, parry);
                tell_object(me, HIM"\n你感覺到氣血不順，速度漸漸慢了下來。\n\n"NOR);
                return;
        }
        else if( query("weapon_prop", weapon) == 0 )
        {
                message_vision(HIY"\n$N手中的"NOR+weapon->name()+NOR HIY"已毀，不得不停下腳步。\n"NOR, me);
                remove_effect(me, target, dodge, damage, parry);
                return;
        }
        else if (me->query_skill_mapped("force") != "kurong-changong")
        {
                remove_effect(me, target, dodge, damage, parry);
                tell_object(me, HIY"\n你感到內息不暢，不得不停下腳步。\n\n" NOR);
                return;
        }
        if (random(5) == 1)
                message_vision(HIG"$N身姿如同九天鳳凰，瀟洒飄逸又威勢逼人！\n"NOR,me);
                addn_temp("jiutian", -1, me);
                call_out("checking", 1, me, target, weapon, dodge,damage, parry);
        }
        else {
                remove_effect(me, target, dodge, damage, parry);
                tell_object(me, HIM"\n你感覺到氣血不順，速度漸漸慢了下來。\n\n"NOR);
        }
}

void remove_effect(object me, object target, int dodge, int damage, int parry)
{
        if (!me) return;
        delete_temp("jiutian", me);
        addn_temp("apply/dodge", -dodge, me);
        addn_temp("apply/damage", -damage, me);
        if (!target) return;
        addn_temp("apply/parry", parry, target);
}
