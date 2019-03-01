// camel.c 白駱駝

#include <command.h>
#include <dbase.h>
#include <origin.h>
#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIW"白駱駝"NOR, ({ "bailuotuo" }));
        set("long","一匹西域來的白駱駝，全身雪白，無一根雜毛。\n"
        "中土是沒有這重駱駝的。玩家可以騎上它去指定的地方(ride)。\n");
        set("race", "家畜");
        set("ridable",1);
        set("age", 5);
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
                HIW"白駱駝"NOR"掙了掙轡頭，翻了翻白眼沒理你。\n",
                HIW"白駱駝"NOR"站起來嚼了口乾草，然後又屈腿蹲了下來。\n",
        }) );

        setup();
}