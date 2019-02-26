// This program is a part of NT MudLIB
// tan.c 譚處端

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();
string ask_me();

void create()
{
        set_name("譚處端", ({"tan chuduan", "tan"}));
        set("gender", "男性");
        set("age", 40);
        set("class", "taoist");
        set("nickname",HIY"長真子"NOR);
        set("long",
                "他就是全真次徒譚處端譚真人，他身材魁梧，濃眉大眼，嗓音\n"
                "洪亮，拜重陽真人為師前本是鐵匠出身。\n");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 34);
        set("int", 28);
        set("con", 28);
        set("dex", 28);

        set("title","全真七子之二");
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

        set("qi", 4000);
        set("max_qi", 4000);
        set("jing", 2000);
        set("max_jing", 2000);
        set("neili", 4200);
        set("max_neili", 4200);
        set("jiali", 100);
        set("level", 20);
        set("combat_exp", 1200000);

        set_skill("force", 150);
        set_skill("quanzhen-xinfa", 160);
        set_skill("sword", 150);
        set_skill("quanzhen-jian",160);
        set_skill("dodge", 140);
        set_skill("jinyan-gong", 140);
        set_skill("parry", 150);
        set_skill("strike", 150);
        set_skill("chongyang-shenzhang", 150);
        set_skill("haotian-zhang", 150);
        set_skill("literate",80);
        set_skill("finger",140);
        set_skill("zhongnan-zhi", 140);
        set_skill("taoism",100);
        set_skill("cuff",150);
        set_skill("chunyang-quan",150);
        set_skill("array",150);
        set_skill("beidou-zhenfa", 150);

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
                "全真教"   :  "我全真教是天下道家玄門正宗。\n",
                "三花聚頂" : (: ask_skill1 :),
                "祕籍" : (: ask_me :),
        ]) );
        set("book_count", 1);
        set("master_ob",3);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/greenrobe")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("quanzhen-xinfa",1) < 80 )
        {
                command("say 你的本門內功心法火候不足,難以領略更高深的武功。");
                return;
        }
        if( query("shen", ob)<8000 )
        {
                command("say 我看你還是多做一些俠義之事吧。\n");
                return;
        }
        command("say 好吧，我就收下你這個徒弟了。");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/haotian-zhang/ju", me) )
                return "這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧道素不相識，不知此話從何説起？";

        if (me->query_skill("haotian-zhang", 1) < 1)
                return "你連昊天掌都沒學，何談絕招可言？";

        if( query("family/gongji", me)<250 )
                return "你在我全真教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<30000 )
                return "你的俠義正事還做得不夠，這招我暫時還不能傳你。";

        if (me->query_skill("haotian-zhang", 1) < 120)
                return "你的昊天掌不夠嫻熟，練高點再來吧。";

        if (me->query_skill("force") < 180)
                return "你的內功修為不夠，修煉高後再來找我吧。";

        message_sort(HIY "\n$n" HIY "眉頭一皺，上下打量了$N" HIY "一番"
                     "，當下更不答話，衣袖輕輕一抖，猛然大喝一聲，頓時"
                     "雙掌紛飛，掌勁朝四面八方雲貫而出，氣勢恢弘之極。"
                     "\n\n" NOR, me, this_object());

        command("say 看懂了麼？");
        tell_object(me, HIC "你學會了「三花聚頂」。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("haotian-zhang"))
                me->improve_skill("haotian-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/haotian-zhang/ju", 1, me);
        addn("family/gongji", -250, me);

        return 1;
}

string ask_me()
{
        mapping fam;
        object ob, *obs,ob2 ;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "全真教" )
                return RANK_D->query_respect(this_player()) +
                "與本派素無來往，不知此話從何談起？";

        if (query("book_count") < 1)
                return "你來晚了，本派的內功心法不在此處。";
           obs = filter_array(children("/d/quanzhen/obj/qz_force"), (: clonep :));
                  if (sizeof(obs) > 20)
                return "你來晚了，本派的內功心法不在此處。";

        ob=new("/d/quanzhen/obj/qz_force");
        ob->move(this_player());
        addn("book_count", -1);
        command("rumor"+query("name", this_player())+"弄到了一冊玄門內功心法。");
        return "好吧，這本「玄門內功心法」你拿回去好好鑽研。";
}
int accept_ask(object me, string topic) 
{ 
        switch (topic) 
        { 
        case "浩然一擊" : 
               return MASTER_D->teach_pfm(me, this_object(), 
                             ([ "perform" : "can_perform/haotian-zhang/ji", 
                                "name"    : "浩然一擊",
                                "sk1"     : "haotian-zhang", 
                                "lv1"     : 120, 
                                "sk2"     : "strike", 
                                "lv2"     : 120, 
                                "gongxian": 600, ])); 
               break; 
         default: 
               return 0; 
         } 
} 

