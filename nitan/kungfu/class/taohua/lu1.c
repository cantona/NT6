// lu.c
#include <ansi.h>
#include "taohua.h"

inherit NPC;                                                                    
inherit F_MASTER;

void create()
{
        set_name( "陸乘風" ,({ "lu chengfeng", "lu" }));
        set("gender", "男性");
        set("age", 52);
        set("long",
            "陸乘風是黃藥師的第四個徒弟。\n"
            "他的鬢角已微見白發，但身材魁梧，雙眼有神。\n");
        set("attitude", "friendly");
        set("class", "scholar");
        set("str", 24);
        set("int", 30);
        set("con", 25);
        set("dex", 21);

        set("max_qi", 4000);
        set("max_jing", 2000);
        set("neili", 4200);
        set("max_neili", 4200);
        set("jiali", 50);
        set("shen_type",1);

        set("combat_exp", 1500000);

        set_skill("force", 170);            // 基本內功
        set_skill("luoying-xinfa", 170);    // 落英心法
        set_skill("unarmed", 160);          // 基本拳腳
        set_skill("xuanfeng-tui", 160);     // 旋風掃葉腿
        set_skill("strike", 160);           // 基本掌法
        set_skill("luoying-shenzhang", 160);// 落英神劍掌
        set_skill("dodge", 150);            // 基本躲閃
        set_skill("anying-fuxiang", 150);   // 暗影浮香
        set_skill("parry", 160);            // 基本招架
        set_skill("sword", 160);            // 基本劍法
        set_skill("luoying-shenjian", 160); // 落英神劍
        set_skill("literate", 140);         // 讀書識字

        map_skill("force"  , "luoying-xinfa");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("strike" , "luoying-zhang");
        map_skill("dodge"  , "anying-fuxiang");
        map_skill("parry"  , "luoying-shenjian");
        map_skill("sword"  , "luoying-shenjian");

        prepare_skill("unarmed", "xuanfeng-tui");
        prepare_skill("strike" , "luoying-zhang");

        set("jinbing", 10);
        create_family("桃花島", 2, "弟子 歸雲莊主");

        set("inquiry", ([
           "桃花島":   "這兒就是桃花島，你若不是本派弟子，要過桃花陣。",
           "桃花陣":   "往南就是了。",
           "東邪":     "家師人稱東邪！呵呵。",
           "西毒":     "歐陽鋒是與家師並世齊名的高手，人稱老毒物。",
           "南帝":     "聽家師說段王爺現在出家當了和尚，法名一燈。",
           "北丐":     "北丐洪七公是丐幫幫主，現在揚州城外。",
           "黃蓉":     "她是師父的愛女。",
           "黃藥師":   "你要拜訪家師？"
        ]) );
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

int accept_object(object who, object ob)
{
        int exp;
        if (query("jinbing") < 0)
        {
                command("say " + RANK_D->query_respect(who) + "我很累，你回頭再來領賞吧。");
                return 0;
        }
        if( strsrch(query("name", ob),"完顏康的頭顱")<0 && 
            strsrch(query("name", ob),"完顏洪烈的頭顱")<0 && 
            strsrch(query("name", ob),"歐陽鋒的頭顱")<0 && 
            strsrch(query("name", ob),"歐陽克的頭顱")<0 && 
            strsrch(query("name", ob),"彭連虎的頭顱")<0 && 
            strsrch(query("name", ob),"樑子翁的頭顱")<0 && 
            strsrch(query("name", ob),"靈智上人的頭顱")<0 && 
            strsrch(query("name", ob),"沙通天的頭顱")<0 && 
            strsrch(query("name", ob),"侯通海的頭顱")<0 && 
            strsrch(query("name", ob),"沈青剛的頭顱")<0 && 
            strsrch(query("name", ob),"吳青烈的頭顱")<0 && 
            strsrch(query("name", ob),"馬青雄的頭顱")<0 && 
            strsrch(query("name", ob),"錢青健的頭顱")<0 && 
            strsrch(query("name", ob),"大金兵的頭顱")<0 && 
            strsrch(query("name", ob),"段天德的頭顱")<0 )
        {
                command("say 給我這些東西有什麼用？\n");
                return 0;
        }
        else
        {
                command("say 不錯不錯，我一直想殺這些金狗，謝你代勞了。");
        }
        exp = 20+random(30);
        addn("jinbing", -1);
        tell_object(who,HIW"陸乘風獎勵了你\n"+chinese_number(exp)+"點實戰經驗\n"NOR);
        return 1;
}
