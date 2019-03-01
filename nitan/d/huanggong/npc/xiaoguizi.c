// xiaoguiz.c

inherit NPC;

void create()
{
        set_name("小桂子", ({ "xiao guizi", "xiao", "guizi" }) );
        set("gender", "無性" );
        set("age", 13);
        set("long",
                "這位小太監在一旁小心侍侯着，手裏拿着一包藥。\n");
        set("combat_exp", 1000);
        set_skill("unarmed", 20);
        set_skill("parry", 20);
        set_skill("dodge", 20);
        
        set_temp("apply/attack", 5);
        set_temp("apply/defense", 5);
        set_temp("apply/damage", 5);

        set("attitude", "friendly");
        set("rank_info/respect", "小公公");
        setup();
        set("chat_chance", 5);
        set("chat_msg", ({
"小桂子説道：公公，再服一劑藥，好不好？",
"小桂子道: 再服半劑，多半不打緊。",
        }) );

        carry_object("/d/city/obj/cloth")->wear();
        carry_object("/d/beijing/obj/yaofen");
        add_money("silver",10);
}