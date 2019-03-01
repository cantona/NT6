// liumang.c 流氓

inherit NPC;

void create()
{
        set_name("流氓", ({ "liu mang", "liu" }));
        set("gender", "男性");
        set("age", 19);
        set("long", "他是一個成天遊手好閒的流氓，長得倒是白白胖胖的，也許以前有過錢。\n");
        
        set("combat_exp", 1000);
        set("shen_type", -1);

        set("attitude", "peaceful");
        
        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver",2);
}
