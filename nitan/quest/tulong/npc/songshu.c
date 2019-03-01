//songshu.c
inherit NPC;

void create()
{
        set_name("鬆鼠", ({ "song shu", "shu" }) );
        set("race", "野獸");
        set("age", 2);
        set("long", "一只可愛的鬆鼠。\n");
        set("attitude", "peaceful");
 
        set("str", 15);
        set("cor", 16);

        set("limbs", ({ "頭部", "身體", "爪子", "尾巴" }) );
        set("verbs", ({ "bite" }) );
 
        set("combat_exp", 300);

        set_temp("apply/attack", 5);
        set_temp("apply/damage", 3);
        set_temp("apply/defence",5);
        set_temp("apply/armor",3);

        setup();
}
