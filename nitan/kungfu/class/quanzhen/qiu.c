// This program is a part of NT MudLIB

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_GUARDER;

string ask_job();
void reward_dest(object obj, object ob);
void thank_dest(object obj, object ob);

void create()
{
        set_name("丘處機", ({"qiu chuji", "qiu"}));
        set("gender", "男性");
        set("age", 36);
        set("class", "taoist");
        set("nickname",HIM"長春子"NOR);
        set("long",
                "他就是江湖上人稱‘長春子’的丘處機丘真人，他方面大耳，\n"
                "滿面紅光，劍目圓睜，雙眉如刀，相貌威嚴，平生疾惡如仇。\n");
        set("attitude", "heroism");
        set("shen_type",1);
        set("str", 32);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("title","全真七子之四");

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

        set("qi", 4800);
        set("max_qi", 4800);
        set("jing", 2400);
        set("max_jing", 2400);
        set("neili", 5100);
        set("max_neili", 5100);
        set("jiali", 100);
        set("level", 20);
        set("combat_exp", 1400000);
        set("no_get", 1);

        set_skill("force", 185);
        set_skill("quanzhen-xinfa", 185);
        set_skill("sword", 185);
        set_skill("quanzhen-jian",185);
        set_skill("dodge", 180);
        set_skill("jinyan-gong", 180);
        set_skill("parry", 185);
        set_skill("strike", 185);
        set_skill("chongyang-shenzhang", 185);
        set_skill("haotian-zhang", 185);
        set_skill("literate", 150);
        set_skill("finger",170);
        set_skill("zhongnan-zhi", 170);
        set_skill("taoism",190);
        set_skill("medical", 180);
        set_skill("liandan-shu", 180);
        set_skill("cuff",150);
        set_skill("chunyang-quan",150);
        set_skill("array",150);
        set_skill("beidou-zhenfa", 150);

        map_skill("array","beidou-zhenfa");
        map_skill("force", "quanzhen-xinfa");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("finger", "zhongnan-zhi");
        map_skill("strike", "haotian-zhang");
        prepare_skill("finger", "zhongnan-zhi");
        prepare_skill("strike","haotian-zhang");

        create_family("全真教", 2, "弟子");

        set("coagents", ({
                ([ "startroom" : "/d/quanzhen/shiweishi",
                   "id"        : "ma yu" ]),
                ([ "startroom" : "/d/quanzhen/wanwutang",
                   "id"        : "wang chuyi" ]),
        }));

        set("book_count",1);
        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄門正宗。\n",
                "純陽神通功": "純陽神通功是本門第一絕技，可惜我輩愚昧不堪，都沒有練成。",
                "任務" : (: ask_job :),
                "job" : (: ask_job :),
        ]) );

        set("master_ob",4);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/greenrobe")->wear();

}

void init()
{
        ::init();
        remove_call_out("greeting");
        call_out("greeting", 1, this_player());
}


void greeting(object ob)
{
        mapping fam;
        int i ;
        object me;

        me = this_object();
        if (! ob || environment(ob) != environment() || ! living(me))
                return;

        if (interactive(ob) && base_name(environment()) == query("startroom"))
        {
                if( !(fam=query("family", ob)) || fam["family_name"] != "全真教" )
                {
                        if (ob->is_not_bad())
                                command("say 這裡是本教重地，你走動小心些。");
                        else
                        {
                                command("say 你這魔頭，竟敢闖入我全真重地，我一定要殺了你！");
                                kill_ob(ob);
                        }
                } else
                        command("smile"+query("id", ob));
        }
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("quanzhen-xinfa",1) < 120 )
        {
                command("say 你的本門內功心法火候不足,難以領略更高深的武功。");
                return;
        }
        if( query("shen", ob)<12000 )
        {
                command("say 你目前表現太差！多做點行俠仗義的是再來找我！\n");
                return;
        }
        command("say 好吧，我就收下你這個徒弟了，可別壞了我們全真七子得名頭！");
        command("recruit "+query("id", ob));
}

string ask_job()
{
        mapping job_stat;
        object ob = this_player();
        object me = this_object();
        int good_skill;
        object yaochu;
        object ob2;

        job_stat=query_temp("qz/caiyao", ob);

        if( query("family/family_name", ob) != "全真教" )
                return "這位" + RANK_D->query_respect(ob) + "非我全真教弟子，豈敢勞煩。\n";

        if( query("combat_exp", ob)>2000000 )
                return "這位"+RANK_D->query_respect(ob)+"實戰經驗已經頗高，豈敢勞煩大架。\n";

        if (job_stat)
        {
                command("hmm "+query("id", ob));
                return "你還沒完成任務，就又想要新的？\n";
        }

        command("nod");
        command("say 好，最近煉丹用的草藥都用完了，你去山下樹林裡去採一些回來。");

        if (objectp(yaochu = present("yao chu", ob)))
                destruct(yaochu);

        ob2 = new("/d/quanzhen/obj/yaochu");
        ob2->move(me);
        set_temp("qz/caiyao", 1, ob);
        command("give yao chu to "+query("id", ob));

        return "早去早回，路上要小心一些！\n";
}

int accept_object(object me, object obj)
{
        object ob = this_player();
        int r;
        if (r = ::accept_object(me, obj))
                return r;

        command("say " + obj->name() + "?");

        if( query("id", obj) == "chuanbei" || 
            query("id", obj) == "fuling" || 
            query("id", obj) == "gouzhizi" || 
            query("id", obj) == "heshouwu" || 
            query("id", obj) == "huanglian" || 
            query("id", obj) == "jugeng" || 
            query("id", obj) == "jinyinhua" || 
            query("id", obj) == "shengdi" )
        {

                if( (query("family/family_name", ob) == "全真教") && 
                    (query("id", ob) == query("player", obj)) )
                {
                        call_out("reward_dest", 1, obj, ob);
                } else
                {
                        call_out("thank_dest", 1, obj, ob);
                }

                return 1;
        }

        command( "hmm" );
        command( "say 你給我這東西做什麼？" );
        return 0;
}

void reward_dest(object obj, object ob)
{
        int time;
        object yaochu;

        if (! objectp(ob))
                return;

        if (objectp(yaochu = present("yao chu", ob)))
                destruct(yaochu);

        command("pat "+query("id", ob));
        command("say "+query("name", ob)+"幹的不錯，下去休息一下吧！\n");

        if( query_temp("qz/caiyao", ob) )
        {
                delete_temp("qz/caiyao", ob);
        }
        if (objectp(obj))
        destruct(obj);
}


void thank_dest(object obj, object ob)
{
        command( "jump");
        command( "say 我們很需要這些藥材，多謝啦！\n");
        destruct(obj);
}
