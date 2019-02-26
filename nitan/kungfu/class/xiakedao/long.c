// long.c

#include <ansi.h>
inherit NPC;

int ask_zhou();
int ask_back();

void create()
{
        set_name("龍島主", ({ "long daozhu", "long" }));
        set("title", HIR "俠客島島主" NOR);
        set("gender", "男性");
        set("age", 60);
        set("long",
              "這是個看起來五十來歲的漢子，面眉全面，臉色紅潤，着一襲黃袍，昂然挺立。\n"
        );

        set_temp("apply/attack", 600);
        set_temp("apply/armor", 1500);
        set_temp("apply/damage", 800);
        set_temp("apply/unarmed_damage", 800);
        set_temp("apply/dodge", 600);
        set_temp("apply/parry", 600);

        set("qi", 9000);
        set("max_qi", 9000);
        set("jing", 20000);
        set("max_jing", 20000);
        set("neili", 15000);
        set("max_neili", 15000);
        set("jiali", 250);
        set("combat_exp", 5000000);
        set("score", 20000000);

        set_skill("force", 300);
        set_skill("taixuan-gong", 300);
        set_skill("dodge", 300);
        set_skill("taixuan-gong", 300);
        set_skill("unarmed", 300);
        set_skill("taixuan-gong", 300);
        set_skill("parry", 300);

        map_skill("force", "taixuan-gong");
        map_skill("dodge", "taixuan-gong");
        map_skill("unarmed", "taixuan-gong");
        map_skill("parry", "taixuan-gong");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: perform_action, "unarmed.taixuan" :),
        }) );

        set("chat_chance", 5);
        set("inquiry", ([
                "臘八粥" : (: ask_zhou :),
                "俠客島" : "這個島是我和木兄弟無意中發現的。",
                "back"   : (: ask_back :),
                "離島"   : (: ask_back :),
        ]));

        create_family("俠客島", 0, "島主");
        setup();

        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && ! is_fighting() && random(3) == 1)
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (! objectp(ob) || environment(ob) != environment())
                return;

        if( query("combat_exp", ob)<10000 )
              say("龍島主抬頭望了你一眼，説道：”經驗尚淺。”\n");
        else
        if( query("combat_exp", ob)<100000 )
              say("龍島主瞟了你一眼，説道：“未到火候。”\n");

        return;
}

int ask_zhou()
{
        message_sort("$N對$n説：“這是本島特有的東西，它主要"
                     "由一味“斷腸獨骨腐心草”構成，要開花後"
                     "效力方著，但這種草每十年才開一次花，所"
                     "以一般人很難得到的，小兄弟想要就要看你"
                     "的緣分了！”\n", this_object(), this_player());
        return 1;
}

int ask_back()
{
        object me;

        me = this_player();
        if( query("combat_exp", me) >= 500000 )
        {
         message_vision("$N冷冷的看了一會兒$n，才道：“你沒長腿？經驗都過50萬，還要我幫你？”\n",
                               this_object(), me);
                return 1;
        }

        message_vision("$N歎了口氣，道：“既然這樣！還是讓李四送你出島吧！”\n",
                       this_object());
        me->move("/d/xiakedao/haitan");
        message("vision", "李四陪着" + me->name() + "走了過來，説了幾句話，陰着臉離去了。\n",
                environment(me), me);
        tell_object(me, HIR "李四送你到海灘，冷冷道：“你這廢物！"
                        "好好練好功夫，別總麻煩我們家島主。”\n" NOR
                        "你連忙陪了幾個笑臉，李四才怏怏離去。\n");
        return 1;
}

int accept_object(object who, object ob)
{
        object zhou;

        // 沒有中過故事
        if( !query("story/labazhou", who) )
                return 0;

        // 不是銅牌
        if( (query("id", ob) != "e pai") && (query("id", ob) != "shan pai") )
                return 0;

        // 給粥
        zhou = new("/d/xiakedao/obj/labazhou");
        if (zhou)
                zhou->move(who, 1);

        message_vision("$N對$n道：“這臘八粥服後於我輩練武之士大有補益，閣下趁熱喝吧！”\n",
                       this_object(), who);
        destruct(ob);
        return 1;
}

/*
int accept_object(object who, object ob)
{
        object obn;

        if( query("id", ob) != "shanebu" && query("id", ob) != "fuxincao" )
        {
                message_vision("\n龍島主搖頭道：這不是我想要的呀！\n",who);
                return 0;
        }
        if( query("id", ob) == "shanebu" )
        {
                if( random(query("kar", who)) <= 25 )
                {
                        message_vision("龍島主搖頭道：我看小兄弟今生於此無緣。\n",who);
                        return 1;
                }
                else
                {
                        remove_call_out("destroy");
                        call_out("destroy", 1, who, ob);

                        if(query_temp("cao"))
                        {
                                message_vision("\n龍島主見是賞善罰惡簿，大喜道：恭喜這位小兄弟了!\n",who);
                                obn=new("/clone/medicine/nostrum/labazhou");
                                obn->move(who);
                                delete_temp("bu");
                                delete_temp("cao");
                                return 1;
                        }
                        else if(query_temp("bu"))
                        {
                                message_vision("\n龍島主見是賞善罰惡簿，對$N搖頭道：賞善罰惡簿我有了。\n",who);
                                return 0;
                        }
                        else
                        {
                                message("vision","龍島主看見賞善罰惡簿，大喜道：現在只差腐心草了。\n",environment(who));
                                set_temp("bu",1);
                                return 1;
                        }
                }
        }
        if( query("id", ob) == "fuxincao" )
        {
                if( random(query("kar", who)) <= 25 )
                {
                        message_vision("龍島主搖頭道：我看小兄弟今生於此無緣。\n",who);
                        return 1;
                }
                else
                {
                        remove_call_out("destroy");
                        call_out("destroy", 1, who, ob);

                        if(query_temp("bu"))
                        {
                                message_vision("\n龍島主見是腐心草，大喜道：恭喜這位小兄弟了!\n",who);
                                obn=new("/clone/medicine/nostrum/labazhou");
                                obn->move(who);
                                delete_temp("cao");
                                delete_temp("bu");
                                return 1;
                        }
                        else if(query_temp("cao"))
                        {
                                message_vision("\n龍島主見是腐心草，對$N搖頭道：腐心草我已經有了。\n",who);
                                return 0;
                        }
                        else
                        {
                                message("vision","龍島主看見腐心草，大喜道：現在只差賞善罰惡簿了。\n",environment(who));
                                set_temp("cao",1);
                                return 1;
                        }
                }
        }
        return 1;
}
*/

