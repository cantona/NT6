#include <ansi.h>
#include "wudu.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

void create()
{
        set_name("何紅藥", ({ "he hongyao", "he" }));
        set("nickname", WHT "疤面丐婆" NOR);
        set("long", @LONG
他就是五毒教的長老，教主的姑姑何紅藥。雖然是
教主的長輩，但功夫卻是一塊跟上代教主學的。據
說她曾經被立為教主繼承人，但後來犯下大錯，所
以被罰到此處看守聖地，以贖前罪。她穿著一身破
舊的衣衫，滿臉疤痕，長得骨瘦如柴，雙目中滿是
怨毒之色。
LONG);
        set("title", "五毒教長老");
        set("gender", "女性");
        set("age", 45);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 30);
        set("int", 40);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 4000);
        set("max_jing", 4000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 100);
        set("combat_exp", 1500000);
        set("score", 10000);

        set_skill("force", 180);
        set_skill("wudu-shengong", 180);
        set_skill("xiuluo-yinshagong", 160);
        set_skill("dodge", 180);
        set_skill("wudu-yanluobu", 180);
        set_skill("strike", 180);
        set_skill("tianchan-zhang", 180);
        set_skill("hand", 180);
        set_skill("qianzhu-wandushou", 180);
        set_skill("claw", 180);
        set_skill("wusheng-zhao", 180);
        set_skill("parry", 180);
        set_skill("sword", 180);
        set_skill("jinwu-goufa", 180);
        set_skill("whip", 140);
        set_skill("xiewei-bian", 140);
        set_skill("throwing", 100);
        set_skill("hansha-sheying", 100);
        set_skill("literate", 100);
        set_skill("poison", 120);
        set_skill("wudu-qishu", 120 );
        set_skill("martial-cognize", 160);

        set("no_teach", ([
                "xiuluo-yinshagong"  : "修羅陰煞功必須由教主親傳。",
                "hansha-sheying"     : "含沙射影這技能我都沒能夠學好。",
        ]));

        map_skill("force", "xiuluo-yinshagong");
        map_skill("dodge", "wudu-yanluobu");
        map_skill("strike", "tianchan-zhang");
        map_skill("hand", "qianzhu-wandushou");
        map_skill("claw", "wusheng-zhao");
        map_skill("throwing", "hansha-sheying");
        map_skill("parry", "jinwu-goufa");
        map_skill("sword", "jinwu-goufa");
        map_skill("whip", "xiewei-bian");
        map_skill("poison", "wudu-qishu");

        prepare_skill("strike", "tianchan-zhang");
        prepare_skill("claw", "wusheng-zhao");

        set("coagents", ({
                ([ "startroom" : "/d/wudu/huating1",
                   "id"        : "he tieshou" ]),
        }));

        set("guarder", ([
                "refuse_other": CYN "$N" CYN "身形一晃，擋住$n" CYN
                                "，喝道：沒有教主準許，誰也不得進入"
                                "本教聖地。" NOR,
                "refuse_carry": CYN "$N" CYN "對$n" CYN "喝道：你"
                                "背上背的是什麼人？給我放下來！" NOR,
        ]));

        create_family("五毒教", 11, "長老");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.duo" :),
                (: perform_action, "claw.lian" :),
                (: perform_action, "strike.chan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

        setup();

        carry_object("/d/wudu/npc/obj/jiandao")->wield();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/d/wudu/obj/wuxing");

        add_money("gold",2);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)>-1000 )
        {
                command("say 我越看你越象六扇門派來的臥底。");
                return;
        }
        if( query("shen", ob)>-8000 )
        {
                command("say 你心慈手軟，我是不會收你的！");
                return;
        }
        if( query("combat_exp", ob)<60000 )
        {
                command("say 你還是先去增長點經驗吧。");
                return;
        }
        if ((int)ob->query_skill("wudu-shengong", 1) < 80)
        {
                command("say 你的五毒心法還學的不夠啊。");
                return;
        }
        if ((int)ob->query_skill("wudu-qishu", 1) < 50)
        {
                command("say 我五毒教弟子以毒殺人，修習毒技是首要的。");
                command("say 你是否還應該多多鑽研本門的絕學？");
                return;
        }

       command("nod");
       command("say 不錯，不錯。");
       command("recruit "+query("id", ob));
       set("title", "五毒教護法", ob);
       return;
}
