// hqniu.c 胡青牛

#include <ansi.h>
inherit NPC;
void create()
{
        string weapon;
        set_name("胡青牛",({"hu qingniu","hu","qingniu"}));
        set("title",HIY"蝶谷醫仙"NOR);
        set("long", "他就是號稱“見死不救”的蝶谷醫仙胡青牛。神清骨秀，臉上帶著冷漠之情。\n");
        set("age", 41);
        set("attitude", "friendly");
        set("shen", -1000);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("per", 30);
        set("max_qi", 3000);
        set("max_jing", 3000);
        set("neili", 5000);
        set("eff_jingli", 3000);
        set("max_neili", 3000);
        set("jiali", 50);
        set("combat_exp", 1500000);
        set("unique", 1);

        set_skill("sword",220);
        set_skill("dodge",220);
        set_skill("force", 220);
        set_skill("blade",220);
        set_skill("qingfu-shenfa", 220);
        set_skill("shenghuo-ling", 220);
        set_skill("lieyan-dao", 220);
        set_skill("liehuo-jian", 220);
        set_skill("parry", 220);
        set_skill("cuff", 220);
        set_skill("qishang-quan",220);
        set_skill("literate", 200);
        set_skill("medical", 200);

        set_skill("shenghuo-shengong",200);
        map_skill("force", "shenghuo-shengong");
        map_skill("cuff","qishang-quan");
        map_skill("blade","shenghuo-lingfa");
        map_skill("sword","liehuo-jian");
        map_skill("dodge", "qingfu-shenfa");
        map_skill("parry", "shenghuo-lingfa");        
        prepare_skill("cuff","qishang-quan");        

        set("inquiry", ([
           "波斯明教" : "我中土明教源于波斯明教，已有百年厲史了",
           "聖火令" : "聽說聖火令是我明教的聖物，但我始終不得一見，實為憾事！",
           "王難姑" : "哎，那是我的發妻，我好想念她......",
           "金花婆婆" : "別提了，昔年因為不救治她丈夫，因而與她結下了深仇。",
//         "秘籍"  : (: ask_miji :),
        ]));
         
        setup();
        weapon = "/clone/weapon/changjian";
        carry_object(weapon)->wield();
        carry_object("/clone/cloth/changpao")->wear();
}