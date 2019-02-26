// This program is a part of NT MudLIB

#include <command.h>
#include <ansi.h>
#include "tobebonze.h"

inherit NPC;
string ask_yao();
string ask_jian();

void create()
{
        set_name("靜風師太", ({ "jingfeng shitai","jingfeng","shitai"}));
        set("long", "她是一位中年師太，只見她眉目底垂，手中握着一把鋼刀。"
                    "自然而然的有股威嚴。\n");
        set("gender", "女性");
        set("age", 42);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "bonze");

        set("str", 21);
        set("int", 21);
        set("con", 27);
        set("dex", 24);

        set("max_qi", 1800);
        set("max_jing", 900);
        set("neili", 2400);
        set("max_neili", 2400);
        set("level", 10);
        set("combat_exp", 250000);

        set_skill("persuading", 80);
        set_skill("force", 140);
        set_skill("throwing", 80);
        set_skill("linji-zhuang", 140);
        set_skill("dodge", 120);
        set_skill("zhutian-bu", 120);
        set_skill("finger", 120);
        set_skill("tiangang-zhi", 120);
        set_skill("hand", 120);
        set_skill("jieshou-jiushi", 120);
        set_skill("parry", 120);
        set_skill("sword", 120);
        set_skill("blade", 130);
        set_skill("emei-jian", 120);
        set_skill("huifeng-jian", 120);
        set_skill("yanxing-dao", 130);
        set_skill("literate", 100);
        set_skill("mahayana", 100);
        set_skill("buddhism", 100);
        set_skill("martial-cognize", 40);

        map_skill("force","linji-zhuang");
        map_skill("finger","tiangang-zhi");
        map_skill("dodge","zhutian-bu");
        map_skill("hand", "jieshou-jiushi");
        map_skill("sword","huifeng-jian");
        map_skill("blade","yanxing-dao");
        map_skill("parry","huifeng-jian");

        prepare_skill("hand", "jieshou-jiushi");
        prepare_skill("finger", "tiangang-zhi");

        set("inquiry", ([
                "傷藥" : (: ask_yao :),
                "武器" : (: ask_jian :),
                "出家" : (: ask_for_join :),
        ]));

        set("gao_count", 4);
        set("jian_count", 2);

        create_family("峨嵋派", 4, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.jie" :),
                (: perform_action, "finger.ling" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        setup();
         carry_object(WEAPON_DIR"gangdao")->wield();
        carry_object(CLOTH_DIR"ni-cloth")->wear();
        carry_object(CLOTH_DIR"ni-shoe")->wear();
}

void attempt_apprentice(object ob)
{
        command ("say 阿彌陀佛！貧尼不收弟子。\n");
        return;
}

string ask_yao()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) ||
           fam["family_name"] != "峨嵋派")
                return RANK_D->query_respect(this_player()) +
                "與本派素無來往，不知此話從何談起？";

        if( query("qi", this_player()) >= query("max_qi", this_player()) )
                return "你未曾受傷，討這藥膏做什麼？";

        if (ob = present("tianxiang gao", this_player()))
                return "你身上不是帶着本門祕藥？";

        if (query("gao_count") < 1)
                return "你來晚了，本門祕藥已盡數給了本派弟子。";

        addn("gao_count", -1);
        ob = new("/d/emei/obj/tianxiang-gao");
        ob->move(this_player());
        return "我這裏有本門祕藥，你拿去療傷吧。";
}

string ask_jian()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) ||
           fam["family_name"] != "峨嵋派")
                return RANK_D->query_respect(this_player()) +
                "與本派素無來往，不知此話從何談起？";

        if (query("jian_count") < 1)
                return "我現在沒有什麼武器好給，你下次在來吧。";

        if (ob = present("ruanjian", this_player()))
                return "你身上不是帶着武器嗎？怎麼還來要！";

        addn("jian_count", -1);
        ob = new("/d/emei/obj/ruanjian");
        ob->move(this_player());
        return "我這裏有一把軟劍，你拿去用吧。";
}
