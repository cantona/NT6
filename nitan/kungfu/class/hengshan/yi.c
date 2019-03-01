// Last Modified by Sir on May. 22 2001
// yi.c
inherit NPC;
inherit F_MASTER;

#include <ansi.h>;
#include "hengshan.h";
#include "tobebonze.h";

string ask_for_join();
string ask_me();
void create()
{
        set_name("定逸師太", ({ "dingyi shitai", "shitai", "dingyi" }) );
        set("long",
        "她是恆山派的定逸師太，性格剛猛，為人正直，有巾幗不讓須眉之風。\n"
        "她眼中精光四射，絕無半點老態。\n");
        set("gender", "女性");
        set("class", "bonze");
        set("age", 45);
        set("attitude", "peaceful");
        set("per", 24);
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 28);
        set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
                "join"  : (: ask_for_join :),
                "秘籍"  : (: ask_me :),
                "手法精要" : (: ask_me :),
                "還俗"  : "恆山弟子，不能還俗。",
        ]));
        set("env/wimpy", 60);

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
                (: perform_action, "sword.yuyin" :),
                (: perform_action, "sword.yuyin" :),
                (: perform_action, "sword.yuyin" :),
                (: perform_action, "sword.liuyun" :),
                (: perform_action, "sword.liuyun" :),
                (: perform_action, "sword.liuyun" :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("wield changjian") :),
                (: command("wield changjian") :),
                (: command("wield chacngjian") :),
                (: command("wield changjian") :),
                (: perform_action, "hand.break" :),
                (: perform_action, "hand.break" :),
                (: perform_action, "hand.break" :),
                (: perform_action, "strike.diezhang" :),
                (: perform_action, "strike.diezhang" :),
                (: perform_action, "strike.diezhang" :),
        }));

        set("max_qi", 4000);
        set("max_jing", 2000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali",100);
        set("jingli", 1500);
        set("max_jingli", 1500);
        set("combat_exp", 1500000);
        set("score", 1000);
        set("book_count", 1);

        set_skill("unarmed", 200);
        set_skill("sword", 180);
        set_skill("force", 200);
        set_skill("parry", 200);
        set_skill("dodge", 200);
        set_skill("strike", 180);
        set_skill("hand", 150);
        set_skill("buddhism", 150);
        set_skill("baiyun-xinfa",180);
        set_skill("hengshan-jian", 250);
        set_skill("chuanyun-shou",250);
        set_skill("tianchang-zhang",250);
        set_skill("lingxu-bu", 250);
        set_skill("literate", 100);

        map_skill("force","baiyun-xinfa");
        map_skill("sword", "hengshan-jian");
        map_skill("strike","tianchang-zhang");
        map_skill("hand","chuanyun-shou");
        map_skill("parry", "hengshan-jian");
        map_skill("dodge", "lingxu-bu");

        create_family("恆山派", 13, "弟子");
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void init()
{
        add_action("do_kneel", "kneel");
}

void attempt_apprentice(object ob)
{
        string name, new_name;

        if (! permit_recruit(ob))
                return;

        if( query("class", ob) != "bonze" )
        {
                command ("say 阿彌陀佛！貧尼不收俗家弟子。");
                return;
        }

        if ((int)ob->query_skill("baiyun-xinfa",1) < 90 )
        {
                command("say 你的本門內功心法火候不足,難以領略更高深的武功。");
                return;
        }
        if( query("shen", ob)<100000 )
        {
                command( "say 你若能多為俠義之舉，當能承我衣砵。\n");
                return;
        }

        command("say 阿彌陀佛，善哉！善哉！好吧，我就收下你了。");
        command("say 希望你能努力行善，濟度眾生，以光大我恆山派。");
        command("recruit "+query("id", ob));
        name=query("name", ob);
        new_name = "儀" + name[2..3];
        command("say 從今以後你的法名叫做" + new_name + "。");
        set("name", new_name, ob);
}

string ask_me()
{
        object ob;

        if( query("family/family_name", this_player()) != "恆山派" )
                return RANK_D->query_respect(this_player()) +
                "與本派毫無瓜葛，我派的武功典籍可不能交給你。";
        if (query("book_count") < 1)
                return "你來晚了，本派的秘籍不在此處。";
        addn("book_count", -1);
        ob = new("/clone/book/basic_hand_book");
        ob->move(this_player());
        command("rumor"+query("name", this_player())+"拿到手法精要啦。\n");
        return "好吧，這本「手法精要」你拿回去好好鑽研。";
}
