#include <ansi.h>
#include "tiezhang.h"

inherit NPC;
inherit F_MASTER;
int ask_naogui();
void create()
{
        set_name("裘千丈", ({ "qiu qianzhang", "qiu", "qianzhang", "zhang" }));
        set("long", "這是一個白鬚老頭，身穿黃葛短衫，足穿麻鞋，右\n"
                    "手揮着一把大蒲扇。滿臉的油滑無賴的表情。\n");

        set("gender", "男性");
        set("age", 60);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 23);
        set("int", 30);
        set("con", 26);
        set("dex", 25);
        set("env/wimpy", 70);

        set("max_qi", 1500);
        set("max_jing", 1500);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 100);
        set("combat_exp", 100000);
        set("score", 40000);

        set_skill("force", 100);
        set_skill("tiezhang-xinfa", 100);
        set_skill("dodge", 120);
        set_skill("lingxu-bu", 120);
        set_skill("strike", 120);
        set_skill("parry", 120);
        set_skill("tongbi-zhang", 120);
        set_skill("tie-zhang", 120);
        set_skill("chuanxin-zhang", 120);
        set_skill("feilong-zhang", 120);
        set_skill("guyue-chan", 120);
        set_skill("staff", 100);
        set_skill("literate", 80);
        set_skill("martial-cognize", 80);

        map_skill("force", "tiezhang-xinfa");
        map_skill("strike", "tongbi-zhang");
        map_skill("parry", "tongbi-zhang");
        map_skill("dodge", "lingxu-bu");
        map_skill("staff", "feilong-zhang");

        prepare_skill("strike", "tongbi-zhang");

        set("no_teach", ([
                "tie-zhang" : "嘿嘿嘿，這玩意不厲害，我的通臂六合掌才是武林絕"
                              "學，你還是用心練這個吧。",
        ]));

        create_family("鐵掌幫", 15, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.chu" :),
                (: perform_action, "cuff.jia" :),
                (: perform_action, "staff.fei" :),
                (: exert_function, "recover" :),
        }) );


        set("inquiry", ([
                "name" : "記得先父曾給我起過一個名，叫甚麼‘千丈’。我念着不好聽，也就難得用它。\n",
                "here" : "這裏就是鐵掌幫的總壇所在，你如沒事，不要四處亂走，免招殺身之禍！！！\n",
                "鬧鬼" : (: ask_naogui :),
        ]));

        setup();

        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/gangzhang")->wield();
        add_money("silver", 100);

        set("chat_chance", 10);
        set("chat_msg", ({
                CYN "裘千丈大大咧咧的説道：“鐵掌幫上上下下的事情，沒有爺爺不"
                "知道的！”\n" NOR,
                CYN "裘千丈神祕的説道：“一旦內功基礎有成，就可以從花草樹木"
                "中採氣來提高了！”\n" NOR,
        }) );
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("family/family_name", me) && 
             query("family/family_name", me) == "絕情谷" && 
             query("family/master_name", me) == "裘千尺" )
        {
                command("yi");
                command("say 我道是誰，原來是三妹的弟子，我們本來就是一家人。");
                command("sigh");
                command("say 這個事情我做不了主，你還是去找二弟吧。");
                set("move_party/絕情谷—鐵掌幫", 1, me);
                return;
        }

        if( query("shen", me)>0 )
        {
                command("heng");
                command("say 他媽的！爺爺我最恨你這樣心慈手軟的小王八蛋！。");
                return;
        }

        command("say 爺爺我武功蓋世，你這娃娃好好跟着我學，準沒錯！");
        command("recruit "+query("id", me));
}

int accept_fight(object me)
{
        command("say " + RANK_D->query_respect(me) + "怕是活膩了，來來來，讓爺爺教訓教訓你！\n");
        command("say 啊喲，糟糕，糟糕，這會兒當真不湊巧！你等一會，我肚子痛，要出恭！\n");
        return 0;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "孤雁出羣" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tongbi-zhang/chu",
                           "name"    : "孤雁出羣",
                           "sk1"     : "tongbi-zhang",
                           "lv1"     : 80,
                           "force"   : 40,
                           "gongxian": 60,
                           "shen"    : -5000, ]));
                break;

        case "皓月驚空" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/guyue-chan/jing",
                           "name"    : "皓月驚空",
                           "sk1"     : "guyue-chan",
                           "lv1"     : 80,
                           "force"   : 40,
                           "gongxian": 80,
                           "shen"    : -8000, ]));
                break;

        case "龍飛勢" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/feilong-zhang/fei",
                           "name"    : "龍飛勢",
                           "sk1"     : "feilong-zhang",
                           "lv1"     : 160,
                           "force"   : 240,
                           "neili"   : 2500,
                           "gongxian": 400,
                           "shen"    : -20000, ]));
                break;

        default:
                return 0;
        }
}

void unconcious()
{
        die();
}

int ask_naogui()
{
        say( "聽一些幫眾説，經常聽見無名峯上的墳墓中，傳出響聲！嘿嘿！一定有什麼蹊蹺在裏面！\n");
        set_temp("marks/鬧1", 1, this_player());
        return 1;
}
