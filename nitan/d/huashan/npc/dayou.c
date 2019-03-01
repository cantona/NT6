// dayou.c 

inherit NPC;
inherit F_GUARDER;

void create()
{
        set_name("陸大有", ({ "lu dayou", "lu", "dayou" }));
        set("nickname", "六猴兒");
        set("long", 
"陸大有身材很瘦，又長的尖嘴猴腮的，但別看他其貌不揚，他在\n"
"同門中排行第六，是華山派年輕一代中的好手。肩上坐着一隻小\n"
"猴，一對眼睛四處亂轉。\n");
        set("gender", "男性");
        set("age", 26);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 23);
        set("int", 23);
        set("con", 24);
        set("dex", 28);
        
        set("max_qi", 800);
        set("max_jing", 600);
        set("neili", 800);
        set("max_neili", 800);
        set("jiali", 20);
        set("combat_exp", 50000);
        set("score", 5000);

        set_skill("force", 40);
        set_skill("huashan-neigong", 40);
        set_skill("dodge", 60);
        set_skill("parry", 50);
        set_skill("sword", 60);
        set_skill("huashan-sword", 60);

        map_skill("force", "huashan-neigong");
        map_skill("parry", "huashan-sword");
        map_skill("sword", "huashan-sword");

        set("coagents", ({
                ([ "startroom" : "/d/huashan/qunxianguan",
                   "id"        : "yue buqun" ]),
        }));

        create_family("華山派", 14, "弟子");

        setup();
        carry_object("/clone/weapon/changjian")->wield();
}
