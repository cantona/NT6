// fanchang.c 梵唱

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, j, skill, damage;

        skill = me->query_skill("force");
        if( query("neili", me)<skill*3 )
                return notify_fail("你的內力不夠。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力修為不夠。\n");

        if( query("shen", me)<10000 )
                return notify_fail("佛門梵唱需要高深的定力，你氣色不正，難以施展！\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("在這裡不能攻擊他人。\n");

        if( me->query_skill("buddhism", 1) < 100 )
                return notify_fail("你連禪宗心法還未完全領悟，何以施展佛門梵唱絕學？\n");

        if( me->query_skill("yijinjing", 1) < 100 )
                return notify_fail("你連易筋經還未完全領悟，何以施展佛門梵唱絕學？\n");

        addn("neili", -skill/2, me);
        me->start_busy(1);

        message_combatd(YEL"\n$N深深地吸一口氣，面露寶象，一聲"BLINK+HIY"阿…彌…陀…佛…"YEL"梵音回旋環繞，所有人都為之一震！\n\n" NOR, me);

        if( intp(j=query_temp("yueyin", me) )
        && me->query_skill("yijinjing", 1) > 200
        && me->query_skill("buddhism", 1) > 200 )
        {
                addn_temp("apply/dex", j, me);
                addn_temp("apply/defense", j*2, me);
                me->clear_condition("no_perform");
                delete_temp("yueyin", me);
                message_combatd(HIW"$N心情於瞬息之間接連數變，恢復了明智！\n\n"NOR, me);
        }

        ob = all_inventory(environment(me));

        for(i=0; i<sizeof(ob); i++) {
                if( !ob[i]->is_character() || !living(ob[i]) || ob[i]==me ) continue;
                if( skill < ob[i]->query_skill("force")/2 ) continue;
                if( intp(j=query_temp("yueyin", ob[i]) )
                && me->query_skill("yijinjing", 1) > 200
                && me->query_skill("buddhism", 1) > 200 ){
                        addn_temp("apply/dex", j, ob[i]);
                        addn_temp("apply/defense", j*2, ob[i]);
                        ob[i]->clear_condition("no_perform");
                        delete_temp("yueyin", ob[i]);
                        tell_object(ob[i], HIW"你心情於瞬息之間接連數變，恢復了明智！\n\n"NOR);
                        continue;
                }

                if( ob[i]->is_fighting() && !ob[i]->is_killing()){
                        if( query("shen", ob[i])>0){
                                ob[i]->remove_all_enemy();
                                message_vision("\n$N受到$n感招，身行向後一躍，跳出戰圈不打了。\n", ob[i], me);
                                continue;
                        }
                        else if( query("shen", ob[i])>-10000 && query("combat_exp", me)>query("combat_exp", ob[i])){
                                ob[i]->remove_all_enemy();
                                addn("shen", skill*10, ob[i]);
                                message_vision("\n$N全身一震，臉上邪氣稍減，跳出戰圈不打了。\n", ob[i], me);
                                continue;
                        }
                        else if( query("combat_exp", me)>query("combat_exp", ob[i])*2){
                                ob[i]->remove_all_enemy();
                                message_vision("\n$N向後一跳，哈哈道：$n多心了，我們不過切磋切磋罷了。\n", ob[i], me);
                                continue;
                        }
                }

                damage = skill * 2;
                if( random(skill)>ob[i]->query_skill("force")/2 && query("shen", ob[i])<0){
                        ob[i]->receive_damage("jing", damage/2, me);
                        if( query("jing", ob[i])<10)set("jing", 10, ob[i]);
                        addn("neili", -damage, ob[i]);
                        if( query("neili", ob[i])<20)set("neili", 20, ob[i]);
                        tell_object(ob[i], "你覺得心神一震，全身出了一身的冷汗！\n");
                }
                if( ob[i]->is_killing(query("id", me))){
                        if(random(2) == 1)
                                ob[i]->apply_condition("no_perform", 2+random(2)+ob[i]->query_condition("no_perform"));
                        else    ob[i]->apply_condition("no_exert", 2+ob[i]->query_condition("no_exert"));
                        tell_object(ob[i], "你一驚，總覺得這梵唱有一股說不出的壓迫感，使你感到很不舒服！\n");
                        continue;
                }

                if( userp(ob[i]) && query("shen", ob[i])<0 && random(3) == 1){
                        message_vision("$N大喝一聲：快閉嘴！惹得"+RANK_D->query_self_rude(ob[i])+"火起！\n", ob[i]);
                        COMBAT_D->do_attack(ob[i],me,query_temp("weapon", ob[i]),1);
                }

        }
        return 1;
}

int help(object me)
{
        write(HIY"\n易筋經之「金剛梵唱」："NOR"\n");
        write(@HELP
        金剛，堅利之意，歷百劫千生，流轉六道，而覺性不壞。即以金剛之堅，喻
        般若體；以金剛之利，喻般若用。梵唱乃是將一口真氣以祥合之意唱出，內
        夾伏魔神功，能抗拒心魔，清心明志，使人懸崖勒馬。

        要求：  易筋經等級 100 以上；
                易筋經等級 100 以上；
                正氣 10000 以上；
                最大內力 1500 以上；
                內力為內功等級三倍以上。
HELP
        );
        return 1;
}