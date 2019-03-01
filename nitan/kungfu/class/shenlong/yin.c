// This program is a part of NT MudLIB
// yin.c

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("殷錦", ({ "yin jin", "yin"}));
        set("title", HIY"神龍教"YEL"黃龍使"NOR);
        set("long", "這是個漢子, 一臉姦相, 明顯是個小人.\n" );
        set("gender", "男性");
        set("age", 44);
        set("str", 22);
        set("int", 29);
        set("con", 26);
        set("dex", 24);

        set("max_qi", 2900);
        set("qi", 2900);
        set("max_jing", 1500);
        set("jing", 1500);
        set("neili", 3500);
        set("max_neili", 3500);
        set("jiali", 50);
        set("combat_exp", 370000);
        set("level", 15);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set_skill("force", 130);
        set_skill("dodge", 120);
        set_skill("strike", 110);
        set_skill("claw", 110);
        set_skill("parry", 120);
        set_skill("staff", 110);
        set_skill("literate", 50);
        set_skill("huagong-dafa", 130);
        set_skill("zhaixinggong", 120);
        set_skill("chousui-zhang", 110);
        set_skill("sanyin-wugongzhao", 110);
        set_skill("shenlong-xinfa", 100);
        set_skill("shedao-qigong", 100);

        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixinggong");
        map_skill("claw", "sanyin-wugongzhao");
        map_skill("strike", "chousui-zhang");
        map_skill("parry", "chousui-zhang");
        prepare_skill("claw", "sanyin-wugongzhao");
        prepare_skill("strike", "chousui-zhang");

        create_family("神龍教", 0, "長老");

        set("inquiry", ([
                "神龍教" : "一般人是入不了我神龍教的(join shenlongjiao).\n",
                "洪安通" : "教主脾氣不好,要討他歡心才好。\n",
                "教主"   : "教主脾氣不好,要討他歡心才好。\n",
                "入教"   : "一般人是入不了我神龍教的(join shenlongjiao).\n",
                "口號"   : "萬年不老！永享仙福！壽與天齊！文武仁聖！\n",
        ]));
        set("master_ob", 4);
        setup();
        carry_object(CLOTH_DIR"cloth")->wear();
        add_money("silver", 10);
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 2, ob);
        }
}

void greeting(object ob)
{
        object obj;
        if (interactive(ob) && objectp(obj = present("used gao", ob)))
        {
                   set("combat_exp", 100000);
                   set("qi",100);
                   set("jing",100);
        }
}

void attempt_apprentice(object ob)
{
        command("say 除了文物仁聖的洪教主，誰有資格收徒？");
        return;
}
