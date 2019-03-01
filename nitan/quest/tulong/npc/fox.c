// fox.c
// Date: Sep.22 1997

inherit NPC;

void create()
{
        set_name("狐狸", ({ "fox", "huli", "hu" }) );
        set("race", "野獸");
        set("age", 4);
        set("long", "一隻多疑成性的狐狸。\n");
//        set("attitude", "aggressive");
        set("attitude", "peace");
        set("shen_type", -1);

        set("limbs", ({ "狐頭", "狐身", "前爪", "後抓", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("combat_exp", 1330000);

        set_temp("apply/attack", 1000);
        set_temp("apply/defense", 2000);
        set_temp("apply/armor", 300);

        setup();

        set("chat_chance", 10);
        set("chat_msg", ({
                "狐狸向後挪了挪，很是戒備的神情。\n",
                "狐狸瞪着多疑的眼光衝你看，全身一副很緊張的模樣。\n",
        }) );
}
