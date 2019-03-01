// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "十龍十象" NOR; }

inherit F_SSERVER;

string final1(object me, object target, int damage, object weapon, int lvl);
string final2(object me, object target, int damage);
string final3(object me, object target, int damage, object weapon, int lvl);
string final4(object me, object target, int ap);
void tian_end(object me, object target);

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int lvl;
        
        if( !query("reborn/times", me) ) 
                return notify_fail("你所使用的外功中沒有這個功能。\n"); 

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+ "只能對戰鬥中的對手使用。\n");
        
        if( me->is_busy() )
                return notify_fail("你正忙著呢！\n");
                
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) ) 
                return notify_fail(name() + "只能空手使用。\n"); 

        if ((int)me->query_skill("force", 1) < 1000)
                return notify_fail("你內功修為不夠，難以施展" +name()+ "。\n");

        if( query("max_neili", me)<100000 )
                return notify_fail("你內力修為不夠，難以施展" +name()+ "。\n");

        lvl = (int)me->query_skill("longxiang-gong", 1);
        if (lvl < 1000)
                return notify_fail("你龍象般若功火候不夠，難以施展" +name()+ "。\n");

        if( query("neili", me)<10000 )
                return notify_fail("你現在真氣不夠，難以施展" +name()+ "。\n");

        if (me->query_skill("martial-cognize", 1) < 400)
                return notify_fail("你武學修養不足，難以施展" +name()+ "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        message_combatd(HIM "\n$N" HIM "運起十龍十象之力，霎時金波流轉，罡氣籠罩全身，\n"
                        HIM "$N" HIM "縱聲長嘯，漫天掌力狂湧而去，當真石破天驚，威力無比，襲向$n" HIM "。\n" NOR, me, target);

        message_combatd(HIM "十龍十象之一龍一象\n" NOR, me, target);
        
        me->addn("neili", -10000);
        
        // 第一招，判斷對方臂力
        ap = attack_power(me, "unarmed") + me->query_str()*10;
        dp = defense_power(target, "parry") + target->query_str()*10;
        
        damage = damage_power(me, "unarmed");
        
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + random(10),
                                         (: final1, me, target, damage, lvl :));
        } else
        {
                msg = HIC "$n" HIC "氣貫雙臂，凝神以對，竟將$N" HIC "之力卸去。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "十龍十象之二龍二象\n" NOR, me, target);
        
        ap = attack_power(me, "unarmed") + me->query_int()*10;
        // 第二招，判斷對方悟性
        dp=defense_power(target,"parry")+target->query_int()*10;

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + random(10),
                                          HIY "$n" HIY "冷笑一聲，覺得$N" HIY "此招膚淺之極，于"
                                          "是隨意招架，猛然間，「噗嗤」！一聲，雙掌"
                                          HIY "已穿透$n" HIY "的胸膛，鮮血不斷湧出。\n" NOR, me , target);
        } else
        {
                msg = HIC "$n" HIC "會心一笑，看出$N" HIC "這招中的破綻，隨意施招竟將這招化去。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "十龍十象之三龍三象\n" NOR, me, target);
        
        ap = attack_power(me, "unarmed") + me->query_con()*10;
        // 第三招，判斷對方根骨
        dp = defense_power(target, "force") + target->query_con()*10;

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + random(10),
                                           (: final2, me, target, damage :));
        } else
        {
                msg = HIC "$n" HIC "默運內功，內勁貫于全身，奮力抵擋住$N" HIC "這招。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "十龍十象之四龍四象\n" NOR, me, target);

        // 第四招，判斷對方身法

        ap = attack_power(me, "unarmed") + me->query_dex()*10;
        dp = defense_power(target, "dodge") + target->query_dex()*10;

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + random(10),
                                          (: final3, me, target, damage, lvl :));
        } else
        {
                msg = HIC "$n" HIC "見這招來勢兇猛，身形疾退，瞬間飄出三"
                      "丈，方才躲過$N" HIC "這招。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "十龍十象之五龍五象\n" NOR, me, target);

        // 第五招，判斷對方內力

        if( query("max_neili", me)>query("max_neili", target)*2 )
        {
                 msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + random(10),
                        HIY "$n" HIY "思慮未定，$N" HIY "的內勁已破體而入，"
                            "$n" HIY "受此重擊，喉口一甜，嘔出數口" HIR "鮮血" HIY "。\n" NOR, me, target);
        } else
        {
                msg = CYN "$n" CYN "知道$N這招無可抵擋，"
                       CYN "當即飛身躍起丈許，躲閃開來。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "十龍十象之六龍六象\n" NOR, me, target);

        // 第六招，判斷對方江湖閱歷

        if( query("score", me)>query("score", target)*2 )
        {
                 msg = COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 80 + random(15),
                                          (: final4, me, target, damage :));
        } else
        {
                msg = CYN "$n" CYN "會心一笑，一招擊在氣牆中心，竟將此招破去。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "十龍十象之七龍七象\n" NOR, me, target);
        
        // 第七招，判斷對方基本內功
        
        ap = attack_power(me, "unarmed") + me->query_skill("force", 1);
        dp = defense_power(target, "parry") + target->query_skill("force", 1);
        
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + random(10),
                        HIY "$n" HIY "思慮未定，$N" HIY "的內勁已破體而入，"
                            "$n" HIY "受此重擊，喉口一甜，嘔出數口" HIR "鮮血" HIY "。\n" NOR, me, target);
        } else
        {
                msg = CYN "$n" CYN "面對$N" CYN "這排山倒海攻勢，完全"
                                          CYN "無法抵擋，唯有退後幾步，凝神應對。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "十龍十象之八龍八象\n" NOR, me, target);
        
        // 第八招，判斷對方基本招架
        
        ap = attack_power(me, "unarmed") + me->query_skill("parry", 1);
        dp = defense_power(target, "parry") + target->query_skill("parry", 1);
        
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + random(10),
                        HIY "$n" HIY "騰挪閃躲，竭盡全力，也沒辦法躲開氣旋，被擊了個正著！\n" NOR, me, target);
        } else
        {
                msg = HIC "$n" HIC "見這招來勢兇猛，身形疾退，瞬間飄出三"
                      "丈，方才躲過$N" HIC "這招。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "十龍十象之九龍九象\n" NOR, me, target);
        
        // 第九招，判斷對方基本輕功
        
        ap = attack_power(me, "unarmed") + me->query_skill("dodge", 1);
        dp = defense_power(target, "parry") + target->query_skill("dodge", 1);
        
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(10),
                                          HIY "$n猶如和數十人戰鬥，哪裡還能抵擋的住，"
                                          HIY "僅僅數息之間，已經身中數招！\n" NOR, me , target);
        } else
        {
               msg = CYN "$n大吃一驚，連忙退後，居然"
                      CYN "僥幸躲開了這一招！\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "十龍十象之十龍十象\n" NOR, me, target);
        
        // 第十招，判斷對方武學修養
        
        ap = attack_power(me, "unarmed") + me->query_skill("martial-cognize", 1);
        dp = defense_power(target, "parry") + target->query_skill("martial-cognize", 1);
        
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + random(10),
                        HIY "$n" HIY "面對威力如此強大的一招，根本無法招架，被重重擊中，\n"
                        HIY "五臟六腑翻騰不休，口中" HIR "鮮血" HIY "如箭般噴出！\n" NOR, me, target);
        } else
        {
                msg = CYN "$n在身邊布下層層內勁，將$N" CYN "凌厲的攻勢盡數抵擋。\n" NOR;
        }
                     
        me->start_busy(6 + random(5));
        return 1;
}

string final1(object me, object target, int damage, int lvl)
{
        addn("neili", -(lvl+random(lvl)), target);

        return  HIY "$n" HIY "卻覺$N" HIY "這招氣勢恢弘，于是運力奮力抵擋。但是無奈這"
                "招威力驚人，$n" HIY "悶哼一聲，倒退幾步，頓覺內息渙散，身"
                "上早已染滿鮮血！\n" NOR;
}

string final2(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 2, me);
        target->receive_wound("jing", damage / 4, me);
        return  HIY "$n" HIY "心中一驚，但見$N" HIY "這幾招奇異無比，招式變化莫測，"
                "但威力卻依然不減，正猶豫間，$n" HIY "卻已中招，頓感精力不濟，渾"
                "身無力。\n" NOR;
}

string final3(object me, object target, int damage, int lvl)
{
   
        target->start_busy(4 + random(3));
  
        return  HIY "$N" HIY "掌法奇妙無比，雙手時而宛若遊龍，時而"
                "宛若驚鴻，霎那間$n" HIY "已遍體鱗傷，$N" HIY "猛然將雙拳一"
                "轉，拳勢陡然加快，將$n" HIY "團團圍住，竟無一絲空隙！\n" NOR;

}

void tian_end(object me, object target)
{
        if( target && query_temp("no_perform", target) )
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口"
                                        "氣，臉色由白轉紅，看起來好"
                                        "多了。\n" NOR, target);

                        tell_object(target, HIY "你感到被擾亂的真氣"
                                            "慢慢平靜了下來。\n" NOR);
                }
        addn_temp("apply/avoid_busy", 90, target);
        addn_temp("apply/reduce_busy", 36, target);
        addn_temp("apply/avoid_weak", 90, target);
        addn_temp("apply/avoid_forget", 90, target);
        tell_object(target, HIR "你的忽視虛弱，忽視忙亂、忽視絕招冷凍能力終于解除封印。\n" NOR);
                delete_temp("no_perform", target);
        }
        return;
}

string final4(object me, object target, int ap)
{
        addn_temp("apply/avoid_busy", -90, target);
        addn_temp("apply/reduce_busy", -36, target);
        addn_temp("apply/avoid_weak", -90, target);
        addn_temp("apply/avoid_forget", -90, target);
        set_temp("no_perform", 1, target);
        remove_call_out("tian_end");
        call_out("tian_end", 10 + random(ap / 50), me, target);
        return HIY "$n" HIY "絲毫不懂此招奧妙，一個疏神，丹田已遭重創！\n" NOR +
               WHT "$n" WHT "感到自身的忽視虛弱，忽視忙亂、忽視絕招冷凍能力被封印。\n" NOR;
}