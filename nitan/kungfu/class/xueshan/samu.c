#include <ansi.h>
#include "xueshan.h"
#include "tobebonze.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("薩木活佛", ({ "samu huofo", "huofo", "samu" }));
        set("long", @LONG
薩木活佛是雪山寺有道的高僧，對佛法有精深
的研究。只見他身穿一件黃色袈裟，頭帶僧帽。
便似一副若有所思的樣子。
LONG);
        set("title", "雪山寺活佛");
        set("gender", "男性");
        set("class", "bonze");
        set("age", 38);
        set("attitude", "peaceful");
        set("shen_type", -1);

        set("str", 35);
        set("int", 20);
        set("con", 25);
        set("dex", 20);

        set("max_qi", 3500);
        set("max_jing", 2500);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 150);
        set("level", 20);
        set("combat_exp", 800000);

        set_skill("force", 180);
        set_skill("mizong-neigong", 180);
        set_skill("dodge", 160);
        set_skill("shenkong-xing", 160);
        set_skill("hammer", 160);
        set_skill("dali-chu", 160);
        set_skill("xiangmo-chu", 160);
        set_skill("hand", 180);
        set_skill("dashou-yin", 180);
        set_skill("cuff", 180);
        set_skill("yujiamu-quan", 180);
        set_skill("parry", 180);
        set_skill("lamaism", 200);
        set_skill("literate", 200);
        set_skill("sanscrit", 200);
        set_skill("martial-cognize", 180);

        map_skill("force", "mizong-neigong");
        map_skill("dodge", "shenkong-xing");
        map_skill("parry", "xiangmo-chu");
        map_skill("hammer", "xiangmo-chu");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");

        prepare_skill("cuff", "yujiamu-quan");
        prepare_skill("hand", "dashou-yin");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "hand.yin" :),
                (: perform_action, "cuff.jiang" :),
                (: exert_function, "recover" :),
        }));

        create_family("雪山寺", 3, "活佛");

        set("inquiry",([
                "剃度" : (: ask_for_join :),
                "出家" : (: ask_for_join :),
        ]));

        set("master_ob", 3);
        setup();

        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"seng-shoe")->wear();
        carry_object("/d/xueshan/obj/y-jiasha")->wear();
        carry_object("/d/xueshan/obj/sengmao")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) != "男性" )
        {
                command("say 修習密宗內功需要純陽之體。");
                command("say 這位" + RANK_D->query_respect(ob) +
                        "還是請回吧！");
                return;
        }

        if( query("class", ob) != "bonze" )
        {
                command("say 我佛門的清規戒律甚多。");
                command("say 這位" + RANK_D->query_respect(ob) +
                        "還是請回吧！");
                return;
        }

        if( query("family/family_name", ob) != "雪山寺" )
        {
                command("say 這位" + RANK_D->query_respect(ob) +
                        "既非本寺弟子，還是請回吧！");
                return;
        }

        if ((int)ob->query_skill("lamaism", 1) < 60)
        {
                command("say 入我雪山寺，修習密宗心法是首要的。");
                command("say 這位" + RANK_D->query_respect(ob) +
                        "是否還應該多多鑽研本門的心法？");
                return;
        }

        command("smile");
        command("nod");
        command("say 你就隨我學習佛法吧！");
        command("recruit "+query("id", ob));

        set("title", HIY"大喇嘛"NOR, ob);
}
