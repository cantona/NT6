#include <ansi.h>
#include "tiezhang.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

void create()
{
        set_name("司徒焚", ({ "situ fen", "situ", "fen"}));
        set("long", "一個四十來歲的中年男子，他便是鐵掌幫二代人物\n"
                    "中的佼佼者，為人很是精明，深得幫助的喜愛。\n" );
        set("gender", "男性");
        set("age", 40);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
       
        set("qi", 3500);
        set("max_qi", 3500);
        set("jing", 2000);
        set("max_jing", 2000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 120);
        set("combat_exp", 2000000);
        set("score", 40000);

        set_skill("force", 180);
        set_skill("tiezhang-xinfa", 200);
        set_skill("dodge", 200);
        set_skill("dengping-dushui", 200);
        set_skill("strike", 200);
        set_skill("parry", 200);
        set_skill("chuanxin-zhang", 200);
        set_skill("tongbi-zhang", 200);
        set_skill("cuff", 180);
        set_skill("tiexian-quan", 180);
        set_skill("unarmed", 180);
        set_skill("tiexue-dao", 180);
        set_skill("blade", 180);
        set_skill("literate", 160);
        set_skill("martial-cognize", 160);

        map_skill("force", "tiezhang-xinfa");
        map_skill("strike", "chuanxin-zhang");
        map_skill("cuff", "tiexian-quan");
        map_skill("parry", "chuanxin-zhang");
        map_skill("dodge", "dengping-dushui");
        map_skill("blade", "tiexue-dao");

        prepare_skill("strike", "chuanxin-zhang");
        prepare_skill("cuff", "tiexian-quan");

        set("coagents", ({
                ([ "startroom" : "/d/tiezhang/wztang",
                   "id"        : "qiu qianren" ]),
        }));

        create_family("鐵掌幫", 14, "長老");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.xue" :),
                (: perform_action, "cuff.kai" :),
                (: perform_action, "unarmed.zhui" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

        setup();

        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/gangdao")->wield();
        add_money("silver", 200);
}

void attempt_apprentice(object me)
{
        string purename, name, new_name;

        if (! permit_recruit(me))
                return;

        if( query("family/family_name", me) && 
             query("family/family_name", me) == "絕情谷" && 
             query("family/master_name", me) == "裘千尺" )
        {
                command("yi");
                command("say 原來閣下是裘千尺師叔的後裔，想來你和本幫有極深的淵源。");

                command("consider");
                command("say 這個事情我做不了主，你還是直接去找幫主吧。");

                set("move_party/絕情谷─鐵掌幫", 1, me);
                return;
        }

        if( query("shen", me)>-10000 )
        {
                command("heng");
                command("say 你這樣心慈手軟可不行。");
                return;
        }

        if( query("combat_exp", me)<140000 )
        {
                command("heng");
                command("say 你這點能力怎能成大器，還是練練再來吧！");
                return;
        }

        if ((int)me->query_skill("force") < 60)
        {
                command("say 學武之人最講究內功精純，我看你下的工夫還不夠呀。");
                return;
        }

        if ((int)me->query_skill("strike", 1) < 40)
        {
                command("say 入幫之後連最基本的掌法都沒練好，那你入鐵掌幫作甚？");
                return;
        }

        command("say  既然這樣，我便收下你，希望你苦練本幫神功，將之發揚光大。");

        command("recruit "+query("id", me));
}

void init()
{
        object me, ob;
        mapping fam;

        ::init();

        ob = this_player();
        me = this_object();
        
        if (interactive(ob) 
             && !query("no_fight", environment(ob) )
            && ! present("tiezhang ling", ob)
             && !query("move_party/絕情谷─鐵掌幫", ob )
             && ((fam=query("family", ob) )
            && fam["family_name"] != "鐵掌幫" ) )
        {
                if( query_temp("warned", ob)<3 )
                {
                        command("say 站住！你不是鐵掌幫弟子，不能在此久留！");
                        command("say 你還是速速離開此地吧，不然我可要對你不客氣了！！");
                        addn_temp("warned", 1, ob);
                }
           else if( query_temp("stay", ob)<3 )
                        addn_temp("stay", 1, ob);
           else {
                        command("say 你活得不耐煩了，竟敢到鐵掌幫來撒野！\n");
                        remove_call_out("hiting_ob");
                        call_out("hiting_ob", 1, ob);
                }
        }       
}

int hiting_ob(object ob)
{
        object me;
        me = this_object();
        ob->kill_ob(me);
        me->fight_ob(ob);
        remove_call_out("moving_ob");
        call_out("moving_ob",1,ob);
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "血浪滔天" :
                return MASTER_D->teach_pfm(me, this_object(),
                          ([ "perform" : "can_perform/tiexue-dao/xue",
                           "name"    : "血浪滔天",
                           "msg1"    : HIY "$N" HIY "微微一笑，在你"
                                       "耳邊輕聲嘀咕了幾句，然後順"
                                       "手拔出腰間的剛刀凌空劈斬了"
                                       "幾下，招式很是驚奇。你若有"
                                       "所悟的點了點頭。",
                            "sk1"     : "tiexue-dao",
                           "lv1"     : 100,
                           "force"   : 60,
                           "gongxian": 60,
                           "shen"    : -15000, ]));
                break;

        case "穿心錐" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/chuanxin-zhang/zhui",
                           "name"    : "穿心錐",
                           "sk1"     : "chuanxin-zhang",
                           "lv1"     : 100,
                           "force"   : 150,
                           "dodge"   : 220,
                           "neili"   : 200,
                           "gongxian": 200,
                           "shen"    : -18000, ]));
                break;

        case "破甲推山" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tiexian-quan/tui",
                           "name"    : "破甲推山",
                           "sk1"     : "tiexian-quan",
                           "lv1"     : 100,
                           "force"   : 90,
                           "neili"   : 400,
                           "gongxian": 260,
                           "shen"    : -23000, ]));
                break;

        case "穿心錐" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/chuanxin-zhang/zhui",
                           "name"    : "穿心錐",
                           "sk1"     : "chuanxin-zhang",
                           "lv1"     : 100,
                           "force"   : 150,
                           "dodge"   : 220,
                           "neili"   : 200,
                           "gongxian": 200,
                           "shen"    : -18000, ]));
                break;

        default:
                return 0;
        }
}
