//tongbw.c

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;

string ask_zijinchui();
string ask_zijinchuifa();

void create()
{
        set_name("童百熊", ({ "tongbai xiong","xiong"}) );
        set("gender", "男性" );
        set("age", 75);
        set("title", "日月神教風雷堂長老");
        set("long", "他白髮披散, 銀髯戟張, 臉上的肌肉牽動, \n"
                    "圓睜雙眼, 身上的鮮血已然凝結, 神情甚是可怖。\n");
        set("attitude", "friendly");
        set("shen_type", -1);

        set("per", 21);
        set("str", 23);
        set("int", 23);
        set("con", 22);
        set("dex", 20);

        set("max_qi", 1000);
        set("max_jing",1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 200);
        set("combat_exp", 350000);
        set("score", 30000);

        set_skill("force", 130);
        set_skill("riyue-xinfa", 130);
        set_skill("dodge", 130);
        set_skill("piaomiao-shenfa", 130);
        set_skill("hand", 130);
        set_skill("huanmo-longtianwu", 130);
        set_skill("cuff", 130);
        set_skill("xuwu-piaomiao", 130);
        set_skill("parry", 130);
        set_skill("literate", 80);
        set_skill("sword", 130);
        set_skill("riyue-jian", 130);
        set_skill("blade", 150);
        set_skill("tianmo-dao", 150);

        map_skill("force", "riyue-xinfa");
        map_skill("dodge", "piaomiao-shenfa");
        map_skill("hand", "huanmo-longtianwu");
        map_skill("cuff", "xuwu-piaomiao");
        map_skill("sword", "riyue-jian");
        map_skill("parry", "tianmo-dao");
        map_skill("blade", "tianmo-dao");

        prepare_skill("hand", "huanmo-longtianwu");
        prepare_skill("cuff", "xuwu-piaomiao");

        create_family("日月神教",2,"弟子 風雷堂長老");

        set("chat_chance", 2);
        set("chat_msg", ({
            "童百熊怒瞪雙眼道: “我沒錯, 我沒有叛教! 東方兄弟你不能冤枉我呀! ”\n",
            "童百熊歎了一口氣説：“我和東方兄弟出生入死, 共歷患難的時候, 你們還沒生下來哪!”\n"
        }));

        set("inquiry",([
            "紫金錘"   : (: ask_zijinchui :),
            "紫金錘法" : (: ask_zijinchuifa :),
            "祕籍"     : (: ask_zijinchuifa :),
        ]));
        set("zijin_book", 1);

        set("master_ob",2);
        setup();
        carry_object("/d/heimuya/npc/obj/zijinchui");
        carry_object("/d/heimuya/npc/obj/dadao")->wield();
        carry_object("/d/heimuya/npc/obj/cloth")->wear();
        carry_object("/d/heimuya/npc/obj/card1");
}

void attempt_apprentice(object ob)
{
    if(! permit_recruit(ob))  return;

    if((int)ob->query_skill("riyue-xinfa", 1) < 80)
    {
         command("say 你的內功心法尚欠火候，多練練去吧！");
         return;
    }

    command("recruit "+query("id", ob));
    set("title", HIM"日月神教"HIY"風雷堂教眾"NOR, ob);
}

string ask_zijinchui()
{
    set_temp("zijin_chuifa", 1, this_player());
    message_vision("童百熊歎了口氣，説道：“這柄紫金錘是當年一位"
                   "武林前輩送給我的。”\n", this_object());
    return "唉，只可惜我未能將錘法練成。";
}

string ask_zijinchuifa()
{
    object ob = new("/clone/book/zijin_book");
    object me = this_player();
    string msg;

    if( query_temp("zijin_chuifa", me) && !query("couple", me) && 
        query("combat_exp", me)>10000 )
    {
        if (query("zijin_book"))
        {
            message_vision("童百熊歎了口氣，説道：“我習練紫金錘法多年，仍不能"
                           "悟出其中要領，只習得十之一二。”\n", me);
            msg = "這位" + RANK_D->query_respect(me) + "，你我一見如故，這" +
                  "本書我就送你吧，希望你能領悟其中精要。";
            ob->move(this_object());
            set("zijin_book", 0);
            command("givezijin_bookto"+query("id", me));
        }
        else   msg = "你來晚了，《紫金錘法》一書我已送人。";

        delete_temp("zijin_chuifa", me);
        return msg;
    }
    else
        return "紫金錘法我只傳有緣之人，可惜你不太適合。";
}

void reset()
{
    set("zijin_book", 1);
}
