// shutong.c

inherit NPC;

void create()
{
        set_name("書童", ({ "shu tong", "tong" }));
        set("gender", "男性");
        set("age", 35);
        set("long", "他是莊主的隨身書童，平素看管藏書。\n");
        set("combat_exp", 10000);
        set_skill("dodge", 50);
        set_skill("unarmed", 50);
        set_temp("apply/attack",  50);
        set_temp("apply/defense", 50);
        set("shen_type", -1);
        setup();

        add_money("silver",3);
        carry_object("/clone/misc/cloth")->wear();
}
