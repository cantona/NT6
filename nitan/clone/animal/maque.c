// maque.c 麻雀
// Last Modified by winder on Aug. 1 2002

inherit NPC;

void create()
{
        set_name("麻雀", ({ "ma que", "que", "bird" }) );
        set("race", "飛禽");
        set("age", 3);
        set("long", "一只嘰嘰喳喳，飛來飛去的小麻雀。\n");
        set("attitude", "peaceful");
        
        set("combat_exp", 100);

        set("chat_chance", 10);
        set("chat_msg", ({
                (: this_object(), "random_move" :),
                "小麻雀嘰嘰喳喳的歡叫著，在你頭頂上飛來飛去。\n",
                "小麻雀忽而停在牆頭，忽而飛上樹梢，忙碌著找食吃。\n",
        }) );
        
        set("chat_msg_combat", ({
                (: this_object(), "random_move" :),
                "小麻雀嘰嘰嘰地怒叫著，全身的羽毛都抖豎起來！\n",
        }) );
                
        setup();
}