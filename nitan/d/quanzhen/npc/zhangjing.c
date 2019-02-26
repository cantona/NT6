// zhangjing.c 掌經道長

inherit NPC;
string ask_me();
string ask_zhipu();

void create()
{
        set_name("掌經道長", ({"zhangjing"}));
        set("gender", "男性");
        set("age", 36);
        set("class", "quanzhen");
        set("long",
                "這位是全真教裏掌管經書的道長。他以前是長安鎮上一個私塾\n"
                "的夫子，因為仰慕大道，才拜到了全真門下。不過畢竟因為年\n"
                "歲大了，功夫的根基扎得不牢，這也正合他意，可以安安心心\n"
                "地研讀經書了。\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 18);
        set("int", 18);
        set("con", 20);
        set("dex", 21);

        set("qi", 500);
        set("max_qi", 500);
        set("jing", 350);
        set("max_jing", 350);
        set("neili", 900);
        set("max_neili", 900);
        set("jiali", 0);

        set("combat_exp", 20000);
        set("score", 15000);

        set_skill("array", 20);
        set_skill("force", 40);
        set_skill("xiantian-gong", 40);    //先天氣功
        set_skill("sword", 40);
        set_skill("quanzhen-jian",40);  //全真劍
        set_skill("dodge", 50);
        set_skill("jinyan-gong", 40);   //金雁功
        set_skill("parry", 50);
        set_skill("unarmed", 50);
        set_skill("strike", 50);
        set_skill("haotian-zhang", 50);    //昊天掌
        set_skill("cuff", 50);
        set_skill("chunyang-quan", 50);    //純陽拳
        set_skill("literate", 100);
        set_skill("taoism", 80);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("strike", "haotian-zhang");
        map_skill("cuff", "chunyang-quan");
        prepare_skill("cuff", "chunyang-quan");
        prepare_skill("strike", "haotian-zhang");

        create_family("全真教", 4, "弟子");

        set("book_count",1);
        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄門正宗。\n",
                "道德經" : (: ask_me :),
                "一陽指" : (: ask_zhipu :),
        ]) );

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/yellowrobe")->wear();
}

string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "全真教" )
                return RANK_D->query_respect(this_player()) +
                "與本教毫無瓜葛，你這話可叫我弄不明白了。";
        if (query("book_count") < 1)
                return "你來晚了，道德經已經被人取走了。";
        addn("book_count", -1);
        ob = new("/clone/book/daodejing-i");
        ob->move(this_player());
        return "好吧，這本「道德經」你拿回去好好研讀，有看不懂的地方來問我。";

}

string ask_zhipu()
{
        object me=this_player();
        if( query_temp("tmark/指", me) == 2){
                addn_temp("tmark/指", 1, me);
                return("一陽指的指法譜向來就是由本教祖師親自收存，從不外傳。\n")
;
        }
        else {
                set_temp("tmark/指", 0, me);
                return("聽説一陽指是天下最王道的指法，我也沒有見過。\n");
        }
}

void attempt_apprentice(object ob)
{
        command("say 我不收弟子，你去找別的道長吧。");
}
