//yuanwai.c

inherit NPC;

void create()
{
        set_name("蕭員外", ({"xiao yuanwai", "xiao","yuanwai" }));
        set("gender", "男性");
        set("rank_info/respect", "老員外");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 40);
        set("int", 40);
        set("max_kee", 800);
        set("max_gin", 800);
        set("max_sen", 800);
        set("force", 900);
        set("max_force", 900);
        set("force_factor", 60);
        set("max_mana", 900);
        set("mana", 900);
        set("mana_factor", 40);
        set("combat_exp", 300000);
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        set_skill("force", 50);
          
        setup();
        carry_object("/d/changan/npc/obj/choupao")->wear();
}
void check_daughter(object me);

void init()
{
        ::init();
        check_daughter(this_object());
}

int accept_object (object who, object ob)
{
        object me = this_object();
        object room = environment(me);
        if( query("short", room) != "蕭家大廳" )
                return 0;

        if( query("id", ob) == "xin" )
        {
                remove_call_out("read_letter");
                call_out("read_letter",3,me,who,ob);
                return 1;
        }
        return 0;
}

void read_letter(object me, object who, object ob)
{
        destruct (ob);
        reset_eval_cost();

        message_vision("$N看完信，不由得涕淚俱下。\n"
                       "$N道：這些天我差人尋遍長安城，也沒找"
                       "到我那孩兒，\n原來竟被人拐賣到了青樓之中。\n\n",
                       me);

        message_vision("$N對$n道：若非這位" +
                       RANK_D->query_respect(who)+
                       "前來相告，我可能今生就見不到我的女兒了，\n" +
                       RANK_D->query_respect(who) +
                       "這份恩德叫老夫如何報答啊！\n", me, who);

        remove_call_out("send_to_fight");
        call_out("send_to_fight",3,me,who);
}

void send_to_fight (object me, object who)
{
        object yupei = new("/d/changan/npc/obj/yupei");
        yupei->move(who);
        message_vision("$N對$n說道：還請這位" +
                       RANK_D->query_respect(who) +
                       "再幫幫忙，將我女兒搭救出來！\n\n",
                       me, who);

        message_vision("$N從衣袋內取出一塊玉佩交給$n，道"
                       "“這是我家傳玉佩，湘湘見到會認得的！\n",
                       me, who);
        message_vision("$N給$n一塊玉佩。\n", me, who);
        who->save();
}

void check_daughter(object me)
{
          object room = environment(me);
          object xiangxiang = present("xiangxiang", room);
          object who;
          object yupei;
          reset_eval_cost();
          if( query("short", room) != "蕭家大廳" )
                    return;

          if( !xiangxiang || !query("leader", xiangxiang) )
                    return;
          if( !(who=present(query("leader", xiangxiang),room)) )
                    return;
          if (! (yupei = present("yu pei", who)))
                    return;
          xiangxiang->set_leader(0);
          set_temp("no_return ", 0, xiangxiang);
          remove_call_out ("cry_daughter");
          call_out("cry_daughter",2,me,xiangxiang,who);
          remove_call_out ("announce_success");
          call_out("announce_success",4,me,who);
}

void cry_daughter(object me, object xiangxiang, object who, object yupei)
{
        object book;
        message_vision("$N見了$n一愣，然後老淚縱橫地將$n拉過去。\n",
                       me, xiangxiang); 
        destruct(xiangxiang);
      
        yupei = present("yu pei",who);
        yupei->move(me);
        destruct(yupei);
        command("thank "+query("id", who));
        command("say 這位" + RANK_D->query_respect(who) +
                "救我兒湘湘逃出魔掌！老夫這裡有一本書，\n是"
                "祖上傳下來的，就送給" + RANK_D->query_respect(who) +
                "吧！\n");
        carry_object("/d/changan/npc/obj/book");
        command("give book to "+query("id", who));
}
