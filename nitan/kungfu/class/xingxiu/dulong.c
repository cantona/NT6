// dulong.c 毒龍子

inherit NPC;
inherit F_MASTER;
string ask_me();

void create()
{
        set_name("毒龍子", ({ "dulong zi", "dulong", "zi" }));
        set("nickname", "星宿派四弟子");
        set("gender", "男性");
        set("age", 25);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("class", "fighter");
        set("str", 30);
        set("int", 15);
        set("con", 28);
        set("dex", 28);
        
        set("max_qi", 300);
        set("max_jing", 300);
        set("neili", 800);
        set("max_neili", 800);
        set("jiali", 15);
        set("combat_exp", 100000);
        set("score", 20000);

        set_skill("force", 60);
        set_skill("huagong-dafa", 4);
        set_skill("dodge", 60);
        set_skill("zhaixinggong", 50);
        set_skill("claw", 50);
        set_skill("sanyin-wugongzhao", 20);
        set_skill("strike", 50);
        set_skill("chousui-zhang", 20);
        set_skill("parry", 50);
        set_skill("staff", 80);
          set_skill("tianshan-zhang", 80);
//        set_skill("literate", 50);

        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixinggong");
        map_skill("strike", "chousui-zhang");
        map_skill("claw", "sanyin-wugongzhao");
          map_skill("parry", "tianshan-zhang");
          map_skill("staff", "tianshan-zhang");
        prepare_skill("strike", "chousui-zhang");
        prepare_skill("claw", "sanyin-wugongzhao");
        set("inquiry", ([
                "星宿派" : "可惜老仙不準我收徒, 否則你可拜我為師。",
                "深澗"   : "問阿紫吧。",
                "吹捧"   : "小師妹最討老仙喜歡, 你去問她吧。",
                "蕭峰"   : "要不是那廝, 我早逮住了小師妹。",
                "老仙"   : "你得多吹捧老仙, 否則別想有出頭之日。\n",
                "丁春秋" : "丁春秋是你叫的嗎? 沒大沒小的。以後叫老仙! ",
                "星宿海" : "我現在很忙, 找別人帶你去吧。",
                "神王木鼎" : "我可沒提過, 再問我宰了你。",
                "山洞"   : "笨蛋, 把亂石推開不就可以進去了嗎? ",
        ]) );
        create_family("星宿派", 2, "弟子");
        setup();
          carry_object("/clone/weapon/gangzhang")->wield();
          carry_object("/d/xingxiu/obj/changpao")->wear();
}

void attempt_apprentice(object ob)
{
        command("say 我才不想收徒呢。");
}
