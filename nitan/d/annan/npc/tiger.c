// tiger.c 老虎
// Date: Sep.22 1997

inherit NPC;

void create()
{
        set_name("老虎", ({ "tiger", "laohu", "hu" }) );
        set("race", "野獸");
        set("age", 20);
        set("long", @LONG
一只斑斕猛虎，雄偉極了。

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
        set("neili",5800);
        set("max_qi",5800);
        set("max_jing",5800);
        set("max_neili",5800);
        set("jingli",500);
        set("max_jingli",500);

        set_temp("apply/attack", 200);
        set_temp("apply/defense", 300);
        set_temp("apply/armor", 1000);
        set_temp("apply/damage", 1000);

        setup();

        set("chat_chance", 10);
        set("chat_msg", ({
                "老虎在濬巡，嚇得你大氣都不敢出。\n",
                "老虎仰天長嘯，聲震山谷，黃葉紛墜。\n",
        }) );
}


void init()
{
        object me,ob;
        ::init();
        if (interactive(me = this_player()))
        {
        if (!(ob = present("xionghuang", this_player())))          
               {
               remove_call_out("kill_ob");
               call_out("kill_ob", 1, me);
                }
        }
}