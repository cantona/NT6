#include <weapon.h>
#include <ansi.h>

inherit SWORD;

string do_wield();
string do_unwield();

void create()
{
        set_name(HIY "真武劍" NOR,({ "zhenwu jian", "jian", "sword", "zhenwu" }) );
        set_weight(1500);
        if (clonep())
                destruct(this_object());
        else {
                set("long", @LONG
這是一柄寒光閃閃的寶劍，昔年武當張真人持此劍蕩妖除魔，掃盡羣醜。
江湖宵小，見此劍無不心蕩神搖。
LONG );
                set("unit", "把");
                set("value", 800000);
                set("no_sell", 1);
                set("unique", 1);
                set("material", "steel");
                set("wield_msg", (: do_wield :));
                set("unwield_msg", (: do_unwield :));
                set("stable", 80);
        }
        init_sword(200);
        setup();
}

string do_wield()
{
        object me;

        me = this_player();
        remove_call_out("check_npc");
        call_out("check_npc", 0, me, environment(me));
        if( query("shen", me)>10000 )
        {
                return HIC "$N一聲長嘯，將$n" HIC "盪出劍鞘，霎時天地間浩氣凜然。\n" NOR;
        } else
        if( query("shen", me) >= 0 )
        {
                return HIC "$N一伸手，已然把$n" HIC "亮在手中。\n" NOR;
        } else
        if( query("shen", me)>-10000 )
        {
                return HIG "$N戰戰兢兢的摸出一把$n" HIG "。\n" NOR;
        } else
        {
                return HIG "$N一聲冷笑，“唰”的一聲亮出了$n" HIG "。\n" NOR;
        }
}

string do_unwield()
{
        object me;

        me = this_player();
        remove_call_out("check_npc");
        if( query("shen", me) >= 0 )
                return HIC "$N一揮手，還劍入鞘。\n" NOR;
        else
        if( query("shen", me)>-10000 )
                return HIG "$N把$n" HIG "插回劍鞘，抹了抹頭上的汗。\n" NOR;
        else
                return HIG "$N一曬，把$n" HIG "插回劍鞘。\n" NOR;
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
                    query("id", ob[i]) == "zhang sanfeng" )
                        continue;

                if (me->is_bad())
                {
                        if (userp(ob[i]))
                                continue;

                        if( query("shen", ob[i])>10000 )
                        {
                                message_vision("$N大怒喝道：好你個" + RANK_D->query_rude(me) +
                                               "，居然敢盜用真武劍？\n", ob[i]);
                                if( !query("on_fight", env) )
                                        ob[i]->kill_ob(me);
                        } else
                        if (ob[i]->is_bad())
                        {
                                message_vision(random(2) ? "$N哈哈大笑，對$n道：幹得好，幹得好。\n" :
                                                           "$N拼命鼓掌，對$n道：兄弟加油幹啊！",
                                               ob[i], me);
                        }
                        continue;
                }

                if (me->is_not_good())
                        continue;

                if( query("shen", ob[i])>10000 && !userp(ob[i]) )
                {
                        message_vision(random(2) ? "$N讚道：好劍，好劍！\n" :
                                                   "$N歎道：見此劍真是如見張真人啊！\n",
                                       ob[i]);
                } else
                if( query("shen", ob[i])<-10 && !userp(ob[i]) )
                {
                        mixed ob_exp, my_exp;
                        ob_exp=query("combat_exp", ob[i]);
                        my_exp=query("combat_exp", me);
                        if (ob_exp > my_exp * 2 || ob_exp > 1500000)
                        {
                                message_vision(random(2) ? "$N對$n冷冷道：滾開！少在我面前賣弄。\n" :
                                                           "$N一聲冷笑，對$n道：你以為你是誰？張三丰？哈哈哈哈！\n",
                                               ob[i], me);
                        } else
                        if (ob_exp > 20000)
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
                                message_vision(random(2) ? "$N撲通一聲，癱倒在地，雙手急搖道：“不是我！真的不是我！”\n" :
                                                           "$N一個哆嗦，結結巴巴的什麼也説不上來。\n",
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
        int my_exp, ob_exp;

        if (me->is_bad() || victim->is_good())
                return - damage_bonus / 2;

        if (me->is_not_good() || victim->is_not_bad())
                return 0;

        if (me->query_skill_mapped("sword") != "taiji-jian" ||
            me->query_skill("taiji-jian", 1) < 100)
                // only increase damage
                return damage_bonus / 2;

        switch (random(4))
        {
        case 0:
                if (! victim->is_busy())
                        victim->start_busy(me->query_skill("sword") / 10 + 2);
                return HIC "$N跨前一步，手中的" NOR+HIY "真武劍" NOR+HIC "幻化成無數圓圈，"
                       "向$n逼去，劍法細密之極。$n大吃一\n"
                       "驚，不知如何抵擋，只有連連後退。\n" NOR;

        case 1:
                n = me->query_skill("sowrd");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                n=query("eff_jing", victim);
                n /= 2;
                victim->receive_damage("jing", n, me);
                victim->receive_wound("jing", n / 2, me);
                return random(2) ? HIY "$N一聲長吟，手中的真武劍化作一到長虹，“唰”的掃過$n。\n" NOR:
                                   HIY "$N突然大聲喝道：“邪魔外道，還不受死？”手中真武劍"
                                   HIY "忽的一抖，$n登時覺得眼前一花。\n" NOR;
        }

        // double effect
        return damage_bonus;
}

void start_borrowing()
{
        remove_call_out("return_to_zhang");
        call_out("return_to_zhang", 7200 + random(600));
}

void return_to_zhang()
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
                        call_out("return_to_zhang", 1);
                        return;
                }

                message_vision("忽然一個武當弟子走了過來，看到$N，忙招呼道：“張真人讓我來找你拿回"
                               "真武劍，你現在不用了麼？”\n"
                               "$N道：“好了，好了，你就拿回去吧。”\n"
                               "$N將劍交給武當弟子帶走。\n", me);
        } else
        {
                message("visoin", "忽然一個武當弟子走了過來，撿起真武劍，歎了口氣，搖搖頭走了。\n",
                        me);
        }

        destruct(this_object());
}
