// Npc: /d/guiyun/npc/guanjia.c 管家
// Last Modified by winder on Jul. 9 2001

inherit NPC;

void create()
{
        set_name("管家", ({ "guan jia", "guanjia", "guan", "jia" }));
        set("gender", "男性");
        set("age", 44);
        set("long", "他是歸雲莊的管家，負責日常的莊務。\n");
        
        set("combat_exp", 8000);
        set("shen_type", 0);
        set("max_qi", 210);
        set("max_jing", 210);
        set("neili", 310);
        set("max_neili", 310);
        set("jiali", 10);

        set("attitude", "peaceful");
        
        set_skill("unarmed", 35);
        set_skill("dodge", 35);
        set_temp("apply/attack", 24);
        set_temp("apply/defense", 22);

        set("inquiry",([
                "name" : "咳，那麼麻煩幹什麼，有事您就直呼管家好了。",
        ]));
        setup();
        carry_object("/clone/misc/cloth")->wear();
}
