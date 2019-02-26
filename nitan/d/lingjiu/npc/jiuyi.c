// NPC jiuyi.c

#include <ansi.h>

inherit KNOWER;

void create()
{
        set_name("九翼道人", ({ "jiuyi daoren", "jiuyi"}));
        set("long",
            "他是西夏一品堂禮聘的高手，身材高瘦，臉上總是陰沉沉的。\n"+
            "他輕功極高，擅使雷公擋，憑一手雷公擋功夫，成為江湖的一流高手。\n");
        set("title", "西夏一品堂高手");
        set("gender", "男性");
        set("nickname", HIR "雷動於九天之上" NOR);
        set("age", 40);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set("str", 27);
        set("int", 23);
        set("con", 24);
        set("dex", 30);

        set("max_qi", 2000);
         set("qi", 2000);
        set("jing", 1000);
        set("max_jing", 1000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 20);

        set("combat_exp", 150000);
        set("score", 1500);
        setup();
}