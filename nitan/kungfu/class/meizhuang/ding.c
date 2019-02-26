#include <ansi.h>
#include "meizhuang.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

mixed ask_skill1();

void create()
{
        set_name("丁堅", ({"ding jian","ding",}));
        set("long",
                "他就是隱居江湖數年的一字電劍丁堅，現在在梅莊當僕人。\n"
        );
        set("gender", "男性");
        set("nickname", HIY "一字電劍" NOR);
        set("title", "梅莊僕從");
        set("attitude", "friendly");

        set("age", 30);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("max_qi", 3000);
        set("max_jing", 2700);
        set("neili", 3500);
        set("max_neili", 3500);
        set("jiali", 50);
        set("combat_exp", 500000);

        set_skill("force", 120);
        set_skill("wuzheng-xinfa", 120);
        set_skill("sword", 140);
        set_skill("jidian-jian", 140);
        set_skill("dodge", 140);
        set_skill("feiyan-zoubi", 140);
        set_skill("parry", 120);
        set_skill("strike", 120);
        set_skill("qingmang-zhang", 120);
        set_skill("literate", 100);
        set_skill("martial-cognize", 120);

        map_skill("force", "wuzheng-xinfa");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("parry", "jidian-jian");
        map_skill("sword", "jidian-jian");
        map_skill("strike", "qingmang-zhang");

        prepare_skill("strike", "qingmang-zhang");

        set("coagents", ({
                ([ "startroom" : "/d/meizhuang/houting",
                   "id"        : "hei baizi" ]),
        }));

        set("guarder", ([
                "refuse_other": CYN "$N" CYN "對$n" CYN "皺眉道："
                                "給我站住，孤山梅莊豈是隨便走動地"
                                "方？" NOR,
                "refuse_carry": CYN "$N" CYN "對$n" CYN "喝道：你"
                                "背上背的是什麼人？" NOR,
        ]));

        create_family("梅莊", 2, "僕從");

        set("inquiry", ([
                "絕招"        : "你要問什麼絕招？",
                "絕技"        : "你要問什麼絕技？",
                "電光四射"    : (: ask_skill1 :),
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.dian" :),
                (: exert_function, "recover" :),
        }) );

        set("master_ob",3);
        setup();
        carry_object("/d/city/npc/obj/cloth")->wear();
        carry_object("/d/city/npc/obj/changjian")->wield();
        carry_object("/d/meizhuang/obj/yaoshi");
}

void attempt_apprentice(object me)
{
        string purename, name, new_name;

        if (! permit_recruit(me))
                return;

        if( query("family/family_name", me) && 
             query("family/family_name", me) == "日月神教" && 
             query("family/master_name", me) == "東方不敗" )
        {
                command("ah");
                command("say 原來是東方教主的弟子，興會，興會！");
                command("say 這件事非同小可，我做不了主，你還是去找幾位莊主吧。");
                set("move_party/日月神教—梅莊", 1, me);
                return;
        }

        if( query("shen", me)>1000 )
        {
                command("heng");
                command("say 我們孤山梅莊向來不問江湖事，也不結交你這樣的俠義之士。");
                return;
        }

        if( query("shen", me)<-1000 )
        {
                command("heng");
                command("say 我們孤山梅莊向來不問江湖事，更不會結交名聲不好之人。");
                return;
        }

        command("say 好吧，既然你有心練武，我就收下你。");
        command("recruit "+query("id", me));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/jidian-jian/dian", me) )
                return "能教的我已經都教完了。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素無瓜葛，何出此言？";

        if (me->query_skill("jidian-jian", 1) < 1)
                return "你連疾電劍法都沒學，何談此言？";

        if( query("family/gongji", me)<50 )
                return "你對本莊所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("jidian-jian", 1) < 100)
                return "你的疾電劍法還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("force") < 150)
                return "你的內功火候尚不精純，是學不會這招的。";

        message_vision(HIY "$n" HIY "點了點頭，説道：這疾電劍法的電光"
                       "四射其實是懾人聲勢使其無所施其\n技，我這裏給你"
                       "演示一遍，你可看好了。$n" HIY "説完手中長劍一"
                       "抖，將這套劍\n法施展出來，霎時之間，滿室都是電"
                       "光，耀人眼目。$N" HIY "看後雙目一亮，頓時\n大"
                       "有所悟。\n" NOR, me, this_object());
        command("nod");
        command("say 這招其實很簡單，稍微練練便可以施展了。");
        tell_object(me, HIC "你學會了「電光四射」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("jidian-jian"))
                me->improve_skill("jidian-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jidian-jian/dian", 1, me);
        addn("family/gongji", -50, me);

        return 1;
}
