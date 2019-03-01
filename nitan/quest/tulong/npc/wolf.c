// wolf.c
// Date: Sep.22 1997

inherit NPC;

void create()
{
        set_name("野狼", ({ "wolf", "yelang", "lang" }) );
        set("race", "野獸");
        set("age", 5);
        set("long", "一只獨行的野狼，半張著的大嘴裡露著幾顆獠牙。\n");
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
                "野狼耷邋著尾巴，突然抬頭，沖你發出一聲凄厲的長嚎。\n",
                "野狼閃著綠幽幽的眼光沖你瞄了瞄，血盆巨口裡答答滴著哈喇子。\n",
        }) );
}
