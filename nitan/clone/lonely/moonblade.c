// moonblade.c 圓月彎刀

#include <weapon.h>
#include <ansi.h>

//inherit F_OBSAVE;
inherit BLADE;

string do_wield();
string do_unwield();

void create()
{
        set_name(HIW "圓月彎刀" NOR, ({ "moon blade", "blade", "moon" }));
        set_weight(1500);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIW "此刀乃魔教鎮教之寶，威力無比，圓月刀法配合"
                                "其在月光下使用有通靈之能。\n" NOR );
                set("unit", "把");
                set("value", 800000);
                set("no_sell", 1);
                set("no_store", 1);
                set("material", "steel");
                set("wield_msg", (: do_wield() :));
                set("unwield_msg", (: do_unwield() :));
                set("stable", 80);
        }
        init_blade(500);
        setup();
        //restore();
}

string do_wield()
{
        object me;

        me = this_player();
        remove_call_out("check_npc");
        call_out("check_npc", 0, me, environment(me));
        if( query("shen", me)<-100000 )
        {
                addn_temp("apply/attack", me->query_skill("blade",1)/4, me);
                addn_temp("apply/defense", me->query_skill("parry",1)/4, me);
                return HIW "$N沉聲低吼，緩緩拔出$n" HIW "，只感到一輪月光當中照來。\n" NOR;
        } else
        if( query("shen", me) <= 0 )
        {
                addn_temp("apply/attack", me->query_skill("blade",1)/4, me);
                addn_temp("apply/defense", me->query_skill("parry",1)/4, me);
                return HIC "$N伸手把$n" HIW "抽出刀鞘。\n" NOR;
        } else
        if( query("shen", me)>100000 )
        {
                addn_temp("apply/attack", me->query_skill("blade",1)/4, me);
                addn_temp("apply/defense", me->query_skill("parry",1)/4, me);
                return HIB "$N戰戰兢兢的拔出一把$n" HIB "。\n" NOR;
        } else
        {
                addn_temp("apply/attack", me->query_skill("blade",1)/4, me);
                addn_temp("apply/defense", me->query_skill("parry",1)/4, me);
                return HIB "$N吼管內一陣低吼，“唰”的一聲亮出了$n" HIB "。\n" NOR;
        }
}

string do_unwield()
{
        object me;

        me = this_player();
        remove_call_out("check_npc");
        addn_temp("apply/attack",-me->query_skill("blade",1)/4, me);
        addn_temp("apply/defense",-me->query_skill("parry",1)/4, me);
        if( query("shen", me) <= 0 )
                return HIC "$N隨手將圓月彎刀插回刀鞘。\n" NOR;
        else
        if( query("shen", me)>100000 )
                return HIG "$N把$n" HIG "收了起來，感覺心神不寧，全身虛脫。\n" NOR;
        else
                return HIG "$N一曬，把$n" HIG "插回刀鞘。\n" NOR;
}

void check_npc(object me, object env)
{
        object *ob;
        int i;

        if (! objectp(me) || ! living(me))
                return;

        if (environment(me) != env)
                return;

        ob = all_inventory(env);
        for (i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_character() || ob[i] == me ||                    
                    !living(ob[i]) || query("not_living", ob[i]) || 
                    query("id", ob[i]) == "qing qing" )
                        continue;

                if (me->is_good())
                {
                        if (userp(ob[i]))
                                continue;

                        if( query("shen", ob[i])<-100000 )
                        {
                                message_vision("$N大怒喝道：好你個" + RANK_D->query_rude(me) +
                                               "，居然敢盜用圓月彎刀？\n", ob[i]);
                                if( !query("no_fight", env) )
                                        ob[i]->kill_ob(me);
                        } else
                        if (ob[i]->is_good())
                        {
                                message_vision(random(2) ? "$N哈哈大笑，對$n道：幹得漂亮，俠之"
                                                           "大者，也就是兄台這般人物。\n" :
                                                           "$N拼命鼓掌，對$n道：想不到魔教有"
                                                           "象兄台如此厲害之人呀。",
                                               ob[i], me);
                        }
                        continue;
                }

                if (me->is_not_bad())
                        continue;

                if( query("shen", ob[i])<-100000 && !userp(ob[i]) )
                {
                        message_vision(random(2) ? "$N讚道：好刀，好刀！\n" :
                                                   "$N嘆道：也不知魔教教主那老家伙到底死沒有死？\n",
                                       ob[i]);
                } else
                if( query("shen", ob[i])>10 && !userp(ob[i]) )
                {
                        mixed ob_exp, my_exp;
                        ob_exp=query("combat_exp", ob[i]);
                        my_exp=query("combat_exp", me);
                        if (count_gt(ob_exp, count_mul(my_exp * 2)) || count_gt(ob_exp, 1500000))
                        {
                                message_vision(random(2) ? "$N對$n冷冷道：滾開！少在我面前賣弄。\n" :
                                                           "$N一聲冷笑，對$n道：你以為你是誰？魔教教主"
                                                           "那？哈哈哈哈！\n",
                                               ob[i], me);
                        } else
                        if (count_gt(ob_exp, 20000))
                        {
                                message_vision(random(2) ? "$N臉色有些不對勁。\n" :
                                                           "$N露出害怕的神色。\n",
                                               ob[i]);
                                if( query("no_fight", env) )
                                        continue;
                                message_vision(random(2) ? "$N怒喝一聲，“大家都不要活了！”\n" :
                                                           "$N一言不發，忽的撲向$n，身形極快。\n",
                                               ob[i], me);
                                ob[i]->kill_ob(me);
                        } else
                        {
                                message_vision(random(2) ? "$N撲通一聲，癱倒在地，雙手急搖"
                                                           "道：“不是我！真的不是我！”\n" :
                                                           "$N一個哆嗦，結結巴巴的什麼也說"
                                                           "不上來。\n",
                                               ob[i], me);
                                if( !query("no_fight", env) )
                                        ob[i]->unconcious();
                        }
                }
        }
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
//        int my_exp, ob_exp;

        if (me->is_good() || victim->is_bad())
                return - damage_bonus / 2;

        if (me->is_not_bad() || victim->is_not_good())
                return 0;

        if (me->query_skill_mapped("blade") != "moon-blade" ||
            me->query_skill("moon-blade", 1) < 100)
                // only increase damage
                return damage_bonus / 2;

        switch (random(4))
        {
        case 0:
                if (! victim->is_busy())
                        victim->start_busy(me->query_skill("blade") / 10 + 2);
                return HIB "$N跨前一步，手中的" NOR+HIW "圓月彎刀" NOR+HIB "從意想不到的"
                       "角度向$n攻去，$n只見四周有無數刀光閃動。\n"
                       "不知如何抵擋，只有連連後退。\n" NOR;

        case 1:
                n = me->query_skill("blade");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                n=query("eff_jing", victim);
                n /= 2;
                victim->receive_damage("jing", n, me);
                victim->receive_wound("jing", n / 2, me);
                return random(2) ? HIB "$N沉身低吼，手中的圓月彎刀化作萬道紅光，“唰”的掃過$n。\n" NOR:
                                   HIB "$N突然大聲喝道：“什麼名門正派，還不受死？”手中圓月彎刀"
                                   HIB "忽的一抖，$n登時覺得眼前有如千萬刀光不停閃動。\n" NOR;
        }

        // double effect
        return damage_bonus;
}

void start_borrowing()
{
        remove_call_out("return_to_laozu");
        call_out("return_to_laozu", 14400 + random(1800));
}

void return_to_laozu()
{
        object me;

        me = environment();
        if (! objectp(me))
                return;

        while (objectp(environment(me)) && ! playerp(me))
                me = environment(me);
 
        if (playerp(me))
        {
                if (me->is_fight())
                {
                        call_out("return_to_laozu", 1);
                        return;
                }

                message_vision("忽然一個魔教的弟子走了過來，看到$N，忙招呼道：“青青說"
                               "這把刀不能丟了，放在你手上不大放心，讓我來找你拿回圓月彎刀，你現在不用了麼？”\n"
                               "$N道：“好了，好了，你就拿回去吧。”\n"
                               "$N將神刀交給魔教弟子帶走。\n", me);
        } else
        {
                message("vision", "忽然一個魔教弟子走了過來，撿起圓月彎刀，嘆了口氣，搖搖"
                                  "頭走了。\n", me);
        }

        destruct(this_object());
}
