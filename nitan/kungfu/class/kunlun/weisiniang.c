#include <ansi.h>
#include "kunlun.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("衞四娘", ({"wei siniang", "wei", "siniang"}));
        set("long", "她崑崙派第五代弟子，容顏俏麗，身材豐滿，舉\n"
                    "手投足間帶着點挑逗之意。\n");
        set("nickname", HIY "閃電娘娘" NOR);
        set("gender", "女性");
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

        set_skill("force", 130);
        set_skill("kunlun-xinfa", 130);
        set_skill("dodge", 130);
        set_skill("chuanyun-bu", 130);
        set_skill("hand", 140);
        set_skill("sanyin-shou", 140);
        set_skill("cuff", 140);
        set_skill("zhentian-quan", 140);
        set_skill("parry", 140);
        set_skill("sword", 130);
        set_skill("xunlei-jian", 130);
        set_skill("throwing", 140);
        set_skill("kunlun-qifa", 140);
        set_skill("literate", 140);
        set_skill("liangyi-shengong", 130);
        set_skill("zhengliangyi-jian", 130);
        set_skill("martial-cognize", 120);

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

        create_family("崑崙派", 5, "弟子");

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

        if( query("gender", me) != "女性" )
        {
                command("say 師傅不准我收男弟子，你去找我師兄去吧。");
                return;
        }

        if( query("combat_exp", me)<10000 )
        {
                command("say 你的江湖經驗實在太淺，還是鍛鍊鍛鍊再説吧。");
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
