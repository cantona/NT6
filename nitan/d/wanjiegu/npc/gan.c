// gan.c

inherit NPC;

void create()
{
        set_name("甘寶寶", ({ "gan baobao","gan","baobao" }) );
        set("gender", "女性" );
        set("age", 35);
        set("str", 16);
        set("con", 24);
        set("dex", 21);
        set("per", 27);
        set("int", 27);
        set("long",
        "甘寶寶容色清秀，多愁善感，年輕時曾與\n"
        "段正淳有過一段風流佳話，但段正淳未能\n"
        "與她共守白頭，段正淳離去後，甘寶寶因\n"
        "有身孕，無奈嫁給鍾萬仇為妻。\n");

        set("attitude", "friendly");

        set("max_neili", 200);
        set("neili", 200);
        set("force_factor", 10);

        set("combat_exp", 35000);

        set_skill("finger", 60);
        set_skill("parry", 40);
        set_skill("dodge", 50);
        set_skill("sword", 30);
        set_skill("force", 50);
        set_skill("sun-finger",40);
        set_skill("yizhi-chan",60);

        map_skill("finger", "sun-finger");
        map_skill("parry", "sun-finger");

        setup();

        carry_object("/d/wanjiegu/npc/obj/red-dress")->wear();
        carry_object("/d/wanjiegu/npc/obj/shoes")->wear();
}
