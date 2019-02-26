#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

#include "fight.h"

mixed ask_skill1();
mixed ask_skill2();

void create()                                                                   
{
        set_name("黎生", ({ "li sheng", "li", "sheng" }));
        set("gender", "男性");
        set("long", "這是位生性剛直，嫉惡如仇的丐幫八袋弟子。\n");
        set("title", "丐幫八袋弟子");
        set("nickname", HIW "行俠仗義" NOR);
        set("age", 42);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 32);
        set("int", 32);
        set("con", 32);
        set("dex", 32);
        set("max_qi", 2400);
        set("max_jing", 1600);
        set("neili", 2200);
        set("max_neili", 2200);
        set("jiali", 180);
        set("combat_exp", 1200000);
        set("shen_type", 1);

        set_skill("force", 160);
        set_skill("huntian-qigong", 140);
        set_skill("jiaohua-neigong", 160);
        set_skill("dodge", 160);
        set_skill("feiyan-zoubi", 160);
        set_skill("staff", 140);
        set_skill("jiaohua-bangfa", 140);
        set_skill("unarmed", 140);
           set_skill("cuff", 140);
        set_skill("changquan", 140);
        set_skill("jueming-tui", 140);
        set_skill("strike", 160);
        set_skill("shenlong-baiwei", 160);
        set_skill("tongchui-zhang", 160);
        set_skill("parry", 160);
        set_skill("begging", 200);
        set_skill("checking", 200);
        set_skill("literate", 140);
        set_skill("martial-cognize", 160);

        map_skill("force", "huntian-qigong");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("staff", "jiaohua-bangfa");
        map_skill("strike", "shenlong-baiwei");
        map_skill("unarmed", "jueming-tui");
        map_skill("parry", "shenlong-baiwei");

        prepare_skill("strike", "shenlong-baiwei");

        set("no_teach/shenlong-baiwei", "這招掌法乃是蒙幫主他老"
                                        "人家所賜，不能輕易傳授。");
        set("no_teach/huntian-qigong",  "這內功便是我也未修煉純"
                                        "熟，我還是教你點別的吧。");

        create_family("丐幫", 19, "弟子");

        set("coagents", ({
                ([ "startroom" : "/d/gaibang/undertre",
                   "id"        : "liang zhanglao" ]),
                ([ "startroom" : "/d/gaibang/undertre",
                   "id"        : "jian zhanglao" ]),
        }));

        set("inquiry", ([
                "五丁開山" : (: ask_skill1 :),
                "絕命一踢" : (: ask_skill2 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",3);
        setup();
        carry_object("/d/gaibang/npc/obj/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<0 )
        {
                command("say 你身為丐幫弟子，竟然不做好事？");
                return;
        }
        command("nod");
        command("say 我便收你為徒，日後可得行俠仗義，莫損我丐幫名聲。");
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

        if( query("can_perform/tongchui-zhang/kai", me) )
                return "這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與在下素不相識，不知此話從何説起？";

        if (me->query_skill("tongchui-zhang", 1) < 1)
                return "你連銅錘掌法都沒學，何談絕招可言？";

        if( query("family/gongji", me)<100 )
                return "你在我們丐幫內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<1000 )
                return "你的俠義正事還做得不夠，這招我暫時還不能傳你。";

        if (me->query_skill("tongchui-zhang", 1) < 80)
                return "你的銅錘掌法火候還不夠，還是下去練高點再來吧。";

        if (me->query_skill("force") < 90)
                return "你現在的內功修為不足，還是練高點再來吧。";

        message_sort(HIY "\n$n" HIY "微微一笑，從懷中輕輕取出了一本"
                     "小冊子，指着其中的一段對$N" HIY "細説良久，$N"
                     HIY "一邊聽一邊點頭。\n\n" NOR, me,
                     this_object()); 

        command("nod");
        command("say 招式很簡單，你自己下去練吧。");
        tell_object(me, HIC "你學會了「五丁開山」。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("tongchui-zhang"))
                me->improve_skill("tongchui-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tongchui-zhang/kai", 1, me);
        addn("family/gongji", -100, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/jueming-tui/jue", me) )
                return "這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與在下素不相識，不知此話從何説起？";

        if (me->query_skill("jueming-tui", 1) < 1)
                return "你連絕命腿法都沒學，何談絕招可言？";

        if( query("family/gongji", me)<150 )
                return "你在我們丐幫內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<3000 )
                return "你的俠義正事還做得不夠，這招我暫時還不能傳你。";

        if (me->query_skill("jueming-tui", 1) < 80)
                return "你的絕命腿法火候還不夠，還是下去練高點再來吧。";

        if (me->query_skill("force") < 100)
                return "你現在的內功修為不足，還是練高點再來吧。";

        message_sort(HIY "\n$n" HIY "哈哈一笑，伸手將$N" HIY "招到了"
                     "面前，在$N" HIY "耳邊輕聲嘀咕了些話。$N" HIY "聽"
                     "了半天，突然間不由會心的一笑，看來大有所悟。\n\n"
                     NOR, me, this_object());

        command("nod");
        command("say 這招的要詣就是出招連貫，以奇制勝。");
        tell_object(me, HIC "你學會了「絕命一踢」。\n" NOR);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("jueming-tui"))
                me->improve_skill("jueming-tui", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jueming-tui/jue", 1, me);
        addn("family/gongji", -150, me);

        return 1;
}
