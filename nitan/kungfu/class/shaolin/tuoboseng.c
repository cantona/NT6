// tuoboseng.c
// Date: YZC 96/01/19

inherit NPC;

void create()
{
        set_name("托缽僧", ({"tuobo seng","seng"}));
        set("title", "少林弟子");
        set("long",
                "他是一位未通世故的青年和尚，臉上掛着孩兒般的微笑。\n"
        );

        set("gender", "男性");
        set("attitude", "heroism");
        set("class", "bonze");

        set("age", 20);
        set("shen_type", 1);
        set("str", 15);
        set("int", 30);
        set("con", 30);
        set("dex", 18);
        set("max_qi", 280);
        set("max_jing", 300);
        set("neili", 380);
        set("max_neili", 380);
        set("jiali", 27);
        set("combat_exp", 10000);
        set("shen_type", 1);
        set("chat_chance", 30);

        set("chat_msg", ({
                "托缽僧説道: 請這位施主化幾兩銀子給貧僧，積點陰德，造福眾生。\n",
                (: random_move :)
        }) );

        set_skill("force", 41);
        set_skill("unarmed", 41);
        set_skill("dodge", 41);
        set_skill("parry", 41);
        set_skill("shaolin-shenfa", 42);
        set_skill("jingang-quan", 41);
        set_skill("shaolin-xinfa", 41);

        map_skill("force", "shaolin-xinfa");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("unarmed", "jingang-quan");
        map_skill("parry", "jingang-quan");

        setup();
        carry_object("/d/city/obj/cloth")->wear();

        setup();

}

int accept_object(object me, object ob)
{
        object ling;
        
        command("smile");
        command("say 阿弭陀佛，多謝這位" + RANK_D->query_respect(me) + " ！");

        if( query("money_id", ob) && ob->value() >= 10000 && query("class", me) != "bonze" )
        {
                command("say " + RANK_D->query_respect(me) + 
                "如此樂善好施，兼又身懷絕藝，本寺方丈正欲一晤天下英雄，不知可願赴少林寺內一遊？");

                ling=new("/d/shaolin/obj/tie-ling");
                ling->move(me);
                message_vision("托缽僧給$N一塊鐵鑄令牌。\n", me);

                command("say 此牌限時一日，逾時失效，請於限時前離寺，否則多有不便，切記切記！"); 
                return 1;
        }

        return 1;
}
