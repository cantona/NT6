#include "roomnpc.h"

inherit NPC;

int  accept_object(object who, object ob);

void create()
{
        set_name("僕人", ({"pu ren"}) );
        set("gender", "男性" );
        set("age", 20 + random(20));
        set("long", "這是一個僕人，長得忠厚老實。");
        set("attitude", "friendly");

        setup();
}

int accept_object(object who, object ob)
{
        object obn;

        if( !query("money_id", ob) )
                return 0;

        if (is_owner(who))
        {
                message_vision(name() + "對$N施了一禮。\n", who);
                destruct(ob);
                return 1;
        }

        destruct(ob);
        message_vision(name() + "對$N點頭哈腰道：“多謝這位" +
                       RANK_D->query_respect(who) + "啦！”\n", who);
        return 1;
}
