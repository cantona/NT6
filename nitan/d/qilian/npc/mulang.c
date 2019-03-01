// wolf.c
// Date: Sep. 5 2000

inherit NPC;

void create()
{
        set_name("母狼", ({ "mu lang", "wolf", "lang" }) );
        set("race", "走獸");
        set("age", 5);
        set("gender", "雌性");
        set("long", "一只母狼，半張著的大嘴裡露著幾顆獠牙。\n");
        set("attitude", "peace");
        set("shen_type", -1);

        set("combat_exp", 20000);
        set_temp("apply/attack", 2000);
        set_temp("apply/defense", 3000);
        set_temp("apply/armor", 800);

        setup();

        set("chat_chance", 10);
        set("chat_msg", ({
                "母狼耷邋著尾巴，突然抬頭，沖你發出一聲凄厲的長嚎。\n",
                "母狼閃著綠幽幽的眼光沖你瞄了瞄，血盆巨口裡答答滴著哈喇子。\n",
        }) );
}
