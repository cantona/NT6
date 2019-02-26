// maque.c 麻雀
// /d/gumu/npc/maque.c
// Date: 08/05/2001
// update april 01.08.26

inherit NPC;

void create()
{
        set_name("麻雀", ({ "ma que", "que", "bird", "maque" }) );
        set("race", "飛禽");
        set("age", 1+random(3));
        set("long", "一隻嘰嘰喳喳，飛來飛去的小麻雀。\n");
        set("attitude", "peaceful");
        
        set("combat_exp", 100);

        set("chat_chance", 10);
        set("chat_msg", ({
                (: this_object(), "random_move" :),
                "小麻雀嘰嘰喳喳的叫着，在你頭頂上東飛西撲，靈便異常。\n",
                                "小麻雀貪婪地看着玉蜂，隨時準備撲上去一飽口福。 \n",
        }) );
        
        set("chat_msg_combat", ({
                (: this_object(), "random_move" :),
                "小麻雀嘰嘰嘰地怒叫着，全身的羽毛都抖豎起來！\n",
        }) );
                
        setup();
}