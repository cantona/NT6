// shaofanshifu.c

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("燒飯師傅", ({ "shaofan shifu", "shifu" }));
        set("str", 50);
        set("gender", "男性");
        set("age", 18);
        set("long", "他是聚義館廚房的燒飯師傅。\n");
        set("combat_exp", 2000);
        set("attitude", "friendly");

        setup();
        carry_object("/clone/misc/cloth")->wear();
}
