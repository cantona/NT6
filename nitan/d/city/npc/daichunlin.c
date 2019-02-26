// npc: /d/city/npc/daichunlin.c
// Last Modified by Winder on Jul. 15 2000

#include <ansi.h>
inherit NPC;

void create()
{
        set_name(YEL "戴春林" NOR, ({ "dai chunlin", "dai", "chunlin"}) );
    set("title", "戴記香粉鋪老闆");
    set("age", 42);
    set("long", @LONG
他是揚州城裏戴記香粉鋪的老闆，五短身材，肥肥胖胖，但看上去甚是威
嚴，另人不敢親近。
LONG
        );
        set("attitude", "friendly");
        set("rank_info/respect", "老哥");
        set("rank_info/rude","老王八蛋");
        set("combat_exp",10000);
        set_skill("unarmed", 5);
        setup();
        carry_object( "/clone/cloth/male-cloth")->wear();
}
