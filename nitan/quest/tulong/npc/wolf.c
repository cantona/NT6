// wolf.c
// Date: Sep.22 1997

inherit NPC;

void create()
{
        set_name("野狼", ({ "wolf", "yelang", "lang" }) );
        set("race", "野獸");
        set("age", 5);
        set("long", "一隻獨行的野狼，半張着的大嘴裏露着幾顆獠牙。\n");
//        set("attitude", "aggressive");
        set("attitude", "peace");
        set("shen_type", -1);

        set("limbs", ({ "狼頭", "狼身", "前爪", "後抓", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 20000);
        set_temp("apply/attack", 200);
        set_temp("apply/defense", 300);
        set_temp("apply/armor", 100);

        setup();

        set("chat_chance", 10);
        set("chat_msg", ({
                "野狼耷邋着尾巴，突然抬頭，衝你發出一聲淒厲的長嚎。\n",
                "野狼閃着綠幽幽的眼光衝你瞄了瞄，血盆巨口裏答答滴着哈喇子。\n",
        }) );
}
