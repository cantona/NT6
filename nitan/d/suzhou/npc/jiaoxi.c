// jiaoxi.c

inherit NPC;
#include <ansi.h>

void create()
{
        set_name("老夫子", ({ "lao fuzi", "lao", "fuzi" }));
        set("long",
"一個唯利是圖的蘇州老教習，肚子裏有墨水，可你還要有錢。\n");
        set("gender", "男性");
        set("age", 65);
        set_skill("literate", 200);

        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_skill("parry", 20);
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 20);
        set_temp("apply/damage", 20);

        set("combat_exp", 40000);
        set("shen_type", 1);
        set("inquiry", ([
            "書"   : "唉！書到用時方恨少。",
            "借書" : "借？你不還我到哪裏找你？哼！",
        ]));
        setup();
}

int recognize_apprentice(object ob)
{
        if( !query_temp("mark/朱2", ob))return 0;
        addn_temp("mark/朱2", -1, ob);
        return 1;
}

int accept_object(object who, object ob)
{
        object me = this_player();
        if( !query_temp("mark/朱2", who))set_temp("mark/朱2", 0, who);
        if( query("money_id", ob) && ob->value() >= 500 )
        {
                message_vision("老夫子同意指點$N一些讀書寫字的問題。\n", who);
                addn_temp("mark/朱2", ob->value()/50, who);
                return 1;
        }
}
