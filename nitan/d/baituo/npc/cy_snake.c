// Code of JHSH
// cy_snake.c 赤炎(考據：本草綱目)
// by maco

#include <ansi.h>

inherit SNAKE;

int auto_perform_duwu();

void create()
{
        int poison = 10;
        set_name(HIR"赤炎"NOR, ({ "chi yan", "she", "snake" }) );
        set("long", "這是一條遍體通紅的毒蛇，長僅數寸，細小如指。\n宋朝時於陝西清泉初次發現，劇毒無比，聽説若是被其咬到，七步必亡。\n");
        set("age", 100);
        set("attitude", "aggressive");

        set_weight(8000);

        set("str", 30 + poison );
        set("con", 30 + poison );
        set("int", 20);
        set("dex", 30 + poison );

        set("max_jing", 10000);
        set("max_qi", 12000);
        set("qi", 12000);
        set("max_jingli", 10000);

        set("combat_exp", 2000000);

        set_temp("apply/attack", 500);
        set_temp("apply/damage", 300);
        set_temp("apply/dodge", 400);
        set_temp("apply/armor", 200);

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: auto_perform_duwu :),
        }));

        set("snake_poison", ([
                "level"  : 45,
                "perhit" : 25,
                "remain" : 45,
                "maximum": 45,
                "supply" : 2,
        ]));
        set("bt_snake", 1);

        setup();
}


#include "snake_perform.h"