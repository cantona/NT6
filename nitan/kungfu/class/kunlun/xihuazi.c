#include <ansi.h>
#include "kunlun.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

void create()
{
        set_name("西華子", ({"xi huazi", "xi", "huazi"}));
        set("long", "他是昆侖派第五代弟子，滿腮虯髯，性子十分暴躁。\n");
        set("gender", "男性");
        set("age", 38);
        set("attitude", "heroism");
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("max_qi", 2000);
        set("max_jing", 1500);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 100);
        set("combat_exp", 1000000);

        set_skill("force", 150);
        set_skill("kunlun-xinfa", 150);
        set_skill("dodge", 120);
        set_skill("chuanyun-bu", 120);
        set_skill("hand", 120);
        set_skill("sanyin-shou", 120);
        set_skill("cuff", 120);
        set_skill("zhentian-quan", 120);
        set_skill("parry", 120);
        set_skill("sword", 150);
        set_skill("xunlei-jian", 150);
        set_skill("throwing", 120);
        set_skill("kunlun-qifa", 120);
        set_skill("literate", 140);
        set_skill("liangyi-shengong", 120);
        set_skill("zhengliangyi-jian", 120);
        set_skill("martial-cognize", 100);

        set("no_teach", ([
                "liangyi-shengong"  : "兩儀神功需得掌門人親自傳授。",
                "zhengliangyi-jian"  : "正兩儀劍法乃本門神功，需要掌門人親自傳授。",
        ]));

        map_skill("force", "liangyi-shengong");
        map_skill("dodge", "chuanyun-bu");
        map_skill("parry", "xunlei-jian");
        map_skill("sword", "zhengliangyi-jian");
        map_skill("cuff", "zhentian-quan");
        map_skill("hand", "sanyin-shou");
        map_skill("throwing", "kunlun-qifa");

        prepare_skill("strike", "kunlun-zhang");
        prepare_skill("cuff", "zhentian-quan");

        set("coagents", ({
                ([ "startroom" : "/d/kunlun/tieqinju",
                   "id"        : "he taichong" ]),
        }));

        set("guarder", ([
                "refuse_other": CYN "$N" CYN "對$n" CYN "怒喝道："
                                "他奶奶的，你是什麼人？昆侖派豈是"
                                "讓你隨便走動地方？" NOR,
                "refuse_carry": CYN "$N" CYN "對$n" CYN "喝道：你"
                                "背上背的是什麼人？給我放下來！" NOR,
        ]));

        create_family("昆侖派", 5, "弟子");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "cuff.shi" :),
                (: perform_action, "sword.xun" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),

        }) );

        set("master_ob",3);
        setup();
        carry_object("/d/kunlun/obj/sword")->wield();
        carry_object("/d/kunlun/obj/pao3")->wear();
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("gender", me) == "女性" )
        {
                command("say 師傅不準我收女弟子，你去找我幾個師妹吧。");
                return;
        }

        if( query("combat_exp", me)<10000 )
        {
                command("say 你的江湖經驗實在太淺，還是鍛煉鍛煉再說吧。");
                return;
        }

        if ((int)me->query_skill("kunlun-xinfa", 1) < 30)
        {
                command("say 你對本門的內功心法所知尚淺，練習高了再來找我吧。");
                return;
        }

        command("say 既然" + RANK_D->query_respect(me) + "這麼努力，我就收下你吧。");
        command("recruit "+query("id", me));
}
