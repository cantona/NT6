// qu.c
#include <ansi.h>
#include "taohua.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name( "曲靈風" ,({ "qu lingfeng", "qu" }));
        set("gender", "男性");
        set("age", 46);
        set("long",
            "曲靈風是黃藥師的大徒弟，也是黃藥師最得意的徒兒。他對黃藥師一貫\n"
            "忠心耿耿，尤其是性格古怪，象極了他師父的邪氣。\n"
            "他身形修長，相貌英俊，白衣飄飄，形容瀟洒。\n");
        set("attitude", "peaceful");
        set("class", "scholar");
        set("str", 24);
        set("int", 31);
        set("con", 28);
        set("dex", 22);
        set("chat_chance", 1);
        set("chat_msg", ({
            "曲靈風說道：“師父疼愛小師妹，他的軟□甲一直由小師妹穿著。”\n",
            "曲靈風自言自語地說道：“這個桃花陣，嗨，不簡單！”\n",
        }));
        set("max_qi", 4200);
        set("max_jing", 2100);
        set("neili", 4400);
        set("max_neili", 4400);
        set("jiali", 50);
        set("shen_type", 0);

        set("combat_exp", 1200000);
        set_skill("force", 160);             // 基本內功
        set_skill("luoying-xinfa", 160);     // 落英心法
        set_skill("unarmed", 150);           // 基本拳腳
        set_skill("xuanfeng-tui", 150);      // 旋風掃葉腿
        set_skill("strike", 140);            // 基本掌法
        set_skill("luoying-shenzhang", 140); // 落英神劍掌
        set_skill("dodge", 170);             // 基本躲閃
        set_skill("anying-fuxiang", 170);    // 暗影浮香
        set_skill("parry", 150);             // 基本招架
        set_skill("sword", 150);             // 基本劍法
        set_skill("luoying-shenjian", 150);  // 落英神劍
        set_skill("qimen-wuxing", 150);      // 奇門五行
        set_skill("literate", 180);          // 讀書識字

        map_skill("force"  , "luoying-xinfa");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("strike" , "luoying-zhang");
        map_skill("dodge"  , "anying-fuxiang");
        map_skill("parry"  , "luoying-shenjian");
        map_skill("sword"  , "luoying-shenjian");

        prepare_skill("unarmed", "xuanfeng-tui");
        prepare_skill("strike" , "luoying-zhang");

        create_family("桃花島", 2, "弟子");

        set("inquiry", ([
           "桃花島":   "這兒就是桃花島，你若不是本派弟子，要過桃花陣。",
           "桃花陣":   "往南就是了。",
           "東邪":     "家師人稱東邪！呵呵。",
           "西毒":     "歐陽鋒是與家師並世齊名的高手，人稱老毒物。",
           "南帝":     "聽家師說段王爺現在出家當了和尚，法名一燈。",
           "北丐":     "北丐洪七公是丐幫幫主，現在揚州城外。",
           "黃蓉":     "她是師父的愛女。",
           "黃藥師":   "你要拜訪家師？"
        ]));
        set("master_ob", 4);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian");
}

void attempt_apprentice(object ob)
{
        string master;
        if (! permit_recruit(ob))
                return;
        
        if( stringp(master=query_temp("taohua/master", ob)) )
        {
                if (master != name())
                {
                        command("say 家師不是讓你拜" + master +
                                "的嗎？你怎麼來找我來了？");
                        return;
                }

                command("say 好吧，既然家師有令，我就收下你了，不過要好好遵守桃花島的規矩。");
                command("recruit "+query("id", ob));
                delete_temp("taohua/master", ob);
                return;
        }

        if( query("family/master_name", ob) == "黃藥師" && 
            query("family/family_name", ob) == "桃花島" )
        {
                command("say 大家都是黃島主的弟子，你就別和我尋開心了。");
                return;
        }

        command("shake");
        command("say 我可不敢擅自收徒，你還是找家師黃島主吧！");
}

int accept_fight(object ob)
{
        command("wield jian");
        return 1;
}
