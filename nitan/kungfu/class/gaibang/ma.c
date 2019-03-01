// This program is a part of NT MudLIB
// ma.c 馬大元

#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

mixed ask_skill1();

void create()
{
        set_name("馬大元", ({ "ma dayuan", "ma", "dayuan" }));
        set("long", @LONG
這是一個四十多歲的精壯漢子，身材魁梧，雙
目如電。此人就是丐幫副幫主馬大元。
LONG);
        set("nickname", CYN "鐵爪鎖喉" NOR);
        set("title", "丐幫副幫主");
        set("gender", "男性");
        set("age", 48);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 4500);
        set("max_jing", 3500);
        set("neili", 4800);
        set("max_neili", 4800);
        set("jiali", 220);
        set("combat_exp", 2500000);
        set("level", 30);
        set("score", 500000);
        set("shen_type", 1);

        set_skill("force", 240);
        set_skill("huntian-qigong", 240);
        set_skill("dodge", 240);
        set_skill("feiyan-zoubi", 240);
        set_skill("unarmed", 200);
           set_skill("cuff", 200);
        set_skill("changquan", 200);
        set_skill("jueming-tui", 200);
        set_skill("claw", 240);
        set_skill("suohou-gong", 240);
        set_skill("strike", 200);
        // set_skill("tongchui-zhang", 240);
        set_skill("dragon-strike", 200);
        set_skill("parry", 240);
        set_skill("staff", 240);
        set_skill("dagou-bang", 240);
        set_skill("fumo-zhang", 240);
        set_skill("begging", 280);
        set_skill("checking", 280);
        set_skill("literate", 260);
        set_skill("martial-cognize", 240);

        set("no_teach", ([
                "dagou-bang"    : "打狗棒法向來只有繼位幫主能夠學"
                                  "習，要學去找幫主。",
                "dragon-strike" : "降龍十八掌向來只有和幫主學習。",
        ]));

        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "chanquan");
        map_skill("strike", "dragon-strike");
        map_skill("staff", "dagou-bang");
        map_skill("claw", "suohou-gong");
        map_skill("parry", "suohou-gong");
        map_skill("dodge", "feiyan-zoubi");

        prepare_skill("claw", "suohou-gong");

        create_family("丐幫", 18, "副幫主");

        set("inquiry", ([
                "鐵爪鎖喉" : (: ask_skill1 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "claw.suo" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",4);
        setup();
        carry_object(WEAPON_DIR"gangdao")->wield();
        carry_object(__DIR__"obj/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        if (! permit_recruit(ob))
                return;

        if( query("combat_exp", ob)<200000 )
        {
                command("say 你的江湖經驗不夠，還是先向各位長老學習吧。");
                return;
        }

        if( query("shen", ob)<30000 )
        {
                command("say 你身為丐幫弟子，竟然不做好事？");
                return;
        }

        if( query("family/beggarlvl", ob)<5 )
        {
                command("say 你在本幫的地位太低，還是先向各位長老學習吧。");
                return;
        }

        if ((int)ob->query_str() < 26)
        {
                command("say 我的武藝以剛猛為主，你膂力不行，還是算了吧。");
                return;
        }

        if (ob->query_skill("force") < 150)
        {
                command("say 你的內功火候還不夠，還是先向各位長老學習吧。");
                return;
        }
        command("nod");
        command("say 我今日便收你為徒，倘若勤懇努力，將來必有一番作為。");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "beggar" )
                set("class", "beggar", ob);

        if (lvl > 0)
        {
                set("family/beggarlvl", lvl, ob);
                set("title", title, ob);
        }
}

mixed ask_skill1()
{
        object me;
        me = this_player();

        if( query("can_perform/suohou-gong/suo", me) )
                return "自己下去練習，別老是糾纏不休。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "那是江湖上朋友送的外號，你問這個幹嘛？";

        if (me->query_skill("suohou-gong", 1) < 1)
                return "你學過鎖喉功嗎？不學哪來絕招。";

        if( query("family/gongji", me)<400 )
                return "你在丐幫內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<20000 )
                return "你俠義正事做得不夠，這招我暫時還不能傳你。";

        if (me->query_skill("suohou-gong", 1) < 150)
                return "你的鎖喉功還不到家，要多練練。";

        message_sort(HIY "\n$n" HIY "笑了笑，將$N" HIY "招至身旁，輕"
                     "聲在$N" HIY "耳邊低聲吩咐了幾句，不時還握拳成爪"
                     "比劃演示，全是鎖喉功絕招的精微要詣，$N" HIY "一"
                     "邊聽一邊不住地點頭。\n\n" NOR, me, this_object());

        command("nod");
        command("say 這便是鎖喉功的要詣所在，可記清楚了？");
        tell_object(me, HIC "你學會了「鐵爪鎖喉」。\n" NOR);

        if (me->can_improve_skill("claw"))
                me->improve_skill("claw", 1500000);
        if (me->can_improve_skill("suohou-gong"))
                me->improve_skill("suohou-gong", 1500000);

        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/suohou-gong/suo", 1, me);
        addn("family/gongji", -400, me);
        return 1;
}
