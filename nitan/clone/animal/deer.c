// deer.c
// Last Modified by winder on Aug. 1 2002

inherit NPC;

void create()
{
        set_name("梅花鹿", ({ "deer" }) );
        set("race", "走畜");
        set("age", 5);
        set("long", "一隻漂亮的梅花鹿。\n");
        set("attitude", "peaceful");
        
        set("combat_exp", 800);

        set("chat_chance", 6);
        set("chat_msg_combat", ({
                "\n梅花鹿一轉身，揚起鹿角朝你頂過來！\n",
        }) );
        
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 10);
        set_temp("apply/armor", 10);

        setup();
}

        