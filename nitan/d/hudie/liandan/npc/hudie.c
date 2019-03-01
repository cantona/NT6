// animal: hudie.c

inherit NPC;

void create()
{
        set_name("蝴蝶", ({ "hu die", "hu" }) );
        set("race", "野獸");
        set("age", 4);
        set("long", "一只美麗的蝴蝶，看到它，你不覺有些感傷。\n");
        set("attitude", "peaceful");

        set("str", 26);
        set("cor", 30);

        set("limbs", ({ "前爪","嘴","後爪","翅膀" }));
        set("verbs", ({ "bite" }) );

        set("combat_exp", 800);

        setup();
}

void die()
{
        message_vision("$N輕輕地飄落在地面！$N無聲無息地死了。\n", this_object());
        destruct(this_object());
}

