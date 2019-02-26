// perform 蛤蟆撲擊

#include <ansi.h>
#include <armor.h>
#include <combat.h>

inherit F_SSERVER;
//void tie_result(object me, object target);
void tie_hit(object me, object target);
void pu_hit(object me, object target);

int perform(object me, object target)
{
        object armor,weapon;
        int damage;
        string *limb, type, result, str;


        type = "內傷";

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
        return notify_fail("你不在戰鬥中，不能使用拍擊。\n");

        if( userp(me) && !query("can_perform/jiuyin-hamagong/puji", me) )
                      return notify_fail("你所使用的外功中沒有這種功能。\n"); 

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你手持兵器，無法施展蛤蟆功的掌法絕技。\n");

        if( (int)me->query_skill("jiuyin-hamagong", 1) < 320 )
                return notify_fail("你的蛤蟆功修為不夠。\n");

        if ( me->query_skill_mapped("force") != "jiuyin-hamagong")
                return notify_fail("你現在運使的內功並非蛤蟆功！\n");

        if (me->query_skill_mapped("unarmed") != "jiuyin-hamagong")
                return notify_fail("你沒有準備九陰蛤蟆功，不能使用「撲擊」！\n");
        if( query("neili", me) <= 1000 )
                return notify_fail("你的內力不夠！\n");

        if( query("jingli", me) <= 500 )
                return notify_fail("你的精力不夠！\n");

        delete_temp("puji_time", me);
        remove_call_out("pu_hit");
        pu_hit(me, target);

        return 1;
}

void pu_hit(object me, object target)
{
        object armor;
        int damage, time, ap, dp, pp, fap, hmg, force;
        string msg, *limb, type, result, str;
        object weapon;

        if( !target || !me->is_fighting(target) ) return;

        if( !living(me) || me->is_ghost() ) return;

        if( !target || environment(me) != environment(target) || !me->is_fighting() ) return;

        if( me->query_skill_mapped("force") != "jiuyin-hamagong" || me->query_skill_mapped("unarmed") != "jiuyin-hamagong") return;

        type = "內傷";

        hmg = (int)me->query_skill("jiuyin-hamagong", 1);
        force = (int)me->query_skill("force", 1);

        ap = COMBAT_D->skill_power(me, "unarmed", SKILL_USAGE_ATTACK);
        if( ap < 1 ) ap = 1;
        ap = ap*(1+time);

        dp = COMBAT_D->skill_power(target, "dodge", SKILL_USAGE_DEFENSE);
        if( dp < 1 ) dp = 1;
        
        pp = COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE);
        if( pp < 1 ) pp = 1;

        addn_temp("puji_time", 1, me);
        time=query_temp("puji_time", me);

        if( time == 1 ) msg = HIB "\n$N雙腿一彎，蹲下身來，“閣”的一聲大叫，運起蛤蟆功勁力，雙掌齊發，向前推出。這一\n"
                                  "推實乃$P畢生功力之所聚，$n猛然感受到山洪海嘯般的勁力襲來。\n" NOR;
        else if( time == 2 ) msg = HIM "\n$N第一推剛完，第二推又已迅速異常的趕到，前勁未衰，後勁繼至，掌風越發猛烈。\n" NOR;
        else msg = HIR "\n$N眼看前招落空，卻毫無慌亂，順勢又是一推，第"+chinese_number(time)+"推的掌風猶如沙漠風暴，一陣猛過一陣，呼嘯着向$n撲來。\n"NOR;

        message_vision(msg , me,target);
        
        addn("neili", -hmg*2, me);
        addn("jingli", -hmg/2, me);

        fap = random(ap + dp);

        if( living(target) && fap < dp ) {

                if(time == 1) message_vision(HIY "$n眼見這一推來勢兇猛，擋既不能，避又不可，當下雙足一點，躍高四尺，躲開了這一推。\n只聽身後騰的一聲大響，$N這一推的勁力激起一股狂風巨浪，頓時塵土紛揚，令人驚駭不已。\n\n" NOR, me, target);
        
                else message_vision(HIY "$n眼見這一推氣勢洶洶，當下雙足一點，側躍三尺，又躲開了這一推。\n只聽轟的一聲巨響，蛤蟆功猛勁激得灰泥瀰漫，又是一片塵土飛揚，聲勢驚人。\n" NOR, me, target);
                target->start_busy(2);
                me->start_busy(5);
                if( me->query_skill("unarmed") > time*150 && time < 5)
                        call_out("pu_hit",2+random(2),me,target);
        }

        else if( random(ap+pp)<pp && random(5) == 0 && query("race", target) == "人類" )
        {
                weapon=query_temp("weapon", target);
                if(weapon)
                {
                        weapon->unequip();
                        weapon->move(environment(target));
                        target->reset_action();
                        message_vision(HIR"$N猛覺得勁風罩來，心知不妙，手中"NOR + weapon->name() + HIR"脱手飛出，趕緊也是雙掌向前平推。這一下是以硬接硬，剎那之間，兩下里竟然凝住不動。\n"NOR, target );
                }
                else message_vision(HIR"$N猛覺勁風罩來，心知不妙，也是雙掌向前平推。這一下是以硬接硬，剎那之間，兩下里竟然凝住不動。\n\n"NOR, target );

                message("vision", HIW BLK"兩人本是忽縱忽竄、大起大落的搏擊，突然間變得兩具殭屍相似，連手指也不動一動，似乎氣也不喘一口。\n\n"NOR, environment(me), ({ me, target }) );

                addn("neili", -hmg, target);
                addn("jingli", -hmg, target);
                target->start_busy(3+random(2));
                me->start_busy(2+random(2));
                remove_call_out("tie_hit");
                call_out("tie_hit",3+random(2),me,target);
        }

        else {
                if( query_temp("armor/cloth", target) )
                        armor=query_temp("armor/cloth", target);

                if( (!living(target) || (!armor || (armor && query("armor_prop/armor", armor)<150))) && 
                    ( target->query_skill("dodge")+target->query_skill("parry") ) < random((me->query_skill("unarmed") + 
                         random(me->query_skill("force"))*2/3)) && 
                     query("race", target) == "人類" && 
                     random(2) == 1 &&
                     !query("no_nuoyi", target) )
                {
                        message_vision(HIR"只聽$N一聲慘叫，這一掌正中小腹。但見$n一個身軀突然平平飛出，騰的一響，塵土飛揚，跌在丈許之外，直挺挺的躺在地下，再也不動。\n\n"NOR, target,target );
                        target->receive_wound("qi",query("eff_qi", target),me);
                        target->receive_damage("qi",query("qi", target)+1,me);
                        addn("neili", -(query("jiali", me)+hmg/2), me);
                        addn("jingli", -(query("jiali", me)/2), me);
                }
                else
                {


            damage=(query("jiali", me)+query("age", me))*me->query_skill("force")/30+(random(hmg)+force)*time+query_temp("apply/damage", me);

                        if(damage > me->query_skill("unarmed")*(5+time) ) damage = me->query_skill("unarmed")*(5+time);
                        if(damage < me->query_skill("unarmed")*(1+time) ) damage = me->query_skill("unarmed")*(1+time);
                        addn("neili", -(query("jiali", me)+hmg), me);
                        addn("jingli", -(query("jiali", me)/2), me);

                        target->receive_damage("qi", damage,  me);
                        target->receive_wound("qi", damage/2, me);

                        target->start_busy(1+random(3));
                        me->start_busy(5); 

                        limb=query("limbs", target);

                        if(random(2) ) type = "瘀傷";
                        result = COMBAT_D->damage_msg(damage, type);
                        result = replace_string( result, "$l", limb[random(sizeof(limb))]);
                        result = replace_string( result, "$p", target->name() );
                        message_vision(result, me, target);

                        str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                        message_vision("( $N"+str+" )\n", target);
                        if(wizardp(me)) tell_object(me, "puji damage: "+damage+"\n");
                }
        }

        me->start_busy(4+random(3));
}

void tie_hit(object me, object target)
{
        int sum, n1, n2;
        string msg;

        if( !target || !me->is_fighting(target) ) return;

        if( !living(me) || me->is_ghost() ) return;

        if( !target || environment(me) != environment(target) || !me->is_fighting() ) return;

        sum = me->query_skill("force") + me->query_skill("unarmed") + target->query_skill("force") + target->query_skill("parry");
        n1=query("neili", me);
        n2=query("neili", target);

        addn("neili", -100*sum/(me->query_skill("force")+me->query_skill("unarmed")), me);
        if( query("neili", me)<0)set("neili", 0, me);

        addn("neili", -150*sum/(target->query_skill("force")+target->query_skill("parry")), target);
        if( query("neili", target)<0)set("neili", 0, target);

        if( n1 > 3000 && n2 > 3000) {
                msg = WHT"此時雙方掌力均極強勁，欲分勝負，非使對方重創不可。\n"NOR;

                if( n1 > n2 )
                msg += HIW"二人又僵持一會，$n頭頂透出一縷縷的白氣，漸漸越來越濃，就如蒸籠一般。\n"NOR;
                else msg += HIW"二人又僵持一會，$N頭頂透出一縷縷的白氣，漸漸越來越濃，就如蒸籠一般。\n"NOR;
        }

        else {

                if( n1 > n2 ) msg = WHT"$N不斷催動蛤蟆功猛勁，毫無衰頹跡象。稍過片刻，$n已是全身大汗淋漓。\n"NOR;
                else msg = WHT"$N臉上黑氣大盛，將蛤蟆功發揮到了極致。稍過片刻，$N已是全身大汗淋漓。$n似乎依然中氣十足，頭頂熱氣蒸蒸而上。\n"NOR;
                }

        message_vision(msg , me,target );


        if( query("neili", me)>0 && query("neili", target)>0 && me->is_busy() && target->is_busy() && living(me) && living(target) )
        {
                target->start_busy(3+random(2));
                me->start_busy(3+random(2));
                remove_call_out("tie_hit");
                call_out("tie_hit",2+random(2), me,target);
                return;
        }

        if( query("neili", target) <= 0 )
        {
                message_vision(HIR "\n$N突然喘不過氣來，全身發抖，原來內力已全部耗盡。突聞前胸一片骨裂之聲，已被九陰蛤蟆功一掌擊中，哼也哼不出一聲，仰身向後跌倒，雙眼緊閉，臉如白紙，端的是生死難料。\n\n" NOR, target);
                target->receive_wound("qi",query("eff_qi", target),me);
                target->receive_damage("qi",query("eff_qi", target)+1,me);
                return;
        }

        if( query("neili", me) <= 0 )
        {
                message_vision(HIR "\n$N臉上黑氣大作，突然喘不過氣來，全身發抖，原來內力已全部耗盡。蛤蟆功立時全部反彈回來，但聞前胸一片骨裂之聲，哼也哼不出一聲，俯身跌倒，雙眼緊閉，臉如黑墨，端的是生死難料。\n\n" NOR, me);
                me->receive_wound("qi",query("eff_qi", me),target);
                me->receive_damage("qi",query("eff_qi", me)+1,target);
        }

//      remove_call_out("tie_result");
//      call_out("tie_result",1,me,target);
}
