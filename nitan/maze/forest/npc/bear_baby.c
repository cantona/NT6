inherit NPC;

void create()
{
        string *names = ({"小棕熊","小黑熊","小白熊"});
        set_name( names[random(sizeof(names))], ({ "baby bear","bear"}));
        set("vendetta_mark","bear");
        set("race", "野獸");
        set("gender", "雄性");
        set("age", 20);
        set("long", "這是一隻可愛的小熊。\n");

        set("str", 50);
        set("dex", 20);
        set("con", 50);
        set("max_qi", 2000);
        set("max_jing", 1000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("combat_exp", 100000);

        set("attitude", "peaceful");
/*
        set("chat_chance", 2);
        set("chat_msg", ({
                "小熊拱了拱你的腳。\n"
        }) );
*/
        set("limbs", ({ "頭部", "身體", "前腳", "後腳", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set_temp("apply/attack", 30);
        set_temp("apply/armor", 30);
        set_temp("apply/unarmed_damage", 20);
        setup();
        carry_object(__DIR__"obj/bear_skin");
}
