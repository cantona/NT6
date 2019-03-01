// zhangfang.c

#include <ansi.h>

inherit NPC;
int  chu_hai();

void create()
{
        set_name("賬房老夫子", ({ "lao zhangfang","zhangfang","lao" }));
        set("gender", "男性");
        set("age", 56);
        set("long",
        "這是一個見錢眼開的老賬房。飽經風霜的臉上透出一絲狡猾。\n", );

        set("combat_exp", 10000);
        set("shen_type", 1);

        set("eff_qi",2000);
        set("qi",2000);
        set("max_neili", 1000);
        set("neili", 1000);
        set("jiali", 100);

        set_skill("force", 200);
        set_skill("unarmed", 400);
        set_skill("dodge", 200);
        set_skill("parry", 200);
        set("inquiry", ([
            "學費"  : "五兩銀子！\n",
            "學習"  : "先交五兩銀子！\n",
            "練功"  : "先交五兩銀子！\n",
            "學武"  : "先交五兩銀子！\n",
            "學武功": "先交五兩銀子！\n",
        ]) );

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

int accept_object(object who, object ob)
{
    if( query("combat_exp", who) >= 50000 )
    {
        message_vision("老賬房望著$N說：你的武功應該歷練江湖才能再長進，不能埋沒在這裡了。\n", who);
        return 0;
    }
    if( query("money_id", ob) && ob->value() >= 500 )
    {
        set_temp("marks/jinniu_paied", 1, who);
        message_vision("老賬房對$N說：好！既然這位" + RANK_D->query_respect(who)
          + "如此上進，那就進去找師傅學吧！\n" , who);
               return 1;
    }
    else
        message_vision("老賬房皺眉對$N說：您給的也太少了點兒吧？\n", who);
        return 0;
}