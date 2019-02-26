// sun.c 孫不二
// By Lgg,1998.10

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;

string ask_me();

void create()
{
        set_name("孫不二", ({"sun buer", "sun"}));
        set("gender", "女性");
        set("age", 33);
        set("class", "taoist");
        set("nickname",CYN"清淨散人"NOR);
        set("long",
                "她就是全真教二代弟子中唯一的女弟子孫不二孫真人。她本是\n"
                "馬鈺入道前的妻子，道袍上繡着一個骷髏頭。\n");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 30);
        set("int", 29);
        set("con", 29);
        set("dex", 29);

        set("title","全真七子之末");
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
        }));

        set("qi", 3700);
        set("max_qi", 3700);
        set("jing", 1800);
        set("max_jing", 1800);
        set("neili", 4100);
        set("max_neili", 4100);
        set("jiali", 100);

        set("combat_exp", 660000);

        set_skill("force", 140);
        set_skill("quanzhen-xinfa", 140);
        set_skill("sword", 150);
        set_skill("quanzhen-jian",150);
        set_skill("dodge", 150);
        set_skill("jinyan-gong", 150);
        set_skill("parry", 140);
        set_skill("strike", 140);
        set_skill("chongyang-shenzhang", 140);
        set_skill("haotian-zhang", 140);
        set_skill("literate",100);
        set_skill("finger",120);
        set_skill("zhongnan-zhi", 120);
        set_skill("taoism",100);
        set_skill("cuff",200);
        set_skill("whip",200);
        set_skill("chunyang-quan",200);
        set_skill("duanyun-bian",200);
        set_skill("array",150);
        set_skill("beidou-zhenfa", 150);

        map_skill("force", "quanzhen-xinfa");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("finger", "zhongnan-zhi");
        map_skill("strike", "haotian-zhang");
        prepare_skill("finger", "zhongnan-zhi");
        prepare_skill("strike","haotian-zhang");

        create_family("全真教", 2, "弟子");

        set("book_count",1);
        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄門正宗。\n",
                "昊天掌" :  (: ask_me :),
                "昊天掌法" :  (: ask_me :),
        ]) );

        set("master_ob",3);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/magrobe")->wear();

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) == "男性"){
                command("say 我不收男徒，你還是去拜我幾位師兄為師吧。\n");
                return;
        }
        if ((int)ob->query_skill("quanzhen-xinfa",1) < 50 )
        {
                command("say 你的本門內功心法火候不足,難以領略更高深的武功。");
                return;
        }
        if( query("shen", ob)<6000 )
        {
                command("say 我看你還是多做一些俠義之事吧。\n");
                return;
        }
        command("say 好吧，我就收下你這個徒弟了。");
        command("recruit "+query("id", ob));
}

string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "全真教" )
                return RANK_D->query_respect(this_player()) +
                "與本教毫無瓜葛，我教的武功典籍可不能交給你。";
        if (query("book_count") < 1)
                return "你來晚了，昊天掌譜已經被人取走了。";
        addn("book_count", -1);
        ob = new("/clone/book/zhangfapu");
        ob->move(this_player());
        return "好吧，這本「昊天掌譜」你拿回去好好研讀。";

}
