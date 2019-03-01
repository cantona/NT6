#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("黃伯流", ({ "huang boliu", "huang", "boliu"}));
        set("title", "黃河幫幫主");
        set("nickname", HIW "銀髯蛟" NOR);
        set("long", @LONG
這便是日月神教黃河幫幫主黃伯流，他看上去
已經甚為蒼老了，但是雙目精光四射，銀髯飄
飄，模樣威武之極。
LONG);
        set("gender", "男性");
        set("class", "scholar");
        set("age", 81);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 36);
        set("int", 36);
        set("con", 36);
        set("dex", 36);
        
        set("max_qi", 4000);
        set("max_jing", 3000);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 150);
        set("combat_exp", 2500000);
        set("score", 30000);

        set_skill("force", 180);
        set_skill("tianhuan-shenjue", 180);
        set_skill("riyue-xinfa", 180);
        set_skill("dodge", 180);
        set_skill("juechen-shenfa", 180);
        set_skill("cuff", 180);
        set_skill("zhenyu-quan", 180);
        set_skill("claw", 180);
        set_skill("poyue-zhao", 180);
        set_skill("parry", 180);
        set_skill("blade", 180);
        set_skill("danding-dao", 180);
        set_skill("strike", 180);
        set_skill("qingmang-zhang", 180);
        set_skill("martial-cognize", 180);
        set_skill("literate", 140);

        map_skill("dodge", "juechen-shenfa");
        map_skill("force", "tianhuan-shenjue");
        map_skill("blade", "danding-dao");
        map_skill("strike", "qingmang-zhang");
        map_skill("parry", "danding-dao");
        map_skill("cuff", "zhenyu-quan");
        map_skill("claw", "poyue-zhao");

        prepare_skill("claw", "poyue-zhao");
        prepare_skill("cuff", "zhenyu-quan");

        create_family("黃河幫", 7, "幫主");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.kou" :),
                (: perform_action, "cuff.tong" :),
                (: perform_action, "claw.duan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

        set("master_ob",3);
        setup();

        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
             command("say 我不收徒。\n");
}
