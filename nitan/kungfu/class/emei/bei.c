// This program is a part of NT MudLIB

#include "emei.h"

inherit NPC;
inherit F_MASTER;
int ask_for_ji();

void create()
{
        set_name("貝錦儀", ({ "bei jinyi", "bei", "jinyi"}));
        set("long", "她是峨嵋派的第四代俗家弟子。\n");
        set("gender", "女性");
        set("age", 21);
        set("attitude", "peaceful");
        set("class", "fighter");
        set("shen_type", 1);

        set("str", 21);
        set("int", 25);
        set("con", 24);
        set("dex", 20);

        set("max_qi", 2100);
        set("max_jing", 1000);
        set("neili", 2500);
        set("max_neili", 2500);
        set("level", 10);
        set("combat_exp", 250000);

        set_skill("throwing", 60);
        set_skill("persuading", 100);
        set_skill("force", 120);
        set_skill("emei-xinfa", 120);
        set_skill("linji-zhuang", 100);
        set_skill("dodge", 100);
        set_skill("zhutian-bu", 100);
        set_skill("strike", 80);
        set_skill("jinding-zhang", 80);
        set_skill("finger", 60);
        set_skill("tiangang-zhi", 60);
        set_skill("parry", 100);
        set_skill("sword", 120);
        set_skill("emei-jian", 120);
        set_skill("huifeng-jian", 120);
        set_skill("literate", 100);
        set_skill("mahayana", 100);
        set_skill("buddhism", 100);
        set_skill("martial-cognize", 20);

        map_skill("force","linji-zhuang");
        map_skill("finger","tiangang-zhi");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","jinding-zhang");
        map_skill("sword","huifeng-jian");
        map_skill("parry","huifeng-jian");

        prepare_skill("strike", "sixiang-zhang");

        set("inquiry", ([
                "出家"     : "你去本山的庵堂裡找我靜字輩師姐吧。她們在福壽庵、千佛庵、\n萬年庵、萬行庵和臥雲庵修行。\n",
                "滅絕師太" : "她是本派掌門人，在華藏庵修行。\n",
                "紀曉芙"   : (: ask_for_ji :),
        ]));

        create_family("峨嵋派", 4, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.xian" :),
                (: perform_action, "strike.xing" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("master_ob", 3);
        set("master_ob", 3);
        set("master_ob", 3);
        setup();

        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"female-cloth")->wear();
        carry_object(CLOTH_DIR"female-shoe")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("say 好吧，我就收下你了。");
        command("recruit "+query("id", ob));
}

int ask_for_ji()
{
        object ob;
        ob = this_player();
        tell_object(ob,"貝錦儀說道：紀曉芙在舍身崖呢。她就是想不開。嗨！\n");
        set("marks/ji", 1, ob);
        return 1;
}
