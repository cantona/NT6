// tong-ren.c 銅人

#include <ansi.h>

inherit FIGHTER;

void create()
{
        set_name("銅人", ({ "tong ren", "ren" }) );
        set("gender", "男性" );
        set("age", 30);
        set("long", "一個練功用的比武銅人，是仿制木人制作的，由于\n"
                    "是用青銅制作的，所以具有更持久的耐力，但是卻\n"
                    "不會對練功者造成太大的傷害。\n");
        set("scale", 150);
        set("min_exp", 25000);

        set("str", 25);
        set("con", 25);
        set("dex", 25);
        set("int", 25);

        set("max_qi", 300);
        set("eff_qi", 300);
        set("qi", 300);
        set("max_jing", 100);
        set("jing", 100);
        set("neili", 300);
        set("max_neili", 300);
        set("jiali", 10);
        set("shen_type", 0);


        set("combat_exp", 250000);

        set_skill("force",   80); 
        set_skill("unarmed", 80);
        set_skill("dodge",   80);
        set_skill("parry",   80);

        setup();
}
