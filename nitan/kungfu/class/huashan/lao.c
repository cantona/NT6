// lao-denuo.c

#include <ansi.h>
inherit NPC;
inherit F_GUARDER;
inherit F_MASTER;

#include "qizong.h"

string ask_me(object who);
void create()
{
        set_name("勞德諾", ({ "lao denuo","lao","denuo" }) );
        set("nickname", "老好人");
        set("gender", "男性");
        set("age", 61);
        set("long", "勞德諾是嶽不羣的二弟子，武藝也是不凡。\n");
        set("attitude", "peaceful");

        set("str", 26);
        set("con", 30);
        set("int", 24);
        set("dex", 30);

        set("max_qi", 3400);
        set("max_jing", 1700);
        set("neili", 2800);
        set("max_neili", 2800);

        set("combat_exp", 150000);
        set("shen_type", -1);
        set("score", 5000);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.lao" :),
                (: perform_action, "cuff.song" :),
                (: perform_action, "sword.feng" :),
                (: perform_action, "sword.lian" :),
                (: exert_function, "recover" :)
        }) );

        set_skill("unarmed", 120);
        set_skill("sword", 140);
        set_skill("force", 140);
        set_skill("cuff", 120);
        set_skill("strike", 120);
        set_skill("parry", 120);
        set_skill("dodge", 120);
        set_skill("literate", 100);
        set_skill("martial-cognize", 100);

        set_skill("huashan-sword", 140);
        set_skill("huashan-neigong", 140);
        set_skill("huashan-quan", 120);
        set_skill("huashan-zhang", 120);
        set_skill("huashan-shenfa", 120);

        map_skill("sword", "huashan-sword");
        map_skill("parry", "huashan-sword");
        map_skill("force", "huashan-neigong");
        map_skill("cuff", "huashan-quan");
        map_skill("strike", "huashan-zhang");
        map_skill("dodge", "huashan-shenfa");

        prepare_skill("strike", "huashan-zhang");
        prepare_skill("claw", "huashan-quan");

        set_temp("apply/damage", 100);
        set_temp("apply/armor", 100);

        set("inquiry", ([
                "嶽不羣"     :  "他是我尊師，你找他有事嗎？\n",
                "甯中則"     :  "她是我師母！\n",
                "紫霞祕籍" : (: ask_me :),
        ]));

        set("apply/dodge", 100);

        set("coagents", ({
                ([ "startroom" : "/d/huashan/qunxianguan",
                   "id"        : "yue buqun" ]),
        }));

        create_family("華山派", 14, "弟子");
        set("master_ob",4);
        set("master_ob",2);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if( !permit_recruit(ob) )
                return;

        if( query("shen", ob)<0 )
        {
             command("shake");
             command("say 我華山派乃名門正派，不收你這種心術不正之徒！");
             return;
        }

        command("say 好吧，我就收下你了。");
        command("recruit "+query("id", ob));
}


int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "截手式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-sword/jie",
                           "name"    : "截手式",
                           "sk1"     : "huashan-sword",
                           "lv1"     : 30,
                           "gongxian": 60,
                           "shen"    : 500, ]));
                break;

        case "飛絮飄渺" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-zhang/piao",
                           "name"    : "飛絮飄渺",
                           "sk1"     : "huashan-zhang",
                           "lv1"     : 30,
                           "gongxian": 60,
                           "shen"    : 600, ]));
                break;

        case "蒼松式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-quan/song",
                           "name"    : "蒼松式",
                           "sk1"     : "huashan-quan",
                           "lv1"     : 40,
                           "gongxian": 100,
                           "shen"    : 800, ]));
                break;

        case "劍掌五連環" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-sword/lian",
                           "name"    : "劍掌五連環",
                           "sk1"     : "huashan-sword",
                           "lv1"     : 50,
                           "force"   : 100,
                           "gongxian": 150,
                           "shen"    : 1200, ]));
                break;

        default:
                return 0;
        }
}


string ask_me(object who)
{
        int i;
        object *ob, book;

        if ((random(10) < 8) || is_fighting())
                return "對不起，這件事，我不清楚，你還是問我師傅去吧！\n";

        set_temp("apply/attack",  50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage",  50);

        message("vision",
                YEL "看來這件事你都知道了？臭賊，去死吧！\n"
                "勞德諾使開長劍，招數精奇，狠辣無比，一改整日笑咪咪的模樣。\n" NOR,
                environment(), this_object());


        ob = all_inventory(environment());
        for (i = sizeof(ob) - 1; i >= 0; i--)
        {
                if (! userp(ob[i])) continue;

                if( query_temp("hs/askzixia", ob[i]) )
                {
                        delete_temp("hs/askzixia", ob[i]);
                        book = new("/clone/book/zixia_book");
                        book->move(environment(this_object()));
                }
                kill_ob(ob[i]);
                ob[i]->fight(this_object());
        }

        return "我帶師投藝，忍辱負重，你竟敢打我的主意！\n";
}

