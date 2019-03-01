// tiger.c 老虎
// Date: Sep.22 1997

inherit NPC;

void create()
{
        set_name("老虎", ({ "tiger", "laohu", "hu" }) );
        set("race", "野獸");
        set("age", 20);
        set("long", @LONG
一隻斑斕猛虎，雄偉極了。

         _.-'"''--..__.("\-''-'")
 ('.__.-' (  *  ) .-'    ( @ _@'
  `-..-''.' _.'  (   _.  `(._Y_)
         `. `._`--\  \_-.._`--'.._
          `-.!))  `.(il)   ''-.(li)

LONG);


//        set("attitude", "aggressive");
        set("attitude", "peace");
        set("shen_type", -1);

        set("limbs", ({ "虎頭", "虎身", "前爪", "後抓", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 30000);
        set_temp("apply/attack", 300);
        set_temp("apply/defense", 300);
        set_temp("apply/armor", 3);

        setup();

        set("chat_chance", 10);
        set("chat_msg", ({
                "老虎在浚巡，嚇得你大氣都不敢出。\n",
                "老虎仰天長嘯，聲震山谷，黃葉紛墜。\n",
        }) );
}
