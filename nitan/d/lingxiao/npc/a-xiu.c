#include <ansi.h>
inherit NPC;

string ask_staff();
void create()
{
        set_name("阿繡", ({"a xiu", "xiu", "a"}));
        set("gender", "女性");
        set("title", "凌霄城主孫女");
        set("age", 16);
        set("long", "她是凌霄城主的孫女，十多歲年紀。聰明伶俐\n"
                    "美麗可人。\n");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("con", 30);
        set("per", 30);
        set("int", 24);
        set("dex", 30);

        set("max_qi", 800);
        set("max_jing", 500);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 10);
        set("combat_exp", 100000);
        set("score", 2000);
  set("count", 1);

        set("inquiry", ([
                    "石破天"   : "天哥去了俠客島，也不知道他現在怎麼樣了。",
                    "大粽子"   : "只有我才能這麼叫他，你可不許。",
                    "石中玉"   : "哼，那個傢伙，死不足惜。",
                    "白萬劍"   : "那是我爹呀。",
                    "白自在"   : "那是我爺爺呀。",
                    "金烏杖" : (: ask_staff :),
        ]) );
        set("chat_chance", 5);
        set("chat_msg", ({
                "阿繡凝視着平靜的潭水，説：這潭很奇怪，裏面好像有什麼東西。\n",
                "阿繡看着遠山的悠悠白雲，歎道：你要什麼時候才從俠客島回來。\n",
                       CYN "阿繡忽然皺顰不快，好像想起了什麼可氣之事。\n" NOR,
        }) );

        set_skill("force", 100);
        set_skill("xueshan-neigong", 100);
        set_skill("wuwang-shengong", 80);
        set_skill("dodge", 80);
        set_skill("taxue-wuhen", 80);
        set_skill("cuff", 80);
        set_skill("lingxiao-quan", 80);
        set_skill("strike", 80);
        set_skill("piaoxu-zhang", 80);
        set_skill("sword", 80);
        set_skill("hanmei-jian", 80);
        set_skill("blade", 120);
        set_skill("jinwu-blade", 120);
        set_skill("parry", 80);
        set_skill("literate", 100);
        set_skill("martial-cognize", 20);

        map_skill("force", "wuwang-shengong");
        map_skill("dodge", "taxue-wuhen");
        map_skill("cuff", "lingxiao-quan");
        map_skill("strike", "piaoxu-zhang");
        map_skill("sword", "hanmei-jian");
        map_skill("blade", "jinwu-blade");
        map_skill("parry", "jinwu-blade");

        prepare_skill("strike", "piaoxu-zhang");
        prepare_skill("cuff", "lingxiao-quan");

        create_family("凌霄城", 7, "弟子");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "blade.chi" :),
                (: exert_function, "recover" :)
        }) );

        setup();
        
        carry_object("/clone/weapon/mudao")->wield();
        carry_object("/clone/cloth/xian-cloth")->wear();
        carry_object("/clone/cloth/boots")->wear();
        carry_object("/clone/cloth/belt")->wear();
}

string ask_staff()
{
        object ob;
        object me;
        me = this_player();

        if(query("count") < 1)
                return "這位" +RANK_D->query_respect(me)+"，真是抱歉，金烏杖已經有人幫我給奶奶帶去了。";
    if( query("combat_exp", me)<200000 )
                return "你武功尚未到家，我怎敢把金烏杖交給你？";
        addn("count", -1);
        ob=new(WEAPON_DIR"treasure/jinwu-staff");
        if ( ob->violate_unique() )
        {
                destruct( ob );
                return "你武功尚未到家，我怎敢把金烏杖交給你？";
        }
        else
        {
                ob->move(this_player());
                return "這位" +RANK_D->query_respect(me)+"，請幫我把這把金烏杖帶給我奶奶，真是多謝了。";
        }
}
void attempt_apprentice(object ob)
{
        command("say 我是不收徒的，你進城找我師兄們好了。");
}
