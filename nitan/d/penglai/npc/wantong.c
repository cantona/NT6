// 
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("頑童", ({ "wan tong", "wan", "tong" }));

        set("long", "一個可愛的頑童，天真無比。\n");
        
        set("gender", random(2) ? "女性" : "男性");
        set("age", 6);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 200000);
        set("max_jing", 50000);
        set("max_neili", 30000);
        set("neili", 30000);
        set("jiali", 200);
        set("combat_exp", 121);

        
        set("inquiry", ([
                "蓬萊仙島"               :   "啊啊啊，你說的什麼呀，我怎麼沒聽過　……？？\n",
        ]));
             
        setup();

        carry_object("/clone/cloth/cloth")->wear();
}

void unconcious()
{
        die();
}
