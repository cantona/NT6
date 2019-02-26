#include <ansi.h>
inherit NPC;
void create()
{
        set_name("癩蛤蟆", ({ "toad" }) );
        set("race", "野獸");
        set("age", 5);
        set("maze_get",1);
        set("combat_exp",1000000);
        set("long", "一隻身上長滿疙瘩，難看之極的癩蛤蟆。\n");
        set("verbs", ({ "bite" }) );
        set("limbs", ({
                "頭部", "頸部", "胸部", "後背", "腹部",
                "前腿", "後腿"
        }) );
        set("death_msg",CYN"\n癩蛤蟆白肚子朝天一陣哆嗦。。。。 \n"NOR);
        set("self_go_msg",1);
        set("arrive_msg","癩蛤蟆悉悉簌簌地跑了過來。");
        set("leave_msg","癩蛤蟆一溜煙地跑掉了。");

        set_skill("dodge", 30);
        set("maze_item",1);
        setup();
}
