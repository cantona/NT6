#include <ansi.h>
#include "honghua.h"

#define HUILONGBI    "/clone/lonely/huilongbi"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

mixed ask_bi();
mixed ask_skill1();

void create()
{
        object ob;
        set_name("趙半山", ({"zhao banshan", "zhao", "banshan"}));
        set("title", "紅花會三當家");
        set("nickname", HIY "千臂如來" NOR );
        set("gender", "男性");
        set("age", 48);
        set("long", "只見他一張胖胖的臉，笑起來給人一副很慈\n"
                    "祥的感覺。他原是温州王氏太極門掌門大弟\n"
                    "子。豪邁豁達，行俠江湖，一手暗器功夫和\n"
                    "太極劍少有能匹敵。屠龍幫風流雲散之後，\n"
                    "投入紅花會。很得被紅花會老當家於萬亭賞\n"
                    "識。\n");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 21);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 4500);
        set("max_qi", 4500);
        set("jing", 3000);
        set("max_jing", 3000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 150);
        set("combat_exp", 3000000);
        set("score", 10000);

        set_skill("force", 220);
        set_skill("honghua-xinfa", 220);
        set_skill("tianchi-neigong", 220);
        set_skill("unarmed", 220);
        set_skill("dodge", 220);
        set_skill("yanzi-chuanyun", 220);
        set_skill("taiji-jian", 220);
        set_skill("taiji-quan", 220);
        set_skill("parry", 220);
        set_skill("sword", 220);
        set_skill("throwing", 240);
        set_skill("huilong-bifa", 240);
        set_skill("martial-cognize", 200);
        set_skill("literate", 200);

        set("no_teach", ([
                "taiji-jian" : "嗯……你還是學點其它的吧。",
                "taiji-quan" : "嗯……你還是學點其它的吧。",
        ]));

        map_skill("force"   , "tianchi-neigong");
        map_skill("unarmed" , "taiji-quan");
        map_skill("dodge"   , "yanzi-chuanyun");
        map_skill("parry"   , "taiji-jian");
        map_skill("sword"   , "taiji-jian");
        map_skill("throwing", "huilong-bifa");

        create_family("紅花會", 4, "當家");

        set("inquiry", ([
                "回龍璧" : (: ask_bi :),
                "掌藏龍" : (: ask_skill1 :),
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chan" :),
                (: perform_action, "throwing.cang" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );
        setup();

        if (clonep())
        {
                ob = find_object(HUILONGBI);
                if (! ob) ob = load_object(HUILONGBI);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        set_temp("handing", ob);
                } else
                {
                        set_temp("handing", carry_object("/d/beijing/npc/obj/jinbiao"));
                }
        }
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();
    
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("shen", me)<15000 )
        {
                command("say 你俠義之事做得太少，需要多多注意。");
                return;
        }

        if( query("combat_exp", me)<200000 )
        {
                command("say 你的江湖經驗太淺，還是先跟着其它幾位當家練練吧。");
                return;
        }

        if ((int)me->query_skill("honghua-xinfa", 1) < 80)
        {
                command("say 你下去把本門的心法練好了再來找我。");
                return;
        }

        command("smile");
        command("say 念在你如此有心，我便收下你好了。");
        command("recruit "+query("id", me));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/huilong-bifa/cang", me) )
                return "這招我不是早傳授給你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素無瓜葛，何出此言？";

        if (me->query_skill("huilong-bifa", 1) < 1)
                return "你連回龍璧法都沒學，還談什麼絕招可言？";

            if( query("family/gongji", me)<600 )
                return "你在會中所作的貢獻還不夠，這招我不忙傳你。";

        if( query("shen", me)<30000 )
                return "你俠義正事做得不夠，這招我不能傳你。";

        if (me->query_skill("force") < 160)
                return "你的內功火候不足，學不成這一招。";

        if (me->query_skill("huilong-bifa", 1) < 120)
                return "你的回龍璧法還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "哈哈一笑，將$N" HIY "招至跟前，輕"
                       "聲在耳旁祕密説了些什麼。隨後又伸出右\n手，十指"
                       "箕張，一伸一縮，看樣子是一種很特別的暗器法門。\n"
                       NOR, me, this_object());

        command("haha");
        command("say 聽清楚了嗎，自己下去練吧。");
        tell_object(me, HIC "你學會了「掌藏龍」。\n" NOR);

        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("huilong-bifa"))
                me->improve_skill("huilong-bifa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/huilong-bifa/cang", 1, me);
          addn("family/gongji", -600, me);

        return 1;
}

mixed ask_bi()
{
        object me;
        object ob;

        me = this_player();

        if( query("family/family_name", me) != "紅花會" )
                return "嘿，你是哪裏來的？我可不認識你。";

        if( query("family/master_id", me) != "chenjialuo" && 
           query("family/master_id", me) != "wuchendaozhang" && 
           query("family/master_id", me) != "zhaobanshan" )
                return "這個…你師父"+query("family/master_name", me)+CYN
                       "説了，不能太寵着你，過些日子吧。";

        if (me->query_skill("huilong-bifa", 1) < 150)
                return "等你回龍璧法練成後再來找我，快下去練練。";

        if( query("shen", me)<30000 )
                return "哎呀呀，我這倒不是吝嗇，可是你的德行也……";

        if (present("huilong bi", me))
                return "我的回龍璧不正是你拿着在用嗎，為何還反倒問起我來了？";

        ob = present("huilong bi", this_object());

        if (! objectp(ob))
                return "你來晚了，回龍璧現在並不在我手中。";

        message_vision("$N拿出" HIC "回龍璧" NOR "(Huilong bi)給$n。\n",
                       this_object(), me);
        ob->move(me, 1);
        set_temp("handing", carry_object("/d/beijing/npc/obj/jinbiao"));

        return "既然這樣，我這支回龍璧你就暫時拿去用吧。";
}
