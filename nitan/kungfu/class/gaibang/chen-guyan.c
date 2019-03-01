// chen-guyan.c

#include <ansi.h>;
inherit NPC;
inherit F_MASTER;
#include "fight.h"

void create()
{
        set_name("陳孤雁", ({"chen guyan", "chen", "guyan"}));
        set("nickname", "長臂叟");
        set("gender", "男性");
        set("title", "丐幫九袋長老");
        set("age", 50);
        set("long","他是一個兩條手臂甚長的老者。\n");
        set("attitude", "peaceful");
        set("class", "beggar");
         set("beggarlvl", 9);

        set("str", 24);
        set("int", 20);
        set("con", 24);
        set("dex", 20);

        set("qi", 900);
        set("max_qi", 900);
        set("jing", 100);
        set("max_jing", 100);
        set("neili", 1300);
        set("max_neili", 1200);
        set("jiali", 100);

        set("combat_exp", 100000);
        set("score", 20000);

        set_skill("force", 90); // 基本內功
        set_skill("huntian-qigong", 90); // 混天氣功
        set_skill("blade", 120); // 基本刀法
        set_skill("liuhe-dao", 120); // 四象六合刀
        set_skill("hand", 85); // 基本手法
        set_skill("suohou-hand", 80); // 鎖喉擒拿手
        set_skill("dodge", 95); // 基本躲閃
        set_skill("xiaoyaoyou", 85); // 逍遙遊
        set_skill("parry", 90); // 基本招架

        set_skill("strike",85);  // 基本掌法
        set_skill("lianhua-zhang",85); // 蓮花掌
        set_skill("dragon-strike",85);

        map_skill("strike","lianhua-zhang");
        prepare_skill("strike","lianhua-zhang");
        map_skill("force", "huntian-qigong");
        map_skill("hand", "suohou-hand");
        map_skill("blade", "liuhe-dao");
        map_skill("parry", "liuhe-dao");
        map_skill("dodge", "xiaoyaoyou");
        prepare_skill("hand", "suohou-hand");

        //set("party/party_name", HIC"丐幫"NOR);
        //set("party/rank", RED"九袋長老"NOR);
        //set("party/level", 9);
        create_family("丐幫", 18, "弟子");

        setup();

        carry_object(__DIR__"obj/cloth")->wear();
        carry_object(WEAPON_DIR"gangdao")->wield();
}

void attempt_apprentice(object ob)
{
        command("say 老夫不收徒弟，" + RANK_D->query_respect(ob) + "還是請回吧。");
}
