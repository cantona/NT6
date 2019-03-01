// This program is a part of NT MudLIB
// lu.c

#include <ansi.h>

inherit NPC;

inherit F_MASTER;
string ask_me();

void create()
{
        set_name("陸高軒", ({ "lu gaoxuan", "lu" ,"gaoxuan"}));
        set("title", HIY"神龍教"NOR"軍師");
        set("nickname",HIC "神機妙算" NOR);
        set("long", "他天庭飽滿，地闊方圓，容貌頗為英俊。\n然而滿面愁容，恰"
                    "似頃刻間便有殺身之禍一般。\n");
        set("gender", "男性");
        set("age", 37);

        set("str", 24);
        set("int", 35);
        set("con", 26);
        set("dex", 25);

        set("max_qi", 3500);
        set("qi", 3500);
        set("max_jing", 1800);
        set("jing", 1800);
        set("neili", 3300);
        set("max_neili", 3300);
        set("jiali", 30);
        set("level", 12);
        set("combat_exp", 360000);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set_skill("force", 120);
        set_skill("shenlong-xinfa", 120);
        set_skill("dodge", 120);
        set_skill("yixing-bufa", 120);
        set_skill("hand", 120);
        set_skill("shenlong-bashi", 120);
        set_skill("parry", 120);
        set_skill("staff", 120);
        set_skill("shedao-qigong", 120);
        set_skill("literate", 120);

        map_skill("force", "shenlong-xinfa");
        map_skill("dodge", "yixing-bufa");
        map_skill("hand", "shenlong-bashi");
        map_skill("parry", "shedao-qigong");
        map_skill("staff", "shedao-qigong");
        prepare_skill("hand", "shenlong-bashi");

        create_family("神龍教", 0, "閒散教眾");

        set_temp("apply/damage", 60);
        set("book_count", 1);

        set("inquiry", ([
                "神龍教" : "一般人是入不了我神龍教的(join shenlongjiao).\n",
                "入教"   : "一般人是入不了我神龍教的(join shenlongjiao).\n",
                "洪安通" : "教主脾氣不好,要討他歡心才好。\n",
                "教主"   : "教主脾氣不好,要討他歡心才好。\n",
                "口號"   : "萬年不老！永享仙福！壽與天齊！文武仁聖！",
                "秘籍"   : (: ask_me :),
        ]) );
        set("master_ob", 3);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 10);
}

void init()
{
        object ob;

        if (interactive(ob = this_player()) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 2, ob);
        }
}

void greeting(object ob)
{
        object obj;
        if (! objectp(ob)) return;
        if (interactive(ob) && objectp(obj = present("used gao", ob)))
        {
                set("combat_exp", 1000000);
                set("qi", 1500);
                set("jing", 1500);
        }
}

void attempt_apprentice(object ob)
{
        command("sigh");
        command("say 老夫忙得很，現不收徒。");
}

string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "神龍教" )
                return RANK_D->query_respect(this_player()) +
                "與本教素無來往，不知此話從何談起？";

        if (query("book_count") < 1)
                return "你來晚了，本教的秘籍不在此處。";

        addn("book_count", -1);

        if (random(2) == 0) ob = new("/clone/book/shoufa");
        else ob = new("/clone/book/bufa");

        ob->move(this_player());
        return "好吧，這本「"+query("name", ob)+"」你拿回去好好鑽研。";
}
