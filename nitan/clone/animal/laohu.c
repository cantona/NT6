// laohu.c 老虎
// Last Modified by winder on Aug. 1 2002

// inherit NPC_TRAINEE;
inherit "/inherit/char/trainee";

void create()
{
        set_name("老虎", ({ "lao hu", "hu", "tiger" }) );
        set("race", "走獸");
        set("age", 25);
        set("long", "這是一頭吊睛白額，氣勢洶洶的大虎，正惡狠狠地盯着你，好像隨時隨地都會撲上來擇人而噬！\n");
        set("msg_fail", "$n衝$N呲牙吼了一聲");
        set("msg_succ", "$n一面口中向$N荷荷發威，一面向後退了半步，似乎有些怯了");
        set("msg_trained","$n低吼着在$N的面前伏了下來");
        set("auto_follow",1);
        set("attitude", "aggressive");

        set("wildness", 12);
        set("ridable", 1);
        set("ability", 4);
        
        set("str", 40);        
        set("con", 40);
        set("dex", 40);        
        set("int", 10);

        set("combat_exp", 20000);

        set_temp("apply/attack", 50);
        set_temp("apply/damage", 70);
        set_temp("apply/armor",  30);

        set_weight(150000);

        set("chat_chance", 10);
        set("chat_msg", ({
                (: this_object(), "random_move" :),
                "老虎用前爪拍擊着地面，口中荷荷發威，好像隨時都要撲上來！\n",
                "老虎微微側着腦袋，雙目炯炯，緊緊地注視着你的一舉一動。\n",
                "老虎突然立了起來，繞着你走了半圈，似乎在觀察着什麼。\n",
        }) );
        
        set("chat_msg_combat", ({
                (: this_object(), "random_move" :),
                "\n老虎怒嘯一聲，一反身，長長的尾巴向鐵棍一樣揮了過來！\n",
                "\n老虎全身一曲一弓，忽然躍起半空，猛地撲了下來！\n",
        }) );
                
        setup();
}

void die()
{
        message_vision("\n$N仰天慘嚎了一聲，趴在地上不動了。\n", this_object());
        ::die();
}

void init()
{        
        object ob;

        ::init();
        if( interactive(ob = this_player()) && ob->query_weight() >= 50000)
        {
                if(!this_object()->query_lord(ob)) {
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob);
                }
        }        
}
