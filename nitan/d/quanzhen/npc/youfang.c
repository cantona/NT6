// youfangdaoren.c

inherit NPC;

void create()
{
        set_name("遊方道人", ({"youfang daoren","daoren"}));
        set("long", "他是一位未通世故的青年道人，臉上掛着孩兒般的微笑。\n");

        set("gender", "男性");
        set("attitude", "heroism");
        set("class", "quanzhen");

        set("age", 20);
        set("shen_type", 1);
        set("no_get", 1);
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
                "遊方道人説道: 請這位施主化幾兩銀子給貧道，隨喜隨喜，造福眾生。\n",
                (: random_move :)
        }) );

        set_skill("force", 41);
        set_skill("strike", 41);
        set_skill("dodge", 41);
        set_skill("parry", 41);
        set_skill("jinyan-gong", 42);
        set_skill("haotian-zhang", 41);
        set_skill("xiantian-gong", 41);

        map_skill("force", "xiantian-gong");
        map_skill("dodge", "jinyan-gong");
        map_skill("strike", "haotian-zhang");
        map_skill("parry", "haotian-zhang");
        create_family("全真教", 4, "弟子");
        setup();
        carry_object(CLOTH_DIR"daopao")->wear();

        setup();

}

int accept_object(object me, object ob)
{
        object ling;
        
        command("smile");
        command("say 無量壽佛，多謝這位" + RANK_D->query_respect(me) + " ！");

        if( query("money_id", ob) && ob->value() >= 10000 && query("class", me) != "bonze" )
        {
                command("say " + RANK_D->query_respect(me) + 
                "如此樂善好施，兼又身懷絕藝，全真祖師正欲一晤天下豪傑，不知可願赴重陽宮內一遊？");

                ling=new("/d/quanzhen/npc/obj/tie-ling");
                ling->move(me);
                message_vision("遊方道人給$N一塊鐵鑄令牌。\n", me);

                command("say 此牌限時一日，逾時失效，請於限時前離宮，否則多有不便，切記切記！"); 
                return 1;
        }

        return 1;
}
