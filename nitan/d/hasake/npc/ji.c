// Jay 3/17/96
inherit NPC;
string ask_li();
void create()
{
        set_name("計老人", ({ "ji laoren", "ji"}));
        set("gender", "男性");
        set("age", 83);
        set("long", "滿頭白髮，竟無一根是黑的，身材甚是高大，
只是弓腰曲背，臉上全是皺紋，衰老已極。\n");
        set("attitude", "friendly");
        set("combat_exp", 475000);
        set("shen", 4800);
        set("str", 22);
        set("int", 22);
        set("con", 22);
        set("dex", 24);
        set("max_qi", 800);
        set("max_jing", 500);
        set("neili", 900);
        set("max_neili", 900);
        set("jiali", 10);
        set_skill("changquan", 90);
        set_skill("liuhe-dao", 90);
        set_skill("cuff", 90);
        set_skill("xiaoyaoyou", 90);
        set_skill("force", 90);
        set_skill("huntian-qigong", 90);
        set_skill("blade", 90);
        set_skill("parry", 90);
        set_skill("dodge", 90);
        map_skill("force", "huntian-qigong");
        map_skill("blade", "liuhe-dao");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "liuhe-dao");
        map_skill("cuff", "changquan");
        prepare_skill("cuff", "changquan");
        set("inquiry", ([
            "李文秀" : (: ask_li :),
            "哈薩克人" : "哈薩克人最愛喝又香又烈的美酒。\n",
            "華輝" : "誰？我不知道這個人。\n",
        ]) );
        setup();
        carry_object(__DIR__"obj/bishou")->wield();
        carry_object(__DIR__"obj/yangao")->wear();
      if (clonep(this_object())) 
        carry_object(__DIR__"obj/rousisuo");
}

string ask_li()
{
    object me, ob, where;
    me=this_player();
    ob = find_living("li wenxiu");
    if (!ob) return "這孩子，不知道又跑哪去了，唉。。。\n";
    where = environment(ob);
       if (!where) return "這孩子，不知道又跑哪去了，唉。。。\n";
    return "哦，這孩子好像跑到"+query("short", where)+"玩去了。";
}
