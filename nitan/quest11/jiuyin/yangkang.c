//yangkang.c
//by zhuifeng 2010

inherit NPC;
string ask_me();
string ask_me2();
#include <ansi.h>;

void create()
{
        set_name("楊康", ({"yang kang", "kang", "yang"}));
        set("gender", "男性");
        set("title", HIC "全真教第三代弟子"NOR );
        set("age", 24);
        set("class", "fighter");
        set("long",
                "他又名完顏康。隨母包惜弱嫁完顏洪烈後，成了小王子，
貪圖富貴，至死不改。\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 26);
        set("int", 25);
        set("con", 25);
        set("dex", 26);
        set("per", 28);
        set("kar", 30);
        set("pur", 15);

        set("chat_chance_combat", 350);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "wuqi" :),
                (: exert_function, "ding" :),
                (: perform_action, "sword.sanqing" :),
                (: perform_action, "sword.lian" :),
                (: perform_action, "claw.jiuyin" :),
        }));

        set("qi", 100000);
        set("max_qi", 10000);
        set("jing", 5000);
        set("max_jing", 5000);
        set("neili", 100000);
        set("eff_jingli",10000);
        set("jingli",10000);
        set("max_neili", 100000);
        set("jiali", 200);
        set("quest/jiuyin2/pass",1);
        set("quest/射雕英雄傳/yangjiaqiang/pass",1);

        set("combat_exp", 4300000);

        set_skill("force", 350);
        set_skill("xiantian-gong", 350);
        set_skill("sword", 350);
        set_skill("quanzhen-jianfa", 350);
        set_skill("dodge", 350);
        set_skill("jinyan-gong", 350);
        set_skill("yangjia-qiang", 120);
        set_skill("spear", 120);
        set_skill("parry", 350);
        set_skill("strike", 350);
        set_skill("haotian-zhang", 350);
        set_skill("claw",350);
        set_skill("jiuyin-baiguzhua", 320);
        set_skill("literate", 200);
        set_skill("taoism", 50);
        set_skill("yinlong-bian", 180);
        set_skill("cuixin-zhang", 200);
        set_skill("whip",200);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
         map_skill("spear", "yangjia-qiang");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("strike", "cuixin-zhang");
        map_skill("claw", "jiuyin-baiguzhua");
        map_skill("whip","yinlong-bian");
        prepare_skill("claw", "jiuyin-baiguzhua");
        
        set("inquiry", ([
    "郭嘯天" : "我不認識。",
    "楊鐵心" : "我不認識。",
    "郭靖" : "我不認識。",
    "李萍" : "我不認識。",
    "包惜弱" : "她是我娘。",
    "穆念慈" : "她是我的女人，你問她幹什麼。",
    "黃蓉" : "誰？？？",
    "完顏洪烈" : "你找我父王什麼事情？",
    "丘處機" : "他是我師父",
    "梅超風" : "他是我師父",
    "歐陽克" : "這小子三番五次調戲念慈，我不會放過他的！",
    "完顏康" : (: ask_me :),
    "楊康" : (: ask_me2 :),


	]));


  set("chat_chance", 5);
 set("chat_msg", ({
       "誰也不能讓我離開我父王，念慈如果每次要我離開，我就先假裝答應她，嘿嘿：女人真好騙！\n",
       "師父要我來嘉興和我義兄比武，此人三番五次壞我好事，這次我要讓他好看，哼、哼！\n",
 }) );
        create_family("全真教", 3, "弟子");

        setup();

        carry_object("/d/fuzhou/npc/obj/txs")->wield();
        carry_object("/clone/armor/jinduan")->wear();
}

string ask_me()
{
        object me,ob;
	ob=this_player();
	me=this_object();
        command("unwield shan"); 
	me->set_name("完顏康", ({ "wanyan kang", "kang","wanyan"}) );
	me->set("title",HIY"大金國小王爺"NOR);
	return "我便是大金國小王爺，你有什麼事情！";
}

string ask_me2()
{
        object me,ob;
	ob=this_player();
	me=this_object();
  command("wield shan");
	me->set_name("楊康", ({ "yang kang", "kang","yang"}) );
	me->set("title",HIC"全真教第三代弟子"NOR);
	return "在下便是楊康，你找我何事！";
}

