// This program is a part of NT MudLIB

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();

void create()
{
        set_name("劉處玄", ({"liu chuxuan", "liu"}));
        set("gender", "男性");
        set("age", 38);
        set("class", "taoist");
        set("nickname",WHT"長生子"NOR);
        set("long",
                "他就是全真三徒劉處玄劉真人，他身材瘦小，但顧盼間自有一\n"
                "種威嚴氣概。\n");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 30);
        set("int", 30);
        set("con", 28);
        set("dex", 30);

        set("title","全真七子之三");

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
        }));

        set("qi", 4400);
        set("max_qi", 4400);
        set("jing", 2200);
        set("max_jing", 2200);
        set("neili", 4600);
        set("max_neili", 4600);
        set("jiali", 100);
        set("level", 15);
        set("combat_exp", 850000);

        set_skill("force", 160);
        set_skill("quanzhen-xinfa", 160);
        set_skill("sword", 160);
        set_skill("quanzhen-jian",160);
        set_skill("dodge", 140);
        set_skill("jinyan-gong", 140);
        set_skill("parry", 150);
        set_skill("finger",150);
        set_skill("zhongnan-zhi", 150);
        set_skill("literate", 100);
        set_skill("strike", 150);
        set_skill("chongyang-shenzhang", 150);
        set_skill("haotian-zhang", 150);
        set_skill("finger",150);
        set_skill("array",120);
        set_skill("beidou-zhenfa", 120);
        set_skill("taoism",120);

        map_skill("force", "quanzhen-xinfa");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("finger", "zhongnan-zhi");
        map_skill("strike", "haotian-zhang");
        prepare_skill("finger", "zhongnan-zhi");
        prepare_skill("strike","haotian-zhang");

        create_family("全真教", 2, "弟子");

        set("book_count",1);
        set("inquiry", ([
                "連環掌"     : (: ask_skill1 :),
                "重陽連環掌" : (: ask_skill1 :),
        ]) );

        set("master_ob",3);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/greenrobe")->wear();

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("quanzhen-xinfa",1) < 70 )
        {
                command("say 你的本門內功心法火候不足,難以領略更高深的武功。");
                return;
        }
        if( query("shen", ob)<6000 )
        {
                command("say 多做一些行俠仗義的事情再説吧！。\n");
                return;
        }
        command("say 好吧，我就收下你這個徒弟了。");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/chongyang-shenzhang/lian", me) )
                return "這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧道素不相識，不知此話從何説起？";

        if (me->query_skill("chongyang-shenzhang", 1) < 1)
                return "你連重陽神掌都沒學，何談絕招可言？";

        if( query("family/gongji", me)<100 )
                return "你在我全真教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<10000 )
                return "你的俠義正事還做得不夠，這招我暫時還不能傳你。";

        if (me->query_skill("chongyang-shenzhang", 1) < 100)
                return "你的重陽神掌不夠嫻熟，練高點再來吧。";

        if (me->query_skill("force") < 120)
                return "你的內功修為不夠，修煉高後再來找我吧。";

        message_sort(HIY "\n$n" HIY "眉頭一皺，上下打量了$N" HIY "一番"
                     "，當下更不答話，衣袖輕輕一抖，猛然大喝一聲，頓時"
                     "雙掌紛飛，掌勁朝四面八方雲貫而出，氣勢恢弘之極。"
                     "\n\n" NOR, me, this_object());

        command("say 看懂了麼？");
        tell_object(me, HIC "你學會了「重陽連環掌」。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("chongyang-shenzhang"))
                me->improve_skill("chongyang-shenzhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/chongyang-shenzhang/lian", 1, me);
        addn("family/gongji", -100, me);

        return 1;
}

