#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";

string name() { return HIY "十二重天" NOR; }



////////////////////////////////////////
//1  判斷內力
//2  判斷音律修養
//3  判斷佛學及道學修養
//4  判斷江湖閱歷
//5  判斷先天臂力
//6  判斷後天臂力及unarmed
//7  判斷先天悟性
//8  判斷後天悟性及literate
//9  判斷先天根骨
//10 判斷後天根骨及force
//11 判斷先天身法
//12 判斷後天身法及dodge
///////////////////////////////////////

string final(object me, object target, int damage);

int perform(object me, object target)
{
        int damage, damage1;
        int p;
        string msg, cl, wp;
        int ap, dp, dp1;
        int lvl;
        object weapon, cloth;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+ "只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("force", 1) < 1200)
                return notify_fail("你內功修為不夠，難以施展" +name()+ "。\n");

        if( query("max_neili", me)<50000 )
                return notify_fail("你內力修為不夠，難以施展" +name()+ "。\n");

        if( query("max_jingli", me)<10000 )
                return notify_fail("你精力修為不夠，難以施展" +name()+ "。\n");

        lvl = (int)me->query_skill("yinyang-shiertian", 1);
        if (lvl < 1200)
                return notify_fail("你陰陽九轉十二重天火候不夠，難以施展" +name()+ "。\n");

        if( query("neili", me)<12000 )
                return notify_fail("你現在真氣不夠，難以施展" +name()+ "。\n");

        if (me->query_skill("martial-cognize", 1) < 500)
                return notify_fail("你武學修養不足，難以施展" +name()+ "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        message_combatd(HIM "\n$N" HIM "口中默念：天道無常。心神沉入十二重天境界，"
                     "連空間似乎也扭曲了起來。$n" HIM "大驚失色，仿佛已身在異界！\n" NOR, me, target);


        ap = attack_power(me, "force");

        damage = damage_power(me, "force");

        if( query_temp("weapon", me) )
        {
                damage+=query_temp("apply/damage", me);
        } else
        {
                damage+=query_temp("apply/unarmed_damage", me);
        }

        damage *= 10;

        dp = defense_power(target, "dodge") + target->query_skill("yinyang-shiertian", 1);

        // 第一招，判斷對方內力
        message_combatd(HIW "$N" HIW "雙臂一震，一股渾厚至極的內勁洶湧澎湃，"
                     "帶著排山倒海之勢向$n" HIW "席卷而至。\n" NOR, me, target);

        damage1 = 0;

        if (ap * 2 / 3 + random(ap) > dp)
        {
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg = HIW "$n" HIW "舉臂欲擋,然而$N" HIW "渾厚的內力無可抵御，"
                              "剎那間就將$n" HIW "全身骨頭壓碎。" NOR "( $n" RED "受傷過重，已"
                              "經有如風中殘燭，隨時都可能斷氣。" NOR ")\n";
                        damage1 = -1;
                        addn("neili", -2000, me);
                } else
                {
                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage / 2, me);
                        target->receive_damage("jing", damage / 4, me);
                        target->receive_wound("jing", damage / 8, me);
                        p=query("qi", target)*100/query("max_qi", target);

                        msg = HIY "$n" HIY "思慮未定，$N" HIY "的內勁已破體而入，"
                              "$n" HIY "受此重擊，喉口一甜，嘔出數口" HIR "鮮血" HIY "。\n" NOR;
                        msg += "( $n" + eff_status_msg(p) + " )\n";

                        addn("neili", -500, me);
                }
        } else
        {
                msg = CYN "$n" CYN "知道$N這招無可抵擋，"
                       CYN "當即飛身躍起丈許，躲閃開來。\n" NOR;
                addn("neili", -200, me);
        }
        message_combatd(msg, me, target);

        if (damage1 < 0)
        {
                me->start_busy(2);
                target->receive_wound("qi", damage, me);
                set("qi", 1, target);
                set("eff_qi", 1, target);
                set("jing", 1, target);
                set("eff_jing", 1, target);
                target->unconcious(me);
                return 1;
        }

        // 第二招，判斷對方音律修養
        dp1 = target->query_skill("guzheng-jifa", 1) + target->query_skill("tanqin-jifa", 1) +
              target->query_skill("chuixiao-jifa", 1) + dp;

        message_combatd(HIW "\n$N" HIW "一聲清嘯，憑借渾厚的內力，憑空吹奏起莫名的曲子,"
                     HIW "歡快中帶著一絲淡淡的憂傷，仿佛又回到了遙遠的童年。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                target->receive_damage("qi", damage / 2, me);
                target->receive_wound("qi", damage / 4, me);
                target->receive_damage("jing", damage * 2 / 3, me);
                target->receive_wound("jing", damage / 2, me);
                p=query("qi", target)*100/query("max_qi", target);

                msg = HIY "$N" HIY "吹奏間隙緩步而上，$n" HIY "卻仍沉浸在回憶之中，"
                      HIY "$N" HIY "一擊得手。\n" NOR;
                msg += "( $n" + eff_status_msg(p) + " )\n";
        } else
        {
                msg = CYN "幸而$n" CYN "精通音律，嚴陣以待，$N" CYN "無處下手。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第三招，判斷對方佛學及道學修養
        dp1 = target->query_skill("buddhism", 1) + target->query_skill("lamaism", 1) +
              target->query_skill("taoism", 1) + dp;

        message_combatd(HIW "\n$N用內力將一股醉人的幽香彌漫開來，便似一個溫柔"
                     HIW "美麗的女子臥在身側一般\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                target->receive_damage("qi", damage / 2, me);
                target->receive_wound("qi", damage / 4, me);
                target->receive_damage("jing", damage * 2 / 3, me);
                target->receive_wound("jing", damage / 2, me);
                p=query("qi", target)*100/query("max_qi", target);

                msg = HIY "霎時間$n" HIY "只感心頭滾熱，喉幹舌燥，說不出的難受。\n" NOR;
                msg += "( $n" + eff_status_msg(p) + " )\n";
        } else
        {
                msg = CYN "$n" CYN "凝神守一，絲毫不為所動。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第四招，判斷對方江湖閱歷
        dp1=query("score", target);
        dp1 /= 20000;
        if (dp1 > 10000)
                dp1 = 10000;
        if (dp1 > 2000)
        {
                dp1 -= 2000;
                dp1 /= 5;
                dp1 += 2000;
        }

        dp1 += dp;

        message_combatd(HIW "\n$N搖身一晃，頓時顯現千百人影，$n"
                     HIW "環顧左右，不知$N" HIW "真身何在。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                msg = COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 80 + random(15),
                                          (: final, me, target, damage :));
        } else
        {
                msg = CYN "$n" CYN "見多識廣，危急時刻終于看清$N"
                      CYN "招式來路，連忙飛身避開。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第五招，判斷對方先天臂力及基本招架
        dp1=query("str")*30+target->query_skill("parry", target)+dp;

        message_combatd(HIW "\n$N" HIW "大喝一聲，一招攻向$n" HIW "，雖然"
                     "簡單明了，卻有石破天驚之勢！\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage / 2, me);
                target->receive_damage("jing", damage / 4, me);
                target->receive_wound("jing", damage / 8, me);
                p=query("qi", target)*100/query("max_qi", target);

                msg = HIY "$n" HIY "面對威力如此強大的一招，根本無法招架，被重重擊中，\n"
                      HIY "五臟六腑翻騰不休，口中" HIR "鮮血" HIY "如箭般噴出！\n" NOR;
                msg += "( $n" + eff_status_msg(p) + " )\n";

                if( objectp(weapon=query_temp("weapon", target) )
                    && query("stable", weapon)<100
                   && ap / 2 + random(ap) > dp1)
                {
                        wp = weapon->name();
                        msg += HIW "只聽“鏘”的一聲脆響，$n" HIW "手"
                               "中的" + wp + HIW "在$N" HIW "內力激盪"
                               "下應聲而碎，脫手跌落在地上。\n" NOR;
                        addn("neili", -150, me);
                        set("consistence", 0, weapon);
                        weapon->move(environment(target));
                }
        } else
        {
                msg = CYN "$n" CYN "見這招來勢兇猛，身形疾退，瞬間飄出三"
                      "丈，方才躲過$N" CYN "這招。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第六招，判斷對方後天臂力及基本拳腳
        dp1 = target->query_str() * 2 + target->query_skill("unarmed", 1) + dp;

        message_combatd(HIW "\n$N" HIW "前招未落，後招又起，威勢十足的向$n"
                     HIW "當面擊到！\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                addn("neili", -(lvl+random(lvl)), target);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(10),
                                          HIY "只聽$n" HIY "一聲慘叫，被$N" HIY "內勁擊中胸前，"
                                          "“喀嚓喀嚓”斷了幾根肋骨。。\n" NOR, me , target);
        } else
        {
                msg = CYN "$n" CYN "氣貫雙臂，凝神以對，竟將$N" CYN "之力卸去。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第七招，判斷對方先天悟性及基本招架
        dp=query("int")*30+target->query_skill("parry", target)+dp1;

        message_combatd(HIW "\n$N" HIW "一招擊向$n" HIW "身前空擋，"
                     "渾厚的內力竟然形成了一個旋渦。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                target->receive_damage("qi", damage * 3 / 2, me);
                target->receive_wound("qi", damage * 2 / 3, me);
                target->receive_damage("jing", damage / 4, me);
                target->receive_wound("jing", damage / 8, me);
                p=query("qi", target)*100/query("max_qi", target);

                msg = HIY "$n" HIY "未料到$N" HIW "此招竟擊在必經之路，"
                      HIY "來不及變招，身子已經撞入內勁旋渦之中！\n" NOR;
                msg += "( $n" + eff_status_msg(p) + " )\n";
        } else
        {
                msg = CYN "$n" CYN "急忙變招，勉強從旋渦旁邊掠過。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第八招，判斷對方後天悟性及讀書寫字
        dp1 = target->query_int() * 2 + target->query_skill("literate", 1) + dp;

        message_combatd(HIW "\n$N" HIW "雙手其出，胸腹之間竟然露出一個極大的破綻！\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 95 + random(10),
                                          HIY "$n" HIY "一聲冷笑，擊向$N" HIY "胸前。"
                                          "不想招式未到,$N" HIY "的破綻早已不是破綻！\n" NOR, me , target);
        } else
        {
                msg = CYN "$n" CYN "看破此招乃是誘敵，凝神防守，並不出擊。\n" NOR;
        }
        message_combatd(msg, me, target);

                // 第九招，判斷對方先天根骨及基本招架
        dp1=query("con")*30+target->query_skill("parry", target)+dp;

        message_combatd(HIW "\n$N連發數招，層層疊疊的內勁便如一堵無形氣牆，向前疾沖而"
                     HIW "去。$n" HIW "只覺無路可退，心中大驚。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage / 2, me);
                target->receive_damage("jing", damage / 4, me);
                target->receive_wound("jing", damage / 8, me);
                p=query("qi", target)*100/query("max_qi", target);

                msg = HIY "$n還在思考如何閃避，如山般的內勁"
                      HIY "已經壓了過來，重重擊在$n" HIY "的胸口。\n" NOR;
                msg += "( $n" + eff_status_msg(p) + " )\n";

                if( objectp(cloth=query_temp("armor/armor", target) )
                    && query("stable", cloth)<100
                   && ap / 2 + random(ap) > dp1)
                {
                        cl = cloth->name();
                        msg += HIW "只聽“轟”的一聲悶響，$n" HIW "身"
                               "著的" + cl + HIW "在$N" HIW "內力激盪"
                               "下應聲而裂，化成一塊塊碎片。\n" NOR;
                        addn("neili", -150, me);
                        set("consistence", 0, cloth);
                        cloth->move(environment(target));
                }
        } else
        {
                msg = CYN "$n" CYN "會心一笑，一招擊在氣牆中心，竟將此招破去。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第十招，判斷對方後天根骨及基本內功
        dp1 = target->query_con() * 2 + target->query_skill("force", 1) + dp;

        message_combatd(HIW "\n$N" HIW "雙臂陡然暴長數尺。只聽破空之聲驟響，"
                     HIW "雙掌幻出漫天掌影，舖天蓋地向$n" HIW "攻去。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                target->receive_damage("jing", damage / 2, me);
                target->receive_wound("jing", damage / 4, me);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(10),
                             HIY "$n躲閃不及，被$N" HIY "一招擊飛了出去。\n" NOR, me , target);
        } else
        {
                msg = CYN "$n" CYN "面對$N" CYN "這排山倒海攻勢，完全"
                                          CYN "無法抵擋，唯有退後幾步，凝神應對。\n" NOR;
        }

        message_combatd(msg, me, target);

        // 第十一招，判斷對方先天身法及基本招架
        dp1=query("dex")*30+target->query_skill("parry", target)+dp;

        message_combatd(HIW "\n$N" HIW "身體猛然旋轉不定，旋起無數小氣旋，"
                     HIW "宛若流星趕月，向$n" HIW "電射而去。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage / 2, me);
                target->receive_damage("jing", damage / 4, me);
                target->receive_wound("jing", damage / 8, me);
                p=query("qi", target)*100/query("max_qi", target);

                msg = HIY "$n" HIY "騰挪閃躲，竭盡全力，也沒辦法躲開氣旋，被擊了個正著！\n" NOR;
                msg += "( $n" + eff_status_msg(p) + " )\n";

                if( objectp(cloth=query_temp("armor/cloth", target) )
                    && query("stable", cloth)<100
                   && ap / 2 + random(ap) > dp1)
                {
                        cl = cloth->name();
                        msg += HIW "只聽“轟”的一聲悶響，$n" HIW "身"
                               "著的" + cl + HIW "在$N" HIW "內力激盪"
                               "下應聲而碎，化成一塊塊碎片。\n" NOR;
                        addn("neili", -150, me);
                        set("consistence", 0, cloth);
                        cloth->move(environment(target));
                }
        } else
        {
                msg = CYN "$n大吃一驚，連忙退後，居然"
                      CYN "僥幸躲開了這一招！\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第十二招，判斷對方後天身法及基本輕功
        dp1 = target->query_dex() * 2 + target->query_skill("dodge", 1) + dp;

        message_combatd(HIW "\n$N將身法發揮到極至，幻化出千萬人形，一起撲向$n。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                if (! target->is_busy())
                        target->start_busy(4 + random(lvl / 400));
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(10),
                                          HIY "$n猶如和數十人戰鬥，哪裡還能抵擋的住，"
                                          HIY "僅僅數息之間，已經身中數招！\n" NOR, me , target);
        } else
        {
                msg = CYN "$n在身邊布下層層內勁，將$N" CYN "凌厲的攻勢盡數抵擋。\n" NOR;
        }
        message_combatd(msg, me, target);

        me->start_busy(2 + random(5));
        addn("neili", -4000-random(4000), me);
        return 1;
}

string final(object me, object target, int ap)
{
        addn_temp("apply/avoid_busy", -90, target);
        addn_temp("apply/reduce_busy", -36, target);
        addn_temp("apply/avoid_weak", -90, target);
        addn_temp("apply/avoid_locked", -90, target);
        set_temp("no_perform", 1, target);
        remove_call_out("tian_end");
        call_out("tian_end", 10 + random(ap / 50), me, target);
        return HIY "$n" HIY "絲毫不懂此招奧妙，一個疏神，丹田已遭重創！\n" NOR +
               WHT "$n" WHT "感到自身的忽視虛弱，忽視忙亂、忽視絕招冷凍能力被封印。\n" NOR;
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
        addn_temp("apply/avoid_locked", 90, target);
        tell_object(target, HIR "你的忽視虛弱，忽視忙亂、忽視絕招冷凍能力終于解除封印。\n" NOR);
                delete_temp("no_perform", target);
        }
        return;
}

