// xiang.c

#include <ansi.h>;
inherit NPC;
inherit F_MASTER;

#include "fight.h"

void create()
{
        set_name("項長老", ({"xiang zhanglao", "xiang", "zhanglao"}));
        set("nickname", HIR "丐幫六老" NOR);
        set("gender", "男性");
        set("title", "丐幫九袋長老");
        set("age", 59);
        set("attitude", "peaceful");
        set("class", "beggar");
         set("beggarlvl", 9);

        set("str", 30);
        set("int", 24);
        set("con", 30);
        set("dex", 24);

        set("qi", 2000);
        set("max_qi", 2000);
        set("jing", 800);
        set("max_jing", 800);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 200);

        set("combat_exp", 1500000);
        set("score", 200000);
        set("shen", 100000);

        set_skill("force", 150);             // 基本內功
        set_skill("huntian-qigong", 150);    // 混天氣功
        set_skill("dodge", 150);                   // 基本躲閃
        set_skill("xiaoyaoyou", 150);        // 逍遙遊
        set_skill("parry", 150);             // 基本招架
        set_skill("hand", 150);              // 基本手法
        set_skill("suohou-hand", 150);       // 鎖喉擒拿手
        set_skill("blade", 150);             // 基本刀法
        set_skill("liuhe-dao", 150);       // 四象六合刀
        set_skill("begging", 100);           // 叫化絕活
        set_skill("checking", 100);          // 道聽途說
        set_skill("training", 100);          // 馭獸術
        set_skill("strike",85);  // 基本掌法
        set_skill("lianhua-zhang",85); // 蓮花掌
        set_skill("dragon-strike",85);

        map_skill("strike","lianhua-zhang");
        prepare_skill("strike","lianhua-zhang");

        map_skill("force", "huntian-qigong");
        map_skill("hand",  "suohou-hand");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("blade", "liuhe-dao");
        map_skill("parry", "liuhe-dao");
        prepare_skill("hand",  "suohou-hand");

        //set("party/party_name", HIC"丐幫"NOR);
        //set("party/rank", RED"九袋長老"NOR);
        //set("party/level", 9);
        create_family("丐幫", 18, "長老");

        setup();

        carry_object(WEAPON_DIR"gangdao")->wield();
        carry_object(__DIR__"obj/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        command("hmm");
        command("say 走開，我不收徒。");
}
