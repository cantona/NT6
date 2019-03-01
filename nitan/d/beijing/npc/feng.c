inherit NPC;
#include <ansi.h>

void create()
{
        set_name("馮錫范", ({ "feng xifan", "feng" }) );
        set("title", "武夷派第一高手");
        set("nickname", HIR"一劍無血"NOR);
        set("gender", "男性");
        set("age", 45);
        set("long",
                "馮錫范是延平王府衛隊長，武夷派第一高手，一張白湛湛的面皮。\n"
                "台灣戰敗後歸降朝廷，被封為一等忠臣伯。");
        set("attitude", "peaceful");
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 28);

        set("neili", 2400);
        set("max_neili", 2400);
        set("jiali", 30);
        set("max_qi",2000);
        set("max_jing",1200);

        set("shen_type", -1);
        set("combat_exp", 1000000);

        set_skill("unarmed", 180);
        set_skill("sword", 160);
        set_skill("force", 160);
        set_skill("parry", 160);
        set_skill("dodge", 160);
        set_skill("literate", 100);
        set_skill("huashan-sword", 180);
        set_skill("kuangfeng-jian", 180);
        set_skill("huashan-neigong", 160);
        set_skill("huashan-quan", 170);
        set_skill("huashan-zhang", 170);
        set_skill("huashan-shenfa", 170);

        map_skill("sword", "kuangfeng-jian");
        map_skill("parry", "kuangfeng-jian");
        map_skill("force", "huashan-neigong");
        map_skill("unarmed", "huashan-zhang");
        map_skill("dodge", "huashan-shenfa");
        setup();

        carry_object("/d/beijing/npc/obj/sword3")->wield();
        carry_object("/d/beijing/npc/obj/guanfu5")->wear();
}
