#include <ansi.h>
inherit NPC;

void create()
{
        set_name("封萬裡", ({"feng wanli", "feng", "wanli"}));
        set("nickname", HIR "風火神龍" NOR);
        set("long", "他是凌霄城第六代弟子封萬裡，是第六代弟子中\n"
                    "最為出類拔萃的人物。其劍法剛猛迅捷，如狂風\n"
                    "似烈火，因此得了個風火神龍的外號。但不知為\n"
                    "何，他少了一只手臂,眼中全是憤怒悔恨之色。\n");
        set("gender", "男性");
        set("age", 34);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 4200);
        set("max_jing", 3500);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 220);
        set("combat_exp", 1200000);

        set_skill("force", 220);
        set_skill("xueshan-neigong", 220);
        set_skill("dodge", 220);
        set_skill("taxue-wuhen", 220);
        set_skill("cuff", 200);
        set_skill("lingxiao-quan", 200);
        set_skill("strike", 200);
        set_skill("piaoxu-zhang", 200);
        set_skill("sword", 240);
        set_skill("hanmei-jian", 240);
        set_skill("yunhe-jian", 240);
        set_skill("xueshan-jian", 240);
        set_skill("parry", 220);
        set_skill("literate", 200);
        set_skill("martial-cognize", 200);

        map_skill("force", "xueshan-neigong");
        map_skill("dodge", "taxue-wuhen");
        map_skill("cuff", "lingxiao-quan");
        map_skill("strike", "piaoxu-zhang");
        map_skill("sword", "xueshan-jian");
        map_skill("parry", "yunhe-jian");

        prepare_skill("strike", "piaoxu-zhang");
        prepare_skill("cuff", "lingxiao-quan");

        create_family("凌霄城", 6, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
                (: perform_action, "sword.chu" :),
                (: perform_action, "cuff.jue" :),
                (: perform_action, "strike.piao" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        setup();
        
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        command("say 我不收徒，快給我滾開！");
}

int accept_fight(object who)
{
        command("say 別以為我少了一臂便好欺負，給我滾開！");
        return 0;
}

int accept_hit(object me)
{
        object obj = this_object();
        command("say 無恥之徒，別以為我少了一臂便能任人宰割，受死吧！\n");
        this_player()->kill_ob(obj);
        kill_ob(me);
        return 1;
}
