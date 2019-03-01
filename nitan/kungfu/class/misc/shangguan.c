// shangguan.c

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;
inherit F_COAGENT;

string ask_me();

void create()
{
        set_name("上官銀票", ({ "cash" }));
        set("long", "他就是金錢幫幫主。\n");
        set("gender", "男性");
        set("age", 61);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 31);
        set("int", 27);
        set("con", 32);
        set("dex", 30);
        
        set("max_qi", 5000);
        set("max_jing", 3000);
        set("neili", 7000);
        set("max_neili", 7000);
        set("jiali", 160);
        set("combat_exp", 1500000);
        set("score", 70000);

        set_skill("idle-force", 500);
        create_family("金錢幫", 1, "幫主");

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();

}
