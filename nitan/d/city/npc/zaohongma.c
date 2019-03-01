// hongma.c 棗紅馬

#include <command.h>
#include <dbase.h>
#include <origin.h>
#include <ansi.h>

inherit NPC;

void create()
{
        set_name(RED"棗紅馬"NOR, ({ "zaohongma" }));
        set("long","一匹駿馬，全身火紅，無一根雜毛。\n"
                "玩家可以騎上它去指定的地方(ride)。\n");
        set("race", "家畜");
        set("age", 5);
        set("ridable", 1);
        set("int", 30);
        set("qi", 300);
        set("max_qi", 300);
        set("jing", 100);
        set("max_jing", 100);
        set("shen_type", 0);
        set("combat_exp",50000);
        set("attitude", "peaceful");

        set("limbs", ({ "頭部", "腹部", "尾巴","後腿","前腿" }) );
        set("verbs", ({ "bite","hoof" }) );
        set_temp("apply/attack", 50);
        set_temp("apply/armor", 15);
        set_temp("apply/damage", 25);
        set("chat_chance", 3);
        set("chat_msg", ({
                RED"棗紅馬"NOR"抖抖長毛，揚頸「吁噓噓」一陣嘶鳴。\n",
                RED"棗紅馬"NOR"扯了扯韁繩，然後不耐地在地上刨着蹄子。\n",
        }) );

        setup();
}