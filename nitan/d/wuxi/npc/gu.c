// gu.c 顧憲成

inherit NPC;
#include <ansi.h>

void create()
{
        set_name("顧憲成", ({ "gu xiancheng", "gu" }));
        set("gender", "男性");
        set("long", "顧憲成重于學識，講究品行，受到各地學者仰慕。\n");
        set("age", 45);
        set("no_get", 1);
        set_skill("literate", 300);

        set_skill("unarmed", 80);
        set_skill("dodge", 80);
        set_skill("parry", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/damage", 20);

        set("combat_exp", 400000);
        set("shen_type", 1);
        set("inquiry", ([
                "書"   : "唉！書到用時方恨少。",
                "借書" : "借？你不還我到哪裡找你？哼！",
        ]));
        setup();

}

int recognize_apprentice(object ob)
{
        if( !query_temp("mark/顧", ob) )
                return 0;
        addn_temp("mark/顧", -1, ob);
        return 1;
}

int accept_object(object who, object ob)
{
        object me = this_player();
        if( !query_temp("mark/顧", who) )
                set_temp("mark/顧", 0, who);
        if( query("money_id", ob) && ob->value() >= 1000 )
        {
                message_vision("顧憲成同意指點$N一些讀書寫字的問題。\n", who);
                addn_temp("mark/顧", ob->value()/50, who);
                if( me->query_skill("literate", 1) > 21)
                {
                        tell_object(me,"你現在已有一定的文化知識,也可以自己讀書深造了。\n");
                        return 1;
                }
                return 1;
        }
}

