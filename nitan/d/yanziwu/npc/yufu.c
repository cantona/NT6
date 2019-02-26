#include <ansi.h>
inherit KNOWER;

void create()
{
        set_name("漁夫", ({ "yu fu", "yu", "fu" }));
        set("gender", "男性");
        set("age", 40 + random(10));
        set("long", "一個頭戴斗笠的漁夫，正悠然自得地在岸邊垂釣。\n");

        set("attitude", "friendly");

        set("combat_exp", 60000);
        set("shen_type", 1);

        set_skill("unarmed", 50);
        set_skill("blade", 50);
        set_skill("parry", 50);
        set_skill("dodge", 50);

        set_temp("apply/attack", 15);
        set_temp("apply/defense", 15);
        set_temp("apply/damage", 20);

        setup();
        set("chat_chance", 1);
        set("chat_msg", ({
                CYN "漁夫看了你一眼，自言自語道：這世道真是越來越不太平了。\n" NOR,
        }) );
        carry_object("/clone/cloth/cloth")->wear();
        add_money("coin", 20);
}
