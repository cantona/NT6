// duanyu.c 段譽

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("段譽", ({"duan yu", "duan", "yu"}));
        set("gender", "男性");
        set("title", "大理國王子");
        set("age", 22);
        set("long", "他是一個身穿青衫的年輕男子。臉孔略尖，有一股書生的呆氣。\n");
        set("attitude", "peaceful");
        set("class", "royal");
        
        set("str", 21);
        set("int", 36);
        set("con", 32);
        set("dex", 29);

        set("chat_chance", 1);
        set("chat_msg", ({
                CYN "段譽嘆了口氣道：唉，老爸這是怎麼回事？\n" NOR,
        }));

        set("inquiry", ([
                "大理" : "大理是個好地方，山清水秀，風景宜人。\n",
                "王語嫣" : "唉，她心裡只有她表哥，從來就沒把我放在眼裡。\n",
                "拜師" : "嗯……我的師傅是老子、孔子和莊子，他們的學問我還沒學全呢。\n",
        ]));

        set("qi", 5000);
        set("max_qi", 5000);
        set("jing", 2500);
        set("max_jing", 2500);
        set("neili", 9000);
        set("max_neili", 9000);
        set("jiali", 150);

        set("combat_exp", 1500000);

        set_temp("apply/damage", 50);
        set_temp("apply/defense", 50);

        set_skill("force", 280);
        set_skill("beiming-shengong", 280);
        set_skill("finger", 280);
        set_skill("six-finger", 280);
        set_skill("dodge", 280);
        set_skill("lingbo-weibu", 280);
        set_skill("parry", 200);
        set_skill("chess", 200);
        set_skill("buddhism", 280);
        set_skill("literate", 280);
        set_skill("lamaism", 280);
        set_skill("jingluo-xue", 240);
        set_skill("martial-cognize", 200);

        map_skill("force", "beiming-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("parry", "six-finger");
        map_skill("finger", "six-finger");

        prepare_skill("finger", "six-finger");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "finger.six" :),
                (: perform_action, "finger.zhongheng" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/unarmed_damage", 150);

        setup();

        carry_object("/clone/misc/cloth")->wear();
}

void help_girl(object me)
{
        object wang;
        string msg;

        if (! living(this_object()))
                return;

        command("say 語嫣妹子，不要慌張，有我段譽在此！");

        switch(query("gender", me) )
        {
        case "男性":
                msg = "這位" + RANK_D->query_respect(me) +
                      "，你怎能如此狠心？這麼動人的妹子你也下得了手？";
                break;
        case "女性":
                msg = "這位" + RANK_D->query_respect(me) +
                      "，你莫非妒忌人家美貌，所以下此毒手？";
                break;
        default:
                msg = "這位" + RANK_D->query_respect(me) +
                      "，我說你已然半男不女，怎麼還打女孩子的主意？";
                break;
        }        
        command("say " + msg);

        if (wang = present("wang yuyan"))
        {
                if (living(wang))
                        message_vision(HIW "\n$N" HIW "連忙扶住$n" HIW "，背在身"
                                       "後。\n$n" HIW "道：段郎，我看他武功來歷，"
                                       "幫你指點他的破綻。\n" NOR, this_object(), wang);
                else
                        message_vision(HIW "\n$N" HIW "一把摟住$n" HIW "，抱在懷"
                                       "中。\n" NOR, this_object(), wang);

                me->remove_enemy(wang);
                wang->move(this_object());
                remove_call_out("check_enemys");
                call_out("check_enemys", 1, wang);
        }

        kill_ob(me);
}


int accept_fight(object me)
{
        command("say 哎呀呀，有話好好說，不要就動手嘛。");
        return 0;
}

int accept_hit(object me)
{
        command("say 你這人怎麼回事？怎麼突然就動手打人呢？。");
        return 1;
}

int accept_kill(object me)
{
        command("say 反了反了，這年頭還有王法沒有？");
        return 1;
}

void unconcious()
{
        object wang;

        command("say 語嫣妹子……");

        if (wang = present("wang yuyan", this_object()))
        {
                wang->move(environment());
                message_vision(HIW "\n$N" HIW "從$n" HIW "身上跌了下來，大驚"
                               "失色，道：段郎，段郎！你怎麼了啦？\n" NOR, wang,
                               this_object());
        }

        ::unconcious();
}

void die()
{
        object wang;

        if (wang = present("wang yuyan", this_object()))
        {
                wang->move(environment());
                message_vision(HIW "$N" HIW "從$n" HIW "身上跌了下來，大驚失"
                               "色，道：段郎，段郎！你怎麼死了啊？\n" NOR, wang,
                               this_object());
        }

        ::die();
}

void check_enemys(object wang)
{
        if (! objectp(this_object()) || ! objectp(wang))
                return;

        if (! living(this_object()))
                return;

        if (is_fighting() && random(5) == 0 && living(wang))
        {
                message_vision(HIW "\n王語嫣在$N" HIW "耳邊嘀嘀咕咕的說些話。\n"
                               NOR, this_object());
                addn_temp("apply/damage", 10);
                addn_temp("apply/defense", 10);
                receive_curing("qi", 300);
                receive_curing("jing", 150);
                receive_heal("qi", 300);
                receive_heal("jing", 150);
        }

        if (! is_fighting())
        {
                set_temp("apply/damage", 50);
                set_temp("apply/defense", 50);
                if (! living(wang))
                {
                        command("say 這下好了，我的語嫣妹子不會受驚了。");
                        return;
                }
                message_vision(HIW "$n" HIW "對$N" HIW "道：好了，敵人退了，我"
                               "下來吧。\n$N" HIW "這才戀戀不舍的把$n" HIW "放"
                               "了下來。\n" NOR, this_object(), wang);
                wang->move(environment(this_object()));
                return;
        }

        remove_call_out("check_enemys");
        call_out("check_enemys", 1, wang);
}
