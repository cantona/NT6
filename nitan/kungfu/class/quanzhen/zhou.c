// This program is a part of NT MudLIB
// zhou.c 周伯通

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;

#define ZHENJING    "/clone/book/jiuyin1"

mixed ask_skill1();
mixed ask_skill2();

void create()
{
        object ob;
        set_name("周伯通", ({"zhou botong", "zhou"}));
        set("gender", "男性");
        set("age", 62);
        set("class", "taoist");
        set("nickname",HIY "老頑童" NOR);
        set("long", "他看上去須眉皆白，一副得道模樣，然而眼神卻透露出一股狡黠。\n");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 31);
        set("int", 36);
        set("con", 32);
        set("dex", 29);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
        }));

        set("qi", 6200);
        set("max_qi", 6200);
        set("jing", 3100);
        set("max_jing", 3100);
        set("neili", 6500);
        set("max_neili", 6500);
        set("jiali", 50);
        set("level", 60);
        set("combat_exp", 2800000);

        set_skill("force", 280);
        set_skill("quanzhen-xinfa", 280);
        set_skill("xiantian-gong", 280);
        set_skill("sword", 250);
        set_skill("quanzhen-jian",250);
        set_skill("dodge", 260);
        set_skill("jinyan-gong", 260);
        set_skill("parry", 270);
        set_skill("unarmed", 270);
        set_skill("kongming-quan", 270);
        set_skill("strike", 250);
        set_skill("chongyang-shenzhang", 250);
        set_skill("haotian-zhang", 250);
        set_skill("literate", 120);
        set_skill("finger", 250);
        set_skill("taoism", 220);
        set_skill("finger", 260);
        set_skill("zhongnan-zhi", 270);
        set_skill("zuoyou-hubo", 400);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "kongming-quan");
        map_skill("finger","zhongnan-zhi");
        map_skill("strike", "haotian-zhang");
        map_skill("unarmed", "kongming-quan");
        // prepare_skill("cuff", "kongming-quan");

        create_family("全真教", 1, "掌教");
        set("title", "全真教第一代弟子");

        set("book_count",1);
        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄門正宗。\n",
                "九陰真經" : "嘿嘿嘿嘿...",
                "段皇爺" : "段... 段皇爺？人家是皇爺，我不認識！",
                "瑛姑"   : "你，你說啥？",
                "劉瑛"   : "嗯...嗯...嗯？",
                "空明若玄" : (: ask_skill1 :),
                "空空如也" : (: ask_skill2 :),
        ]));

        set("master_ob",4);
        setup();

        if (clonep())
        {
                ob = find_object(ZHENJING);
                if (! ob) ob = load_object(ZHENJING);

                if (! environment(ob) && random(30) == 1)
                        ob->move(this_object());
        }
        carry_object("/d/quanzhen/npc/obj/greenrobe")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("combat_exp", ob)<400000 )
        {
                command("say 你經驗這麼差，還是去找我那幾個師侄教你吧。");
                return;
        }

        if( query("shen", ob)<50000 )
        {
                command("say 你這人品行不好，跟你一起肯定做不了什麼好事。");
                return;
        }

        command("smile");
        command("say 反正最近也沒啥事幹，就收下你玩玩吧。");
        command("recruit "+query("id", ob));
}

/*
int recognize_apprentice(object ob, string skill)
{
        if( !query("can_learn/zhou", ob) )
        {
                message_vision("$N眨眨眼睛，看著$n，嘻嘻笑個不停。\n",
                               this_object(), ob);
                return -1;
        }

        if (skill != "kongming-quan" &&
            skill != "zuoyou-hubo")
        {
                command("say 我...這裡可沒有什麼好教你的！");
                return -1;
        }

        return 1;
}
*/

int accept_fight(object ob)
{
        if( query("combat_exp", ob)<500000 )
        {
                message_vision("$N嘻嘻一笑，對$n道：“你還是"
                               "把功夫練好了再說吧！”\n",
                               this_object(), ob);
                return -1;
        }

        if (is_fighting())
        {
                message_vision("$N對$n叫道：“你先別急，我打完這"
                               "架就來領教你的！”\n",
                               this_object(), ob);
                return -1;
        }

        if (query("qi") < 4000 ||
            query("jing") < 2000 ||
            query("neili") < 4000)
        {
                message_vision("$N搖搖頭對$n道：“我現在"
                               "太累了，等會兒再說吧！”\n",
                               this_object(), ob);
                return -1;
        }

        if( query("can_learn/zhou", ob) )
        {
                message_vision("$N對$n道：“好，那咱們就玩玩！”\n",
                               this_object(), ob);
                return 1;
        }

        message_vision("$N大喜道，好...好，我正手癢癢，咱們來比劃比劃！\n",
                       this_object(), ob);

        competition_with(ob);
        return -1;
}

void win()
{
        object ob;
        if (! objectp(ob = query_competitor()))
                return;

        message_vision("$N看了看$n，嘿嘿笑道：“你的水平還算"
                       "是馬馬虎虎，要好好練功，好好練功。”\n",
                       this_object(), ob);
        ::win();
}

void lost()
{
        object ob;
        if (! objectp(ob = query_competitor()))
                return;

        message_vision("$N哎呀一聲，抹了抹頭上的汗，喜道：“這位" +
                       RANK_D->query_respect(ob) + "，你的武功真厲害，\n"
                       "這樣吧，我拜你為師好了，你教我點功夫，我這裡有一套"
                       "空明拳法和左右互博\n的小伎倆，你有興趣也可以學學，怎麼樣。”\n",
                       this_object(), ob);
        set("can_learn/zhou", 1, ob);
        ::lost();
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/kongming-quan/ruo", me) )
                return "還問這個幹嘛？不如來陪我玩玩。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是誰，我怎麼不認識你？";

        if (me->query_skill("kongming-quan", 1) < 1)
                return "嘿嘿，你連我的空明拳都沒學，又怎麼學絕招？";

        if( query("family/gongji", me)<200 )
                return "你投入我全真教，卻不努力做事，我為什麼要教你？";

        if( query("shen", me)<50000 )
                return "你這人心地還不夠好，暫時我還不能教你。";

        if (me->query_skill("kongming-quan", 1) < 100)
                return "你的空明拳還練得不夠好，下次再說吧。";

        if( query("max_neili", me)<1000 )
                return "你的內力差成這樣，真不知道你是怎麼練功的。";

        message_sort(HIY "\n$n" HIY "抓了抓頭，滿不情願的嘀咕了兩句，這"
                     "才說道：“小子，我把口訣說給你聽，然後你就自己下去"
                     "練，別再來煩我了。”說完便一把將$N" HIY "楸到身邊"
                     "，在$N" HIY "耳旁唧唧咕咕說了半天。\n\n" NOR, me,
                     this_object());

        command("bite");
        command("say 好了，好了，你快走吧。");
        tell_object(me, HIC "你學會了「空明若玄」。\n" NOR);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("kongming-quan"))
                me->improve_skill("kongming-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/kongming-quan/ruo", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/kongming-quan/kong", me) )
                return "快滾，快滾。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是誰，我怎麼不認識你？";

        if (me->query_skill("kongming-quan", 1) < 1)
                return "嘿嘿，你連我的空明拳都沒學，又怎麼學絕招？";

        if( query("family/gongji", me)<500 )
                return "你投入我全真教，卻不努力做事，我為什麼要教你？";

        if( query("shen", me)<60000 )
                return "你這人心地還不夠好，暫時我還不能教你。";

        if (me->query_skill("kongming-quan", 1) < 150)
                return "你的空明拳還練得不夠好，下次再說吧。";

        if( query("max_neili", me)<2000 )
                return "你的內力差成這樣，真不知道你是怎麼練功的。";

        message_sort(HIY "\n$n" HIY "雙目一瞪，對$N" HIY "說道：“你怎麼"
                     "這麼煩，沒看見我正在玩嗎？”接著$n" HIY "搖了搖頭，"
                     "又道：“真是後悔當初收了你，看好了！”說話間右手一"
                     "陡，輕飄飄揮出一拳，拳勁虛實難測，周圍登時被激得塵"
                     "土飛揚。\n\n" NOR, me, this_object());

        command("angry");
        command("say 快走，快走，以後別再來煩我了。");
        tell_object(me, HIC "你學會了「空空如也」。\n" NOR);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("kongming-quan"))
                me->improve_skill("kongming-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/kongming-quan/kong", 1, me);
        addn("family/gongji", -500, me);

        return 1;
}
  int accept_ask(object me, string topic) 
{ 
        switch (topic) 
        { 
        case "靈台空明" : 
               return MASTER_D->teach_pfm(me, this_object(), 
                             ([ "perform" : "can_perform/kongming-quan/ming", 
                                "name"    : "靈台空明", 
                                "sk1"     : "kongming-quan", 
                                "lv1"     : 120, 
                                "sk2"     : "unarmed", 
                                "lv2"     : 120, 
                                "lv3"     : 200, 
                                "gongxian": 600, ])); 
                     break; 

        case "亂拳飛舞" : 
               return MASTER_D->teach_pfm(me, this_object(), 
                              ([ "perform" : "can_perform/kongming-quan/quan", 
                                 "name"    : "亂拳飛舞", 
                                 "sk1"     : "kongming-quan", 
                                 "lv1"     : 120, 
                                 "sk2"     : "unarmed", 
                                 "lv2"     : 120, 
                                 "lv3"     : 200, 
                                 "gongxian": 600, ])); 
                      break; 

            default: 
                     return 0; 
            } 
     } 
/*
void die()
{
        full_self();
        return;
}

*/
