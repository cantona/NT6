#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string attack1(object me, object target, int damage);
string attack2(object me, object target, int damage);
string attack3(object me, object target, int damage);
string attack4(object me, object target, int damage);
string attack5(object me, object target, int damage);
string attack6(object me, object target, int damage);

string name() { return HIR "真﹒六道輪回" NOR; } 

int perform(object me, object target)
{
        object weapon;
        string wn, msg;
        object sroom, room;
        int ap, dp, damage;
        int wait_time;
        int in_shejingdong;

        /*
        // 檢查是否經過賽神龍效果過輪回點6點
        if( !query("scborn/perform_zhen_saishenlong", me) && !query("thborn/ok", me) )
        {
                // 輪回點大于6則自動扣除並設置標志
                if( query("scborn/cur_lunhui_point", me) >= 6 )
                {
                        addn("scborn/cur_lunhui_point", -6, me);
                        set("scborn/perform_zhen_saishenlong", 1, me);
                        me->save();
                }
                // 否則無法施展該招
                else
                        return notify_fail("對不起，由于你的輪回點有問題，你暫時無法施展該招，詳情參見新聞。\n");
        }
        */
        
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "lunhui-sword")
                return notify_fail("需要將六道輪回劍激發為內功才能施展。\n");

        if( query("max_neili", me)<10000 )
                return notify_fail("你的內力修為不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("buddhism", 1) < 200)
                return notify_fail("你對禪宗心法參悟不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("lunhui-sword", 1) < 900)
                return notify_fail("你六道輪回劍火候不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "lunhui-sword")
                return notify_fail("你沒有激發六道輪回劍，難以施展" + name() + "。\n");

        if( query("neili", me)<4000 )
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");
        
        wait_time = 30;
        
        if (me->query_skill("yinyang-shiertian", 1) >= 1000)
                wait_time = 25;
                
        if (me->query_skill("yinyang-shiertian", 1) >= 1400)
                wait_time = 20;
                
        if (me->query_skill("yinyang-shiertian", 1) >= 1600)
                wait_time = 15;
                
        if( time()-query_temp("last_perform_zhen", me)<wait_time )
                return notify_fail("你剛施展過" + name() + "，體內真氣還沒有完全順暢，此時不宜強行運功。\n");
                
                                
        wn = weapon->name();

        message_combatd(HIW "$N" HIW "面露拈花之意，祭起手中" + wn +
                        HIW "，霎時碧波流轉，華光萬丈，說不盡的祥和。"
                        "\n" NOR, me, target);

        //  記錄下最初的房間
        if (! objectp(sroom = environment(me)))
                return 1;

        if (base_name(sroom) == "/d/shenlong/shejingdong" ||
            base_name(sroom) == "/d/shenlong/huodong1" ||
            query("fight_room", sroom) )
                in_shejingdong = 1;

        ap = attack_power(me, "sword"); 
        dp = defense_power(target, "force");

        damage = damage_power(me, "sword")*3;

        // 六道輪回之人間道
        room = find_object("/d/death/liudaolunhui/rendao");
        if (! room) room = load_object("/d/death/liudaolunhui/rendao");

        if (! in_shejingdong)me->move(room);
        if (! in_shejingdong)target->move(room);

        message_combatd(HIY "\n$N" HIY "左手輕輕一撥，右手所持的" + wn +
                       HIY "叮呤做響，劍姿說不出的瀟洒妙曼。\n" NOR, me, target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200,
                                           (: attack1, me, target, damage :));
        } else
        {
                msg = CYN "可是$n" CYN "收斂心神，奮力招"
                      "架，將劍招卸于無形。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 六道輪回之畜生道
        room = find_object("/d/death/liudaolunhui/chushengdao");
        if (! room) room = load_object("/d/death/liudaolunhui/chushengdao");

        if (! in_shejingdong)me->move(room);
        if (! in_shejingdong)target->move(room);

        message_combatd(HIY "\n卻見$N" HIY "面無表情，將手中" + wn +
                       HIY "猛的往前一遞，猶如毒蛇般噬向$n" HIY "。\n"
                       NOR, me, target);

        if (ap * 4 / 5  + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200,
                                           (: attack2, me, target, damage :));
        } else
        {
                msg = CYN "可是$n" CYN "收斂心神，奮力招"
                      "架，將劍招卸于無形。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 六道輪回之餓鬼道
        room = find_object("/d/death/liudaolunhui/eguidao");
        if (! room) room = load_object("/d/death/liudaolunhui/eguidao");

        if (! in_shejingdong)me->move(room);
        if (! in_shejingdong)target->move(room);

        message_combatd(HIY "\n$N" HIY "一聲長嘆，左手捏著劍訣，忽聞" +
                       wn + HIY "上血腥之氣漸濃，朝$n" HIY "迎頭斬落。\n"
                       NOR, me, target);

        if (ap * 4 / 5  + random(ap) > dp)
        {
                if( query("death_skill/guimai", target) )
                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage / 2, 100,
                                                   (: attack3, me, target, damage :));                
                else
                
                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200,
                                                   (: attack3, me, target, damage :));
        } else
        {
                msg = CYN "可是$n" CYN "收斂心神，奮力招"
                      "架，將劍招卸于無形。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 六道輪回之修羅道
        room = find_object("/d/death/liudaolunhui/xiuluodao");
        if (! room) room = load_object("/d/death/liudaolunhui/xiuluodao");

        if (! in_shejingdong)me->move(room);
        if (! in_shejingdong)target->move(room);

        message_combatd(HIY "\n忽見$N" HIY "身形微晃，頓時幻出十數個身"
                       "影，十數柄" + wn + HIY "齊向$n" HIY "刺去。"
                       "\n" NOR, me, target);

        if (ap * 4 / 5  + random(ap) > dp)
        {
                if( query("death_skill/lonely", target) )
                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage / 2, 100,
                                                   (: attack4, me, target, damage :));                
                else
                
                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200,
                                                   (: attack4, me, target, damage :));
        } else
        {
                msg = CYN "可是$n" CYN "收斂心神，奮力招"
                      "架，將劍招卸于無形。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 六道輪回之地獄道
        room = find_object("/d/death/liudaolunhui/diyudao");
        if (! room) room = load_object("/d/death/liudaolunhui/diyudao");

        if (! in_shejingdong)me->move(room);
        if (! in_shejingdong)target->move(room);

        message_combatd(HIY "\n緊接著$N" HIY + wn + HIY "一顫，有若龍吟"
                       "，劍身騰起一道滔天寒流，向四周擴散開去。\n" NOR,
                       me, target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200,
                                           (: attack5, me, target, damage :));
        } else
        {
                msg = CYN "可是$n" CYN "收斂心神，奮力招"
                      "架，將劍招卸于無形。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 六道輪回之天極道
        room = find_object("/d/death/liudaolunhui/tiandao");
        if (! room) room = load_object("/d/death/liudaolunhui/tiandao");

        if (! in_shejingdong)me->move(room);
        if (! in_shejingdong)target->move(room);

        message_combatd(HIY "\n$N" HIY "身外化身，劍外化劍，手中" + wn +
                       HIY "便似蛟龍騰空，撥雲見日，天地為之失色。\n"
                       NOR, me, target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                if( query("death_skill/emperor", target) )
                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage / 2, 100,
                                                   (: attack6, me, target, damage :));                
                else
                
                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200,
                                                   (: attack6, me, target, damage :));
        } else
        {
                msg = CYN "可是$n" CYN "收斂心神，奮力招"
                      "架，將劍招卸于無形。\n" NOR;
        }
        message_combatd(msg, me, target);

        me->start_busy(4 + random(4));
        addn("neili", -4000, me);
        set_temp("last_perform_zhen", time(), me);
        
        // 為什麼提行？為了畫面更為賞心悅目而已
        tell_object(me, "\n\n");
        tell_object(target, "\n\n");

        // 轉移回最初的房間
        if (! in_shejingdong)me->move(sroom);
        if (! in_shejingdong)target->move(sroom);

        return 1;
}

string attack1(object me, object target, int damage)
{
        string msg;

        msg = HIR "$n" HIR "只覺心頭一陣凄苦，竟忍不住要落"
              "下淚來，喉嚨一甜，嘔出一口鮮血。\n" NOR;

        if( !query_temp("liudaolunhui", target) )
        {
                msg += WHT "$p忽然察覺到全身的力氣竟似一絲"
                       "絲遠離自己而去，無助之極。\n" NOR;

                addn_temp("apply/attack", -damage/10, target);
                addn_temp("apply/parry", -damage/10, target);
                addn_temp("apply/dodge", -damage/10, target);
                
                if( query_temp("apply/attack", target)<0 )
                        set_temp("apply/attack", 0, target);
                if( query_temp("apply/parry", target)<0 )
                        set_temp("apply/parry", 0, target);
                if( query_temp("apply/dodge", target)<0 )
                        set_temp("apply/dodge", 0, target);
                                                                     
                set_temp("liudaolunhui", 1, target);
        }
        return msg;
}

string attack2(object me, object target, int damage)
{
        object weapon;
        string wn, msg;

        msg = HIR "忽然間$n" HIR "感到胸口處一陣火熱，劍氣"
              "襲體，帶出一蓬血雨。\n" NOR;

        if( objectp(weapon=query_temp("weapon", target)) )
        {
                // 此特效對天晶無效
                if( query("material", weapon) == "tian jing")return msg;
                
                wn = weapon->name();
                msg += WHT "忽聽「鏘鏘鏘」幾聲脆響，$n" WHT "的" + wn +
                       WHT "竟被$N" WHT "絞成了塊塊碎片。\n" NOR;

                set("consistence", 0, weapon);
                weapon->move(target);
        }
        return msg;
}

string attack3(object me, object target, int damage)
{
        int shd;
        string msg;

        msg = HIR "劍鋒過處，卷起漫天血浪，$n" HIR "只感頭暈目"
              "眩，四肢乏力，難以再戰。\n" NOR;

        if( query_temp("shield", target) )
        {
                shd=query_temp("apply/armor", target);

                addn_temp("apply/armor", -shd, target);
                                        
                if( query_temp("apply/armor", target)<0 )
                        set_temp("apply/armor", 0, target);
                        
                delete_temp("shield", target);

                msg += WHT "$N" WHT "氣勁湧至，宛若刀割，頓時將$n"
                       WHT "的護體真氣摧毀得盪然無存。\n" NOR;
        }
        return msg;
}

string attack4(object me, object target, int damage)
{
        object cloth, armor;
        string cn, an, msg;

        msg = HIR "$n" HIR "頓時大驚失色，瞬間已被$N" HIR "連中"
              "數劍，直削得血肉模糊。\n" NOR;

        if( objectp(cloth=query_temp("armor/cloth", target)) )
        {
                // 此特效對天晶無效
                if( query("material", cloth) == "tian jing")return msg;
                              
                cn = cloth->name();
                msg += WHT "忽聽轟然聲大作，$n" WHT "身著的" + cn +
                       WHT "在$N" WHT "內力激盪下，竟被震得粉碎。\n"
                       NOR;

                set("consistence", 0, cloth);
                cloth->move(target);
        } else
        if( objectp(armor=query_temp("armor/armor", target)) )
        {
                // 此特效對天晶無效
                if( query("material", armor) == "tian jing")return msg;
                                
                an = armor->name();
                msg += WHT "忽聽「哧啦」一聲脆響，$n" WHT "身著的" +
                       an + WHT "竟被$N" WHT "震裂，化成塊塊碎片。\n"
                       NOR;

                set("consistence", 0, armor);
                armor->move(target);
        }
        return msg;
}

string attack5(object me, object target, int damage)
{
        string msg;

        msg = HIR "只見$n" HIR "全身一陣抽搐，被劍鋒所攜的極寒氣流"
              "包裹其中，刺痛難當。\n" NOR;

        if (! target->query_condition("poison"))
        {
                // 此招對朱蛤奇緣玩家無效
                if( query("death_skill/zhuha", target))return msg;
                
                target->affect_by("poison",
                        (["level":query("jiali", me)*3+random(query("jiali", me)),
                           "name"     : "煉獄寒燄",
                           "id":query("id", me),
                           "duration" : 80 ]));

                msg += WHT "霎時間$n" WHT "忽覺一股奇寒散入七經八脈"
                       "，仿佛連血液都停止了流動。\n" NOR;
        }
        return msg;
}
void clear_no_exert(object target)
{
        if (! objectp(target))return;
        
        delete_temp("no_exert", target);
}

string attack6(object me, object target, int damage)
{

        string msg;

        msg = HIR "$N" HIR "劍勢迅猛之極，令$n" HIR "毫無招架余地，"
              "竟鎮怯當場，素手待斃。\n" NOR;

        if( !query_temp("no_exert", target) )
        {
                // 此招對六陰鬼脈玩家無效
                if( query("death_skill/guimai", target))return msg;
                
                set_temp("no_exert", 1, target);
                remove_call_out("clear_no_exert");
                call_out("clear_no_exert", 20, target);

                msg += WHT "$n" WHT "只感到全身真氣渙散，丹元瓦解，似"
                       "乎所有的武功竟都消逝殆盡。\n" NOR;
        }
        return msg;
}