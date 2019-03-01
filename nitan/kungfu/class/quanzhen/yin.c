// This program is a part of NT MudLIB

#include <ansi.h>;
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();

void create()
{
        set_name("尹志平", ({"yin zhiping", "yin"}));
        set("gender", "男性");
        set("class", "taoist");
        set("nickname", HIM"清和真人"NOR);
        set("age", 24);
        set("long",
                "他是丘處機的得意大弟子尹志平，他粗眉大眼，長的有些英雄氣\n"
                "概，在全真教第三代弟子中算得上年輕有為。身材不高，眉宇間\n"
                "似乎有一股憂鬱之色。長的倒是長眉俊目，容貌秀雅，面白無須，\n"
                "可惜朱雀和玄武稍有不和。\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 28);
        set("int", 25);
        set("con", 25);
        set("dex", 25);

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

        set("qi", 1500);
        set("max_qi", 1500);
        set("jing", 800);
        set("max_jing", 800);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 60);

        set("combat_exp", 220000);

        set_skill("force", 110);
        set_skill("quanzhen-xinfa", 110);
        set_skill("sword", 100);
        set_skill("quanzhen-jian", 100);
        set_skill("dodge", 90);
        set_skill("jinyan-gong", 90);
        set_skill("parry", 110);
        set_skill("finger",100);
        set_skill("zhongnan-zhi", 100);
        set_skill("strike", 100);
        set_skill("chongyang-shenzhang", 100);
        set_skill("literate",60);
        set_skill("taoism",60);
        set_skill("array",80);
        set_skill("beidou-zhenfa", 80);
        map_skill("force", "quanzhen-xinfa");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("finger", "zhongnan-zhi");
        map_skill("strike", "chongyang-shenzhang");
        prepare_skill("finger", "zhongnan-zhi");
        prepare_skill("strike", "chongyang-shenzhang");

        create_family("全真教", 3, "弟子");

        set("inquiry", ([
                "全真教"   :  "我全真教是天下道家玄門正宗。\n",
                "劍指南山" : (: ask_skill1 :),
        ]) );

        set("master_ob",3);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/greyrobe")->wear();

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("say 好吧，我就收下你這個徒弟了。");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/zhongnan-zhi/zhi", me) )
                return "這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧道素不相識，不知此話從何說起？";

        if (me->query_skill("zhongnan-zhi", 1) < 1)
                return "你連終南指法都沒學，何談絕招可言？";

        if( query("family/gongji", me)<50 )
                return "你在我全真教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<3000 )
                return "你的俠義正事還做得不夠，這招我暫時還不能傳你。";

        if (me->query_skill("zhongnan-zhi", 1) < 60)
                return "你的終南指法不夠嫻熟，練高點再來吧。";

        if (me->query_skill("force") < 80)
                return "你的內功修為不夠，修煉高後再來找我吧。";

        message_sort(HIY "\n$n" HIY "對$N" HIY "點了點頭，當下更不答"
                     "話，微微探出一指，斜刺而出。但見其指尖晃動不已"
                     "，招式連貫，頗為精奇。\n\n" NOR, me,
                     this_object());

        command("nod");
        command("say 這招很簡單，稍加練習便成。");
        tell_object(me, HIC "你學會了「劍指南山」。\n" NOR);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("zhongnan-zhi"))
                me->improve_skill("zhongnan-zhi", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhongnan-zhi/zhi", 1, me);
        addn("family/gongji", -50, me);

        return 1;
}
