// This program is a part of NT MudLIB

#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

#include "fight.h"

mixed ask_skill1();

void create()
{
        set_name("白世鏡", ({ "bai shijing", "bai", "shijing" }));
        set("long", @LONG
這是一位須眉皆白的老丐，雙目間透出一絲寒
氣。他就是丐幫的傳功長老白世鏡，所擅的纏
絲擒拿手在武林中享名已久。
LONG);
        set("nickname", HIR "大義長老" NOR);
        set("title", "丐幫九袋長老");
        set("gender", "男性");
        set("age", 48);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 4000);
        set("max_jing", 3000);
        set("neili", 4300);
        set("max_neili", 4300);
        set("jiali", 180);
        set("level", 30);
        set("combat_exp", 2200000);
        set("score", 300000);
        set("shen_type", 1);

        set_skill("force", 220);
        set_skill("huntian-qigong", 220);
        set_skill("dodge", 220);
        set_skill("feiyan-zoubi", 220);
        set_skill("unarmed", 200);
        set_skill("cuff", 200);
        set_skill("changquan", 200);
        set_skill("jueming-tui", 200);
        set_skill("strike", 200);
        set_skill("xiaoyaoyou", 200);
        set_skill("hand", 240);
        set_skill("chansi-shou", 240);
        set_skill("parry", 200);
        set_skill("staff", 220);
        set_skill("fengmo-zhang", 220);
        set_skill("jiaohua-bangfa", 220);
        set_skill("begging", 250);
        set_skill("checking", 250);
        set_skill("literate", 180);
        set_skill("training", 160);
        set_skill("martial-cognize", 200);

        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "jueming-tui");
        map_skill("strike", "xiaoyaoyou");
        map_skill("staff", "fengmo-zhang");
        map_skill("hand", "chansi-shou");
        map_skill("parry", "chansi-shou");
        map_skill("dodge", "feiyan-zoubi");

        prepare_skill("hand", "chansi-shou");

        create_family("丐幫", 18, "長老");

        set("inquiry", ([
                "纏絲擒拿" : (: ask_skill1 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.qin" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 150);
        set_temp("apply/armor", 200);

        set("master_ob", 4);
        setup();
        carry_object(__DIR__"obj/cloth")->wear();
        carry_object(WEAPON_DIR"gangzhang")->wield();
}

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_str() < 26)
        {
                command("say 我們丐幫的武藝一向以剛猛為主，" +
                        RANK_D->query_respect(ob) + "臂力太弱，似乎不宜學丐幫的功夫？");
                return;
        }

        if( query("combat_exp", ob)<120000 )
        {
                command("say 你的江湖經驗不夠，還是先向各位長老學習吧。");
                return;
        }

        if( query("shen", ob)<20000 )
        {
                command("say 你身為丐幫弟子，竟然不做好事？");
                return;
        }

        if( query("family/beggarlvl", ob)<4 )
        {
                command("say 你在本幫的地位太低，還是先向其他師父學習吧。");
                return;
        }

        if (ob->query_skill("force") < 90)
        {
                command("say 你的內功火候還不夠，還是先向其他師父學習吧。");
                return;
        }
        command("hmm");
        command("say 我收下你便是，可別給我添麻煩。");
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

        if( query("can_perform/chansi-shou/qin", me) )
                return "這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與在下素不相識，不知此話從何說起？";

        if (me->query_skill("chansi-shou", 1) < 1)
                return "你連纏絲擒拿手都沒學，何談絕招可言？";

        if( query("family/gongji", me)<400 )
                return "你在我們丐幫內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<30000 )
                return "你的俠義正事還做得不夠，這招我暫時還不能傳你。";

        if (me->query_skill("chansi-shou", 1) < 120)
                return "你的纏絲擒拿手火候還不夠，還是下去練高點再來吧。";

        if (me->query_skill("force") < 150)
                return "你現在的內功修為不足，還是練高點再來吧。";

        message_sort(HIY "\n$n" HIY "冷笑一聲，大袖一揮，隨即只見其"
                     "雙手忽折忽扭，或抓或甩，直瑣$N" HIY "各處要脈"
                     "。$N" HIY "見狀不由大驚，連忙左閃右避，招架拆"
                     "解，可始終未能擺脫$n" HIY "的糾纏，心下甚為折"
                     "服。\n\n" NOR, me, this_object());

        command("say 明白了麼。");
        tell_object(me, HIC "你學會了「纏絲擒拿」。\n" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("chansi-shou"))
                me->improve_skill("chansi-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/chansi-shou/qin", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}
