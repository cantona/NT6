//NPC /npc/shizhe3.c

inherit NPC;

void greeting(object);
void init();

void create()
{
        set_name("侍者", ( { "shizhe", "zhe" }) );
        set("title", "俠客島打雜弟子");
        set("gender", "男性" );
        set("age", 30);
        set("long",
              "這是個身著黃衣的三十幾歲漢子，垂手站立，面無表情。\n"
             );
        set("attitude", "friendly");
        set("shen_type", 1);

        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);

        set("max_qi", 330);
        set("max_jing", 320);
        set("neili", 300);
        set("max_neili", 300);

        set("combat_exp", 10000);
        set("score", 10000);

        set_skill("force", 40);
        set_skill("dodge", 40);
        set_skill("unarmed", 40);
        set_skill("parry", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 40);
        set_temp("apply/armor", 40);

        create_family("俠客島", 2, "弟子");

        set("inquiry", ([
            "here" : "這裡就是俠客行的中心了，小人在這服侍了這麼久，對其中的秘密也不大清楚。\n",
            "cha"  : "請你稍待，島主嚴令小人現在不得離開此地！\n",
            "yezi" : "請你稍待，島主嚴令小人現在不得離開此地！\n",
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/d/xiakedao/obj/key1")->wear();
}

void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{

        if( !ob || environment(ob) != environment() ) return;
        say("黃衣侍者說道：這位" + RANK_D->query_respect(ob)
           + "想必你也是來參悟武林秘密的吧。這裡就是俠客行\n"
           + "的正中心，周圍共有二十四間石室，你可隨意來去觀看。但一切\n"
           + "要小心在意，千萬不可莽撞行事。本室可供應飲食，不過還是盡\n"
           + "早離去為好。\n"
             );
        return;
}

int accept_object(object who, object ob)
{
        command("smile");

        if( query("money_id", ob) && ob->value() >= 5000 )
        {command("say " + RANK_D->query_respect(who) +
                "如此古道熱腸，兼又身懷絕藝，本來島主不讓我說的，" +
                "但我實在不忍心見死不救。你從西北門進去，把牆壁上的" +
                "那把木刀取下，拿在手上，對你有好處。但你千萬別告訴" +
                "別人，否則你我都有殺身之禍，切記切記！！！" );
        }
        return 1;

}
void die()
{
        object room;

        say("你敢殺我，老子到陰間也不會放過你。\n");
        message_vision("$N慘嚎一聲，死了！\n", this_object());

        room = environment(this_object());
message("vision", "由于侍者死了摔倒在一旁，這時你才發現剛才他站的地方有點奇怪。\n"
        "地板由兩塊石板組成，似乎是個門.上面還有一鑰匙孔(kong) \n", room);

        ::die();
}
