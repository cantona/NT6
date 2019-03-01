// lingshe.c 靈蛇杖
// by jeeny

#include <weapon.h>
#include <ansi.h>

inherit STAFF;

string do_wield();
string do_unwield();

void create()
{
        set_name(HIW "靈蛇杖" NOR, ({ "lingshe zhang", "staff", "lingshe" }));
        set_weight(1500);
        if (clonep())
                destruct(this_object());
        else {
                set("long", @LONG
這是一柄令人毛骨悚然的寶杖，昔年西毒歐陽峰曾憑借此杖和洪七公大戰
三百回合。杖頭雕著個咧嘴而笑的人頭，面目猙獰，口中兩排利齒，上喂
劇毒，舞動時宛如個見人即噬的厲鬼。更厲害的是纏杖盤旋的兩條毒蛇，
吞吐伸縮，令人難防。
LONG );
                set("unit", "把");
                set("value", 800000);
                set("no_sell", 1);
                set("du", 3) ;
                set("material", "steel");
                set("wield_msg", (: do_wield :));
                set("unwield_msg", (: do_unwield :));
                set("stable", 80);
        }
        init_staff(200);
        setup();
}

string do_wield()
{
        object me;

        me = this_player();
        remove_call_out("check_npc");
        call_out("check_npc", 0, me, environment(me));
        if( query("shen", me)<-10000 )
                return HIW "$N一聲長嘯，取出$n" HIW "，一時間，陰風襲襲。\n" NOR;
        else
        if( query("shen", me) <= 0 )
                return HIC "$N一伸手，已然把$n" HIW "握在手中。\n" NOR;
        else
        if( query("shen", me)>10000 )
                return HIB "$N哆哆嗦嗦的摸出一把$n" HIB "。\n" NOR;
        else
                return HIB "$N一聲冷笑，“唰”的一聲亮出了$n" HIB "。\n" NOR;
}

string do_unwield()
{
        object me;

        me = this_player();
        remove_call_out("check_npc");
        if( query("shen", me) <= 0 )
                return HIC "$N一揮手，收起了靈蛇杖。\n" NOR;
        else
        if( query("shen", me)>10000 )
                return HIG "$N把$n" HIG "收了起來，心還“砰砰砰”跳個不停。\n" NOR;
        else
                return HIG "$N一曬，把$n" HIG "插回腰間。\n" NOR;
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
                    query("id", ob[i]) == "ouyang feng" )
                        continue;

                if (me->is_good())
                {
                        if (userp(ob[i]))
                                continue;

                        if( query("shen", ob[i])<-10000 )
                        {
                                message_vision("$N大怒喝道：好你個" + RANK_D->query_rude(me) +
                                               "，居然敢盜用靈蛇杖？\n", ob[i]);
                                if( !query("on_fight", env) )
                                        ob[i]->kill_ob(me);
                        } else
                        if (ob[i]->is_good())
                        {
                                message_vision(random(2) ? "$N哈哈大笑，對$n道：幹得漂亮，俠之"
                                                           "大者，也就是兄台這般人物。\n" :
                                                           "$N拼命鼓掌，對$n道：兄弟又為武林立"
                                                           "一大功啊",
                                               ob[i], me);
                        }
                        continue;
                }

                if (me->is_not_bad())
                        continue;

                if( query("shen", ob[i])<-10000 && !userp(ob[i]) )
                {
                        message_vision(random(2) ? "$N讚道：好杖，好杖！\n" :
                                                   "$N嘆道：也不知歐陽兄近來可好？\n",
                                       ob[i]);
                } else
                if( query("shen", ob[i])>10 && !userp(ob[i]) )
                {
                        int ob_exp, my_exp;
                        ob_exp=query("combat_exp", ob[i]);
                        my_exp=query("combat_exp", me);
                        if (ob_exp > my_exp * 2 || ob_exp > 1500000)
                        {
                                message_vision(random(2) ? "$N對$n冷冷道：滾開！少在我面前賣弄。\n" :
                                                           "$N一聲冷笑，對$n道：你以為你是誰？歐"
                                                           "陽峰？哈哈哈哈！\n",
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
        int my_exp, ob_exp;

        if (me->is_good() || victim->is_bad())
                return - damage_bonus / 2;

        if (me->is_not_bad() || victim->is_not_good())
                return 0;

        if (me->query_skill_mapped("staff") != "lingshe-zhangfa" ||
            me->query_skill("lingshe-zhangfa", 1) < 100)
                // only increase damage
                return damage_bonus / 2;

        switch (random(4))
        {
        case 0:
                if (! victim->is_busy())
                        victim->start_busy(me->query_skill("staff") / 10 + 2);
                return HIB "$N跨前一步，手中的" NOR+HIW "靈蛇杖" NOR+HIB "從意想不到的"
                       "角度向$n攻去，杖法有如狂風暴雨般猛烈。$n大吃一\n"
                       "驚，不知如何抵擋，只有連連後退。\n" NOR;

        case 1:
                n = me->query_skill("staff");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                n=query("eff_jing", victim);
                n /= 2;
                victim->receive_damage("jing", n, me);
                victim->receive_wound("jing", n / 2, me);
                return random(2) ? HIB "$N一聲長吟，手中的靈蛇杖化作一道白光，“唰”的掃過$n。\n" NOR:
                                   HIB "$N突然大聲喝道：“什麼名門正派，還不受死？”手中靈蛇杖"
                                   HIB "忽的一抖，$n登時覺得眼前有如萬千條毒蛇竄動。\n" NOR;
        }

        // double effect
        return damage_bonus;
}

void start_borrowing()
{
        remove_call_out("return_to_feng");
        call_out("return_to_feng", 7200 + random(600));
}

void return_to_feng()
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
                        call_out("return_to_feng", 1);
                        return;
                }

                message_vision("忽然一個歐陽世家的弟子走了過來，看到$N，忙招呼道：“祖師爺讓"
                               "我來找你拿回靈蛇杖，你現在不用了麼？”\n"
                               "$N道：“好了，好了，你就拿回去吧。”\n"
                               "$N將杖交給歐陽世家弟子帶走。\n", me);
        } else
        {
                message("vision", "忽然一個歐陽世家弟子走了過來，撿起靈蛇杖，嘆了口氣，搖搖"
                                  "頭走了。\n", me);
        }

        destruct(this_object());
}

