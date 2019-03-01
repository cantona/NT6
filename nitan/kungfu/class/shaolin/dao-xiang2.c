// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

string ask_me_1();
string ask_me_2();
string ask_me_3();

#include "dao.h"

void create()
{
        set_name("道象禪師", ({
                "daoxiang chanshi",
                "daoxiang",
                "chanshi",
        }));
        set("long",
                "他是一位身材高大的中年僧人，兩臂粗壯，膀闊腰圓。他手持兵\n"
                "刃，身穿一襲灰布鑲邊袈裟，似乎有一身武藝。\n"
        );

        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 40);
        set("shen_type", 1);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("max_qi", 400);
        set("max_jing", 300);
        set("neili", 450);
        set("max_neili", 450);
        set("jiali", 40);
        set("combat_exp", 10000);
        set("score", 100);

        set_skill("force", 50);
        set_skill("hunyuan-yiqi", 50);
        set_skill("shaolin-xinfa", 50);
        set_skill("dodge", 50);
        set_skill("shaolin-shenfa", 50);
        set_skill("strike", 50);
        set_skill("banruo-zhang", 50);
        set_skill("damo-jian", 50);
        set_skill("buddhism", 50);
        set_skill("literate", 50);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("strike", "banruo-zhang");
        map_skill("parry",  "banruo-zhang");

        prepare_skill("strike", "banruo-zhang");

        create_family("少林派", 39, "弟子");

        set("inquiry", ([
                "金創藥" : (: ask_me_1 :),
                "大還丹" : (: ask_me_2 :),
                "小還丹" : (: ask_me_3 :),
        ]));

        set("jin_count", 20);
        set("dahuandan_count",5);
        set("xiaohuandan_count",5);
        set("master_ob",1);
        setup();

        carry_object("/d/shaolin/obj/dao-cloth")->wear();
}


string ask_me_1()
{
        mapping fam; 
        object ob;
        
        if( !(fam=query("family", this_player())) || fam["family_name"] != "少林派" )
                return RANK_D->query_respect(this_player()) + 
                "與本派素無來往，不知此話從何談起？";

        if ( (int)this_player()->query_condition("bonze_drug" ) > 0 )
                return RANK_D->query_respect(this_player()) + 
                "你是不是剛吃過藥，怎麼又來要了？ 靈藥多吃有害無宜，過段時間再來吧。";

        if (  present("jin chuangyao", this_player()) )
                return RANK_D->query_respect(this_player()) + 
                "你現在身上不是有顆藥丸嗎，怎麼又來要了？ 真是貪得無饜！";

        if (query("jin_count") < 1) return "對不起，金創藥已經發完了";

        ob = new("/d/shaolin/obj/jinchuang-yao");
        ob->move(this_player());

        addn("jin_count", -1);

        message_vision("$N獲得一包金創藥。\n",this_player());
        return "好吧，記住，不到危急關頭不要輕易使用此藥。";

}


string ask_me_2()
{
        mapping fam;
        object ob;
        if( !(fam=query("family", this_player())) || fam["family_name"] != "少林派" )
              return RANK_D->query_respect(this_player()) +
                "與本派素無來往，不知此話從何談起？";

        if ( (int)this_player()->query_condition("bonze_drug" ) > 0 )
                return RANK_D->query_respect(this_player()) +
                "你是不是剛吃過藥，怎麼又來要了？ 靈藥多吃有害無宜，過段時間再來吧。";

        if (  present("dahuan dan", this_player()) )
                return RANK_D->query_respect(this_player()) +
                "你現在身上不是有顆藥丸嗎，怎麼又來要了？ 真是貪得無饜！";

        if (query("dahuandan_count") < 1) return "對不起，大還丹已經發完了";
        ob = new("/d/mingjiao/obj/dahuan-dan");
        ob->move(this_player());
        addn("dahuandan_count", -1);
        message_vision("$N獲得一顆大還丹。\n",this_player());

        return "好吧，記住，不到危急關頭不要輕易使用此藥。";
}

string ask_me_3()
{
        mapping fam;
        object ob;
        if( !(fam=query("family", this_player())) || fam["family_name"] != "少林派" )
                return RANK_D->query_respect(this_player()) +
                "與本派素無來往，不知此話從何談起？";

        if ( (int)this_player()->query_condition("bonze_drug" ) > 0 )
                return RANK_D->query_respect(this_player()) +
                "你是不是剛吃過藥，怎麼又來要了？ 靈藥多吃有害無宜，過段時間再來吧。";

        if (  present("xiaonhuan dan", this_player()) )
                return RANK_D->query_respect(this_player()) +
                "你現在身上不是有顆藥丸嗎，怎麼又來要了？ 真是貪得無饜！";

        if (query("xiaohuandan_count") < 1) return "對不起，小還丹已經發完了";
        ob = new("/d/mingjiao/obj/xiaohuan-dan");
        ob->move(this_player());
        addn("xiaohuan_count", -1);
        message_vision("$N獲得一顆小還丹。\n",this_player());
        return "好吧，記住，不到危急關頭不要輕易使用此藥。";
}
