//tonbaixiong.c
inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;

void greeting(object);
void init();
void create()
{
        set_name("童百熊", ({ "tongbai xiong","xiong"}) );
        set("gender", "男性" );
        set("age", 75);
        set("title", "日月神教風雷堂長老");
        set("long", "他白髮披散, 銀髯戟張, 臉上的肌肉牽動, \n"
                    "圓睜雙眼, 身上的鮮血已然凝結, 神情甚是可怖。\n");
        set("attitude", "friendly");
        set("shen_type", -1);

        set("per", 21);
        set("str", 23);
        set("int", 23);
        set("con", 22);
        set("dex", 20);

        set("max_qi", 1000);
        set("max_jing",1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 200);
        set("combat_exp", 350000);
        set("score", 30000);

        set_skill("force", 100);
        set_skill("dodge", 90);
        set_skill("unarmed", 100);
        set_skill("parry", 80);
        set_skill("hammer",100);
        set_skill("blade",100);
        set_skill("taiji-shengong",70);
        set_skill("tiyunzong", 80);
        set_skill("taiji-dao", 100);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");

        map_skill("parry", "taiji-dao");
        map_skill("blade", "taiji-dao");
        create_family("日月神教",2,"弟子 風雷堂長老");

        set("chat_chance", 3);
        set("chat_msg", ({
                 "童百熊怒瞪雙眼道: “我沒錯, 我沒有叛教! 東方兄弟你不能冤枉我呀! ”\n",
                 "童百熊歎了一口氣説：“我和東方兄弟出生入死, 共歷患難的時候, 你們還沒生下來哪!”\n"
        }) );
        setup();
        carry_object("/d/heimuya/npc/obj/zijinchui")->wield();
        carry_object("/d/heimuya/npc/obj/cloth")->wear();
        carry_object("/d/heimuya/npc/obj/card1")->wear();

}



void attempt_apprentice(object ob)
{
     command("say 我是患難之身, 怎麼能收徒呢。壯士還是請回吧!\n");
}
