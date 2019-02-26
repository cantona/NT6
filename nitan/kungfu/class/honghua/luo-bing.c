#include <ansi.h>
#include "honghua.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();

void create()
{
        set_name("駱冰", ({ "luo bing", "luo", "bing"}));
        set("title", "紅花會十一當家");
        set("nickname", HIC "鴛鴦刀" NOR);
        set("long", "這是一個秀美的少婦。一手短刀，一手握着一\n"
                    "柄長刀。\n");
        set("gender", "女性");
        set("age", 34);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 21);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 1800);
        set("max_qi", 1800);
        set("jing", 1200);
        set("max_jing", 1200);
        set("neili", 2500);
        set("max_neili", 2500);
        set("jiali", 80);
        set("combat_exp", 500000);
        set("score", 1000);

        set_skill("force", 120);
        set_skill("honghua-xinfa", 120);
        set_skill("unarmed", 120);
        set_skill("changquan", 120);
        set_skill("dodge", 140);
        set_skill("yanzi-chuanyun", 140);
        set_skill("blade", 140);
        set_skill("hanwang-qingdao", 140);
        set_skill("parry", 120);
        set_skill("martial-cognize", 100);
        set_skill("literate", 140);

        map_skill("force"  , "honghua-xinfa");
        map_skill("blade"  , "hanwang-qingdao");
        map_skill("unarmed" , "changquan");
        map_skill("dodge"  , "yanzi-chuanyun");
        map_skill("parry"  , "hanwang-qingdao");

        prepare_skill("unarmed", "changquan");

        create_family("紅花會", 4, "當家");

        set("inquiry", ([
                "刀影重重"  : (: ask_skill1 :),
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "blade.ying" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );
        setup();

        carry_object(CLOTH_DIR"female-cloth")->wear();
        carry_object(CLOTH_DIR"female-shoe")->wear();
        carry_object(WEAPON_DIR"gangdao")->wield();
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("shen", me)<-1000 )
        {
                command("say 我紅花會不收不義之人，你還是走吧。");
                return;
        }

        command("xixi");
        command("say 既然這樣，我就收下你好了。");
        command("recruit "+query("id", me));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/hanwang-qingdao/ying", me) )
                return "你不是已經會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素無瓜葛，何出此言？";

        if (me->query_skill("hanwang-qingdao", 1) < 1)
                return "你連韓王青刀都沒學，何談此言？";

            if( query("family/gongji", me)<80 )
                return "你在會中所作的貢獻還不夠，這招我不忙傳你。";

        if( query("shen", me)<5000 )
                return "你俠義正事做得不夠，這招我不能傳你。";

        if (me->query_skill("force") < 120)
                return "你的內功火候不足，學不了這一招！";

        if (me->query_skill("hanwang-qingdao", 1) < 80)
                return "你的韓王青刀還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "點了點頭，將$N" HIY "招至"
                       "身邊，在耳旁低聲細説良久，$N" HIY "聽"
                       "後會心\n的一笑，看來大有所悟。\n" NOR,
                       me, this_object());

        command("nod");
        command("say 剛才我所説的便是韓王青刀的精要，你可記清了？");
        tell_object(me, HIC "你學會了「刀影重重」。\n" NOR);

        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("hanwang-qingdao"))
                me->improve_skill("hanwang-qingdao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/hanwang-qingdao/ying", 1, me);
          addn("family/gongji", -80, me);

        return 1;
}
