// Room: /d/xingxiu/npc/hgirl.c
// Last Modified by winder on Apr. 25 2001

inherit NPC;

void create()
{
        set_name("牧羊女", ({ "muyang nu", "nu", "muyang" }));
        set("gender", "女性");
        set("age", 18 + random(5));
        set("long", "一個維吾爾族女孩。\n");
        set("attitude", "friendly");
        set("env/wimpy", 80);
        set("combat_exp", 500);

        set_skill("unarmed", 5);
        set_skill("dodge", 10);
        set_skill("parry", 10);
        set_skill("whip", 15);

        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);
        set("inquiry", ([
               "星宿派" : "他們躲在星宿海。",
               "星宿海" : "星宿海就是北邊方圓幾百裡的湖泊和沼澤地。\n",
        ]) );

        setup();
        carry_object(__DIR__"obj/wcloth")->wear();
        carry_object(__DIR__"obj/bian")->wield();
}

