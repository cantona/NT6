// ma.c 馬超興

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "yunlong.h"

int ask_weiwang();
string ask_me();

void create()
{
        set_name("馬超興", ({ "ma chaoxing", "ma"}));
        set("title", HIR "天地會"HIW"家後堂香主"NOR);
        set("gender", "男性");
        set("long", "\n他就是天地會家後堂香主，矮矮胖胖的個，善使一柄大刀。\n");
        set("class", "fighter");
        set("age", 45);

        set("int", 30);
        set("qi", 1500);
        set("max_qi", 1500);
        set("jing", 500);
        set("max_jing", 500);
        set("shen_type", 1);

        set("combat_exp", 250000);
        set("attitude", "friendly");

        set_skill("force", 80);
        set_skill("unarmed",80);
        set_skill("parry", 80);
        set_skill("dodge", 80);
        set_skill("sword", 70);
        set_skill("blade", 100);
        set_skill("whip", 70);
        set_skill("yunlong-shengong", 70);
        set_skill("yunlong-shenfa", 70);
        set_skill("wuhu-duanmendao", 80);
        set_skill("houquan", 50);
        set_skill("yunlong-jian", 50);
        set_skill("yunlong-bian", 50);
        set_temp("apply/attack", 25);
        set_temp("apply/defense", 25);
        set_temp("apply/damage", 25);

        map_skill("force", "yunlong-shengong");
        map_skill("dodge", "yunlong-shenfa");
        map_skill("parry", "wuhu-duanmendao");
        map_skill("blade","wuhu-duanmendao");
        map_skill("sword", "yunlong-jian");
        map_skill("whip", "yunlong-bian");
        map_skill("unarmed","houquan");

        create_family("雲龍門", 2, "弟子");
        set("book_count", 1);
        set("inquiry", ([
                "陳近南" :  "這是我們的總舵主！\n",
                "天地會" :  "只要是英雄好漢，都可以入我天地會(join tiandihui)。",
                "入會" :  "加入天地會，一同反清復明！\n",
                "反清復明" : "去藥舖和棺材店仔細瞧瞧吧！",
                "威望" :  (: ask_weiwang :),
                "江湖威望" : (: ask_weiwang :),
                "雲龍經" : (: ask_me :),
        ]));
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: command("smile") :),
                (: command("haha") :),
                (: command("chat 這位" + RANK_D->query_respect(this_player()) +
                           "，你我無冤無仇，何必如此？") :),
                (: command("unwield changjian") :),
                (: command("wield changjian") :),
                (: command("wield bian") :),
                (: perform_action, "sword.xian" :),
                (: perform_action, "whip.chan" :),
                (: perform_action, "blade.duan" :),
                (: perform_action, "unarmed.zhen" :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
                (: command("unwield bian") :),
                (: command("wield blade") :),
                (: command("unwield blade") :),
                      }) );
        set("master_ob", 4);
        setup();
        carry_object(CLOTH_DIR"male-cloth")->wear();
        carry_object(CLOTH_DIR"male-shoe")->wear();
        carry_object(WEAPON_DIR"changbian")->wield();
        carry_object(WEAPON_DIR"changjian");
        carry_object(__DIR__"obj/dadao");
        add_money("silver",20);
}

void init()
{
        ::init();
        remove_call_out("greeting");
        call_out("greeting", 1, this_player());
        add_action("do_join","join");
}

int ask_weiwang()
{
        say("馬超興說道：如果你威望值很高，有些人見了你不但"
            "不會殺你，還會教你武功，送你寶貝。\n" +
            "馬超興又說：殺某些壞人或救某些好人可以提高江湖威望。\n");
        return 1;
}

void greeting(object ob)
{
        if (! objectp(ob) || environment(ob) != environment())
                return;

        if(random(5)<2) say( "馬超興笑道：這位" + RANK_D->query_respect(ob)
                + "，可有什麼不平之事麼？\n");
}

string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || 
                fam["family_name"] != "雲龍門")
                return RANK_D->query_respect(this_player()) +"與本派素無來往，不知此話從何談起？";
        if (query("book_count") < 1)
                return "你來晚了，本派的雲龍真經不在此處。";
        addn("book_count", -1);
        ob = new("clone/book/yljing1");
        ob->move(this_player());
        return "好吧，這本「雲龍經」你拿回去好好鑽研。";
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;
/*
        if( query("gender", ob) == "女性" )
        {
                command("say 女人的名字是弱者，我雲龍門頂天立地，怎會收你呢？！");
                return;
        }
*/
        if( query("gender", ob) == "無性" )
        {
                command("say 雲龍門頂天立地，怎會收你這樣的廢人？！");
                return;
        }
        if( query("party/party_name", ob) != "天地會" )
        {
                command("say 你不是本會弟兄，我不能收你！");
                return;
        }
        if ((int)ob->query_skill("yunlong-shengong",1) < 60 )
        {
                command("say 你的本門內功心法太低了,還是努努力先提高一下吧!");
                command("say 好吧，既然" + RANK_D->query_respect(ob) + "也是" +
                "我輩中人，今天就收下你吧。");
                command("recruit "+query("id", ob));
                if( (!query("class", ob)) || (query("class", ob) != "fighter") )
                set("class", "fighter", ob);
        }
}
void reset()
{
        set("book_count", 1);
}

#include "/kungfu/class/yunlong/tiandihui.h"
