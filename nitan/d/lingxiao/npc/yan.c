#include <ansi.h>

inherit NPC;
inherit F_GUARDER;

void create()
{
        set_name("燕萬鵬", ({"yan wanpeng", "yan", "wanpeng"}));
        set("gender", "男性");
        set("age", 20);
        set("long", "他是凌霄城第六代弟子燕萬鵬。第六代弟子中，為\n"
                    "人數他最為梗直，素有鐵面之稱，所以在此鎮獄。\n");
        set("age", 24);
        set("attitude", "peaceful");

        set("str", 25);
        set("con", 30);
        set("int", 24);
        set("dex", 30);

        set("max_qi", 3000);
        set("max_jing", 2500);
        set("neili", 2500);
        set("max_neili", 2500);
        set("jiali", 120);
        set("combat_exp", 1000000);

        set_skill("force", 160);
        set_skill("xueshan-neigong", 160);
        set_skill("dodge", 140);
        set_skill("taxue-wuhen", 140);
        set_skill("cuff", 140);
        set_skill("lingxiao-quan", 140);
        set_skill("strike", 140);
        set_skill("piaoxu-zhang", 140);
        set_skill("sword", 160);
        set_skill("hanmei-jian", 160);
        set_skill("yunhe-jian", 160);
        set_skill("parry", 140);
        set_skill("literate", 100);
        set_skill("martial-cognize", 60);

        map_skill("force", "xueshan-neigong");
        map_skill("dodge", "taxue-wuhen");
        map_skill("cuff", "lingxiao-quan");
        map_skill("strike", "piaoxu-zhang");
        map_skill("sword", "yunhe-jian");
        map_skill("parry", "hanmei-jian");

        prepare_skill("strike", "piaoxu-zhang");
        prepare_skill("cuff", "lingxiao-quan");

        set("coagents", ({
                ([ "startroom" : "/d/lingxiao/dilao",
                   "id"        : "bai zizai" ]),
        }));

        set("guarder", ([
                "refuse_other": CYN "$N" CYN "對$n" CYN "喝道："
                                "閣下請止步，下面乃我凌宵宮的禁"
                                "地，外人不得入內！" NOR,
                "refuse_carry": CYN "$N" CYN "對$n" CYN "喝道：你"
                                "背上背的是什麼人？快給我放下來"
                                "！" NOR,
        ]));

        create_family("凌霄城", 6, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chong" :),
                (: perform_action, "cuff.jue" :),
                (: perform_action, "strike.piao" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/clone/weapon/changjian")->wear();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        command("say 我有要事在身，你去找我其它師兄弟們好了。");
}
