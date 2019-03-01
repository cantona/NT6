// zhangli.c 掌理道長

inherit NPC;
string ask_me();

void create()
{
        set_name("掌理道長", ({"zhangli"}));
        set("gender", "男性");
        set("age", 22);
        set("class", "quanzhen");
        set("long",
                "這是一位年紀很輕的道人，他精明能幹，是全真教第四代弟子\n"
                "中出類拔萃的人物，前輩真人們分派他來掌理全教上下的雜務。\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 22);
        set("int", 22);
        set("con", 22);
        set("dex", 22);

        set("qi", 600);
        set("max_qi", 600);
        set("jing", 400);
        set("max_jing", 400);
        set("neili", 1200);
        set("max_neili", 1200);
        set("jiali", 0);

        set("combat_exp", 30000);
        set("score", 20000);

        set_skill("array", 30);
        set_skill("force", 60);
        set_skill("xiantian-gong", 50);    //先天氣功
        set_skill("sword", 60);
        set_skill("quanzhen-jian", 60);  //全真劍
        set_skill("dodge", 50);
        set_skill("jinyan-gong", 50);   //金雁功
        set_skill("parry", 60);
        set_skill("unarmed", 60);
        set_skill("strike", 60);
        set_skill("haotian-zhang", 50);    //昊天掌
        set_skill("cuff", 60);
        set_skill("chunyang-quan", 50);    //純陽拳
        set_skill("literate", 50);
        set_skill("taoism", 40);

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
        ob = new("/clone/book/daodejing-ii");
        ob->move(this_player());
        return "好吧，這本「道德經」你拿回去好好研讀。";

}
void attempt_apprentice(object ob)
{
        command("say 我不收弟子，你去找別的道長吧。");
}
