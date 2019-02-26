// wolf.c
// Date: Sep. 5 2000

inherit NPC;

void create()
{
        set_name("母狼", ({ "mu lang", "wolf", "lang" }) );
        set("race", "走獸");
        set("age", 5);
        set("gender", "雌性");
        set("long", "一隻母狼，半張着的大嘴裏露着幾顆獠牙。\n");
        set("attitude", "peace");
        set("shen_type", -1);

        set("combat_exp", 20000);
        set_temp("apply/attack", 2000);
        set_temp("apply/defense", 3000);
        set_temp("apply/armor", 800);

        setup();

        set("chat_chance", 10);
        set("chat_msg", ({
                "母狼耷邋着尾巴，突然抬頭，衝你發出一聲淒厲的長嚎。\n",
                "母狼閃着綠幽幽的眼光衝你瞄了瞄，血盆巨口裏答答滴着哈喇子。\n",
        }) );
}
