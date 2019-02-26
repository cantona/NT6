// tangtian.c
#include <ansi.h>
#include "tangmen.h"

inherit NPC;
inherit F_MASTER;

int give_job();

void create()
{
        set_name("唐甜", ({ "tang tian", "tang", "tian"}));
        set("long", "唐門中三代弟子的代表人，名列唐門一流高手之中，在武林是也隱然為一方之雄。。\n");
        set("gender", "女性");
        set("age", 25);
        set("class", "tangmen");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 28);
        set("max_qi", 8000);
        set("max_jingli", 1500);
        set("max_douzhi", 500);
        set("douzhi", 500);
        set("neili", 4000);
        set("max_neili", 4000);
        set("yanli",200);
        set("jiali", 100);
        set("combat_exp", 800000);
        set("level", 15);
        set("shen",3000);
        set("score", 7000);

        set_skill("force", 180);
        set_skill("throwing", 180);
        set_skill("dodge", 180);
        set_skill("parry", 180);
        set_skill("literate", 180);
        set_skill("hand", 180);
        set_skill("sword", 180);
        set_skill("boyun-suowu", 180);
        set_skill("poison", 180);
        set_skill("medical", 180);
        set_skill("biyun-xinfa", 180);
        set_skill("qiulin-shiye", 180);
        set_skill("wuzhan-mei", 180);
        set_skill("tangmen-throwing", 180);
        set_skill("tangmen-poison", 180);
        set_skill("tangmen-medical", 180);

        map_skill("force", "biyun-xinfa");
        map_skill("throwing", "tangmen-throwing");
        map_skill("dodge", "qiulin-shiye");
        map_skill("parry", "wuzhan-mei");
        map_skill("sword", "wuzhan-mei");
        map_skill("hand", "boyun-suowu");
        map_skill("medical", "tangmen-medical");
        map_skill("poison", "tangmen-poison");

        prepare_skill("hand", "boyun-suowu");

        create_family("唐門世家", 3, "弟子");

        set("inquiry", ([
                "job" : ( : give_job  : ),
        ]));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 2);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/d/tangmen/obj/feidao")->wield();
        carry_object("/d/tangmen/obj/fhshi")->wield();
        carry_object("/d/tangmen/obj/tiejili")->wield();
        carry_object("/d/tangmen/obj/feidao")->wield();
        carry_object("/d/tangmen/obj/fhshi")->wield();
        carry_object("/d/tangmen/obj/tiejili")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        set_temp("handing", carry_object("/d/tangmen/obj/jili"));
}

int give_job()
{
        object me;
        string msg;
        int whose;

        me = this_player();

        if( query("family/family_name", me) != "唐門世家" )
        {
                command("say “你是什麼人，為什麼會在這裏！”\n");
                return 1;
        }

        if( !environment() || base_name(environment()) != query("startroom") )
        {
                say("唐甜説道:“我現在沒心情給你派活，等我回蓮雲閣再説吧！”\n");
                return 0;
        }

        if( query_temp("tangmen/yao", me) || query_temp("tangmen/biao", me) || query_temp("tangmen/duyao", me) )
                command("say “你已經有任務在身了，還要什麼任務？”\n");
        else
        {
                if( query("combat_exp", me) <= 20000 )
                {
                        command("say “恩...好像製藥房正缺人手！你去問問吧！”\n");
                        set_temp("tangmen/yao", 1, me);
                }
                else if( query("combat_exp", me) <= 50000 )
                {
                        command("say “恩...好像制鏢房正缺人手！你去問問吧！”\n");
                        set_temp("tangmen/biao", 1, me);
                }
                else if( query("combat_exp", me) <= 100000 )
                {
                        command("say “恩...好像製毒房正缺人手！你去問問吧！”\n");
                        set_temp("tangmen/du", 1, me);
                }
                else
                {
                        command("say “你已經有一些武功根基了，可以去外面磨練磨練了！”\n");
                }
        }
        return 1;
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("family/family_name", ob) != "唐門世家" )
        {
                command("say “我四川唐門乃是武林世家，你已是武林中人，我不能收你為徒！”\n");
                return;
        }
        if( query("combat_exp", ob)<500000 )
        {
                command("say “你的經驗太少，不能練好的功夫的！”\n");
                return;
        }

        if ( ob->query_skill("biyun-xinfa", 1) < 80 && ob->query_skill("tangmen-throwing", 1) < 80 )
        {
                command("say “你的心法和暗器不太熟練，要加油啊！”\n");
                return;
        }


        command("say “好吧，從今天起你就是唐甜的弟子了。”\n");
        command("recruit "+query("id", ob));
}

