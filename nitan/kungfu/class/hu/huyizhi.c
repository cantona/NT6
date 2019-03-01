// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

#include <ansi.h>;

inherit NPC;
inherit F_MASTER;

string ask_me();

void create()
{
        set_name("胡逸之", ({ "hu yizhi", "hu", "yizhi" }));
        set("gender", "男性");
        set("nickname", HIR "美刀王" NOR);
        set("character", "光明磊落");
        set("age", 37);
        set("long", @LONG
這人胡子拉碴，頭上裹著一圍白巾，腳下踢著
一雙拖鞋，全然一副鄉農模樣。
LONG);
        set("attitude", "peaceful");
        set("str", 36);
        set("int", 28);
        set("con", 31);
        set("dex", 33);

        set("qi", 6500);
        set("max_qi", 6500);
        set("jing", 2000);
        set("max_jing", 2000);
        set("neili", 4500);
        set("max_neili", 4500);
        set("jiali", 160);
        set("level", 40);
        set("combat_exp", 2000000);

        set_skill("force", 640);
        set_skill("lengyue-shengong", 640);
        set_skill("blade", 660);
        set_skill("baisheng-daofa", 660);
        set_skill("hujia-daofa", 640);
        set_skill("dodge", 640);
        set_skill("sixiang-bufa", 640);
        set_skill("parry", 640);
        set_skill("strike", 640);
        set_skill("tianchang-zhang", 640);
        set_skill("cuff", 640);
        set_skill("hujia-quan", 640);
        set_skill("throwing", 650);
        set_skill("mantian-xing", 650);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);
        set_skill("daojian-xiaotianwai", 800);

        map_skill("force", "lengyue-shengong");
        map_skill("blade", "baisheng-daofa");
        map_skill("dodge", "sixiang-bufa");
        map_skill("parry", "baisheng-daofa");
        map_skill("strike", "tianchang-zhang");
        map_skill("cuff", "hujia-quan");
        map_skill("throwing", "mantian-xing");

        prepare_skill("strike", "tianchang-zhang");
        prepare_skill("cuff",   "hujia-quan");

        create_family("關外胡家", 13, "高手");

        set("inquiry", ([
                "百勝刀法" : (: ask_me :),
                "美刀王"   : "美刀王已經死了，還提他做甚？",
                "陳圓圓"   : "唉！我也沒能和她說上幾句話。",
                "陳園園"   : "唉！我也沒能和她說上幾句話。",
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.heng" :),
                (: perform_action, "cuff.kuai" :),
                (: perform_action, "strike.huang" :),
                (: perform_action, "dodge.fei" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("master_ob",5);
        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

string ask_me()
{
        object ob, me;

        me = this_player();
        if( query("family/family_name", me) != "關外胡家" )
                return "這是在下擅長的本事，你要不要較量較量？\n";

        return "很好... 很好... 既然是胡家弟子，有沒有興趣學學我的百勝刀法？";
}

int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) != "關外胡家" )
        {
                command("say 想偷學我們胡家絕技？嘿嘿...");
                return -1;
        }

        if (skill != "baisheng-daofa")
        {
                command("say 我只傳你百勝刀法，其他還是找你師傅去學吧。");
                return -1;
        }

        if( !query_temp("can_learn/huyizhi/baisheng-daofa", ob) )
        {
                command("say 好！你看清楚了！");
                set_temp("can_learn/huyizhi/baisheng-daofa", 1, ob);
        }

        return 1;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "橫掃千軍" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/baisheng-daofa/heng",
                           "name"    : "橫掃千軍",
                           "sk1"     : "baisheng-daofa",
                           "msg1"    : "$N微微點了點頭，在$n耳旁輕聲"
                                       "嘀咕了幾句，隨即又伸手作刀，"
                                       "左劈右斬比劃演示了半天。$n在"
                                       "一旁默不做聲，直到$N演示結束"
                                       "，突然雙眸一亮，似乎在武學上"
                                       "又有了新的突破。",
                           "msg2"    : "這招乃是我窮集畢生精力所創，"
                                       "威力非同小可。",
                           "lv1"     : 150,
                           "force"   : 200,
                           "gongxian": 600,
                           "shen"    : 8000, ]));
                break;

        default:
                return 0;
        }
}
