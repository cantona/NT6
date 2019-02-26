// teller.c

inherit KNOWER;

int do_forge();

void create()
{
        set_name("李鐵嘴", ({ "fortune teller", "teller" }) );
        set("gender", "男性" );
        set("age", 48);
        set("long", "李鐵嘴是個買卜算卦的江湖術士，兼代客寫書信、條幅。\n");
        set("str", 25);
        set("dex", 20);
        set("con", 17);
        set("int", 15);
        set("shen_type", -1);

        set_skill("unarmed", 30);
        set_skill("dodge", 25);
        set_temp("apply/attack", 25);
        set_temp("apply/defense", 25);
        set("combat_exp", 2500);

        set("attitude", "peaceful");
        set("inquiry", ([
                "寫信" : "李鐵嘴説道：代客寫信，每頁五十文。\n",
                "寫條幅" : "李鐵嘴説道：可以用各家字跡寫條幅，每幅五兩白銀。\n",
                "偽造" : (: do_forge :),
        ]) );

        setup();
        add_money("silver", 5);
}

int do_forge()
{
        say("李鐵嘴兩隻眼睛四下掃了掃，「嘿嘿嘿」的乾笑了幾聲...\n");
        write("李鐵嘴輕聲跟你説道：不是我吹牛，保證驀的跟原來"
              "字體一模一樣，每封信\n"
              "                           五十兩白銀，不二價。\n");
        set_temp("marks/李", 1, this_player());
        return 1;
}

int accept_object(object who, object ob)
{
        object letter;

        letter = new(__DIR__"obj/letter");

        if( query("id", ob) == "letterpaper" )
        {
                if( query_temp("marks/李", who) )
                {
                        set_temp("marks/李3", 1, this_player());
                        write("李鐵嘴對你説道：造封信容易，先拿五十兩銀子來。\n");
                        set_temp("marks/李", 0, this_player());
                        call_out("destroy", 1, ob);
                        return 1;
                }else if( query_temp("marks/李2", who) )
                {
                        write("李鐵嘴皮笑肉不笑的對你説道：偽造這"
                              "封信可是關係重大啊，得多收五十兩。\n");
                        set_temp("marks/李4", 1, this_player());
                        set_temp("marks/李2", 0, this_player());
                        call_out("destroy", 1, ob);
                        return 1;
                }
                return 0;
        }
       
        if (ob->value() >= 5000)
        {
                if( query_temp("marks/李4", who) )
                {
                        write("李鐵嘴對你説道：這封信是造好了，但" +
                              RANK_D->query_respect(who) + 
                              "要是出了事，千萬別把我説出來呀。\n");
                        say("李鐵嘴給了"+query("name", who)+"一封手信。\n");
                        set_temp("marks/李4", 0, this_player());
                        letter->move(who);
                        return 1;
                }

                if( query_temp("marks/李3", who) )
                {
                        write("李鐵嘴皮笑肉不笑的對你説道：偽造這封信"
                              "可是關係重大啊，得多收五十兩。\n");
                        set_temp("marks/李4", 1, this_player());
                        set_temp("marks/李3", 0, this_player());
                        return 1;
                }

                if( query_temp("marks/李", who) )
                {
                        write("李鐵嘴對你説道：你想偽造什麼啊? 總"
                              "得拿個樣子來吧。\n");
                        set_temp("marks/李2", 1, this_player());
                        set_temp("marks/李", 0, this_player());
                        return 1;
                }
                say("李鐵嘴一面急忙把錢收起來，一面笑嘻嘻説道：" +
                    RANK_D->query_respect(ob) + "，這怎麼敢當。\n");
                return 1;
        }

        if (ob->value() >= 500)
        {
                say("李鐵嘴笑嘻嘻説道：條幅寫好了，請"
                    "您收起來吧，多謝關照。\n");
                return 1;
        }

        if (ob->value() >= 50)
        {
                say("李鐵嘴笑嘻嘻説道：信寫完了，您收好了，多謝關照。\n");
                return 1;
        }
        return 0;
}

void destroy (object ob)
{
        destruct(ob);
        return;
}
