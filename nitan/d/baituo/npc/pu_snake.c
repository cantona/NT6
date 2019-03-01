// Code of ShenZhou
// pu_snake.c 菩斯曲蛇
// by maco

#include <ansi.h>

inherit SNAKE;

void create()
{
        set_name("菩斯曲蛇", ({ "pusiqu she", "snake", "she", "pusiqu" }) );
        set("age", 100);
        set("long", "這蛇身上金光閃閃，頭頂生有肉角，形狀十分怪異。\n佛經上曾有記載，稱為菩斯曲蛇，聽說此蛇行走如風，極難捕捉。\n");
        set("attitude", "peaceful");

        set_weight(13800);
        set("str", 28 );
        set("con", 38 );
        set("int", 20);
        set("dex", 38 );

        set("max_jing", 4000);
        set("max_qi", 4000);
        set("max_jingli", 4000);


        set("combat_exp", 1000000);

        set_temp("apply/attack", 150);
        set_temp("apply/damage", 150);
        set_temp("apply/dodge", 200);
        set_temp("apply/armor", 150);

        set("snake_poison", ([
                "level"  : 150,
                "perhit" : 50,
                "remain" : 80,
                "maximum": 80,
                "supply" : 3,
        ]));
        set("bt_snake", 1);
        set("limbs", ({ "頭部", "身體", "七寸", "尾巴", "肉角" }) );
        set("verbs", ({ "bite" }) );

        setup();
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) && !is_fighting()
             && random(ob->query_kar()) < 25) {
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob); 
        }
}

void unconcious()
{        
        if(random(4) == 0 ) {
                message_vision("菩斯曲蛇蜿蜒盤行，如一陣風般急竄而逃，頃刻之間已無影無蹤。\n", this_object());
                destruct(this_object());
        }
        else {
                this_object()->disable_player(" <昏迷不醒>");
                set("jing", 0, this_object());
                set("qi", 0, this_object());
                COMBAT_D->announce(this_object(), "unconcious");
                call_out("revive", random(100 - query("con")) + 30);
        }
}

void die()
{
        object ob;
        message_vision("$N全身扭曲，翻騰揮舞一陣，慢慢僵直而死。\n", this_object());
        ob = new(__DIR__"obj/mangshe-dan");
        set("name", "菩斯曲蛇膽", ob);
        set("long", "一枚深紫色的蛇膽，甚是腥臭。\n", ob);
        ob->move(environment(this_object()));
        destruct(this_object());
}
