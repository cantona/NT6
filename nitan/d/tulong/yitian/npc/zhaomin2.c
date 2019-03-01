#include <ansi.h>

inherit NPC;

void create()
{
        set_name("趙敏", ({ "zhao min", "min", "zhao"}));
        set("title", HIY "大元紹敏郡主" NOR);
        set("long",
"她臉泛紅霞，容色麗都。十分美麗之中，更帶着三分英氣，三分豪態，同
時雍容華貴，自有一副端嚴之姿，令人肅然起敬，不敢逼視。\n");
        set("gender", "女性");
        set("age", 15);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 30);
        set("str", 15);
        set("int", 25);
        set("con", 25);
        set("dex", 30);

        set("max_qi", 500);
        set("max_jing", 200);
        set("max_neili", 500);
        set("neili", 500);
        set("jiali", 50);
        set("combat_exp", 50000+random(10000));
        set("score", 20000);
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.ren" :),
        }) );

        set_skill("force", 80);
        set_skill("dodge", 80);
        set_skill("unarmed", 80);
        set_skill("sword", 80);
        set_skill("liangyi-jian", 80);
        set_skill("huifeng-jian", 80);
        set_skill("taiji-shengong", 90);
        set_skill("changquan", 80);
        set_skill("lingxu-bu", 80);
        map_skill("dodge", "lingxu-bu");
        map_skill("parry", "liangyi-jian");
        map_skill("sword", "liangyi-jian");
        map_skill("unarmed", "changquan");

        set("inquiry", ([
            "張無忌" :  "張公子遠在崑崙，不知他近來可好？秋冷春寒，可有寒衣？\n",
            "倚天劍" :  "倚天為天下神兵，怎麼，你想要？\n",
        ]));

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/female2-cloth")->wear();
}
