#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

#include "fight.h"

mixed ask_skill1();

void create()
{
        set_name("奚長老", ({ "xi zhanglao", "xi", "zhanglao" }));
        set("long", @LONG
奚長老乃丐幫元老，武功甚為了得。
LONG);
        set("nickname", HIR "大智長老" NOR);
        set("title", "丐幫九袋長老");
        set("gender", "男性");
        set("age", 53);
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

        set_skill("force", 240);
        set_skill("huntian-qigong", 240);
        set_skill("dodge", 200);
        set_skill("feiyan-zoubi", 200);
        set_skill("unarmed", 220);
           set_skill("cuff", 200);
        set_skill("changquan", 200);
        set_skill("jueming-tui", 220);
        set_skill("strike", 220);
        // set_skill("tongchui-zhang", 220);
        set_skill("xiaoyaoyou", 220);
        set_skill("blade", 220);
        set_skill("liuhe-dao", 200);
        set_skill("parry", 200);
        set_skill("staff", 240);
        set_skill("fumo-zhang", 240);
        set_skill("begging", 250);
        set_skill("checking", 250);
        set_skill("literate", 180);
        set_skill("martial-cognize", 220);

        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "jueming-tui");
        map_skill("strike", "xiaoyaoyou");
        map_skill("blade", "liuhe-dao");
        map_skill("staff", "fumo-zhang");
        map_skill("parry", "fumo-zhang");
        map_skill("dodge", "feiyan-zoubi");

        prepare_skill("strike", "xiaoyaoyou");
        prepare_skill("unarmed", "jueming-tui");

        create_family("丐幫", 18, "長老");

        set("inquiry", ([
                "風火輪" : (: ask_skill1 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.lun" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 150);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",4);
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

        if( query("combat_exp", ob)<120000 )
        {
                command("say 你的江湖經驗不夠，還是先向其他師父學習吧。");
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
        command("nod");
        command("say 我便收下你，希望日後努力上進，能有所作為。");
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

        if( query("can_perform/fumo-zhang/lun", me) )
                return "這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與在下素不相識，不知此話從何説起？";

        if (me->query_skill("fumo-zhang", 1) < 1)
                return "你連伏魔杖法都沒學，何談絕招可言？";

        if( query("family/gongji", me)<350 )
                return "你在我們丐幫內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<30000 )
                return "你的俠義正事還做得不夠，這招我暫時還不能傳你。";

        if (me->query_skill("fumo-zhang", 1) < 120)
                return "你的二十四路伏魔杖火候不夠，下去練高點再來吧。";

        if (me->query_skill("force") < 150)
                return "你現在的內功修為不足，還是練高點再來吧。";

        message_sort(HIY "\n$n" HIY "微笑着對$N" HIY "點了點頭，驀"
                     "地起身而立，陡然一聲暴喝，手中竹棒揮轉如輪，"
                     "殘影化出無數個大圈，瞬間已將$N" HIY "團團裹罩"
                     "其中，便似那風火輪一般，氣勢如虹，招式精奇，"
                     "令人歎為觀止。\n\n" NOR, me, this_object());

        command("haha");
        command("say 你自己去領悟吧。");
        tell_object(me, HIC "你學會了「風火輪」。\n" NOR);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("fumo-zhang"))
                me->improve_skill("fumo-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/fumo-zhang/lun", 1, me);
        addn("family/gongji", -350, me);

        return 1;
}
