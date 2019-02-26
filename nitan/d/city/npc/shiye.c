// shiye.c 知府師爺

inherit NPC;

string ask_me();

void create()
{
        set_name("譚友紀", ({ "tan youji", "tan" }));
        set("title", "知府師爺");
        set("gender", "男性");
        set("age", 57);

        set("combat_exp", 30000);
        set_skill("unarmed", 50);
        set_skill("dodge", 60);
        set_temp("apply/attack",  20);
        set_temp("apply/defense", 20);
        set_temp("apply/damage",  20);
        set("shen_type", 0);

        set("inquiry", ([
                "叫化雞" : (: ask_me :)
        ]) );

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

string ask_me()
{
        if( query_temp("marks/雞", this_player()) )
        {
                say("好小子，你怎麼知道我喜歡吃叫化雞？\n");
                command("lick");
                say("既然你我成了食友，我就告訴你吧。付耳過來！\n");
                command("whisper"+query("id", this_player())+"你去北京找全聚德的老闆，只要告訴他是我叫你去的，他就會...");
                delete_temp("marks/雞", this_player());
                set_temp("marks/雞2", 1, this_player());
                return "今天嗯....啊....那個天氣很好....\n";
        }
        else if( query_temp("marks/雞2", this_player()) )
                return "我是個浙江人，也沒有你那麼羅嗦！\n";
        else
        {
              set_temp("marks/雞", 1, this_player());
                return "泥縮絲米偶釘布懂\n";
        }
}