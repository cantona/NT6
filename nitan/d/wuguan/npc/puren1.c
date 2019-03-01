inherit NPC;
#include <ansi.h>

void create()
{
        set_name("僕人", ({ "pu ren", "puren","ren" }) );
        set("gender", "男性" );
        set("age", 25);
        set("int", 28);
        set("long", "這是個僕人打扮的年青人，兩眼亂轉，四處看個不停。\n");
        set("attitude", "peaceful");
        set("combat_exp",10000 + random(5000));
        set("chat_chance", 1);
        set("chat_msg", ({
        	CYN "僕人突然說道：後院很需要人手，郭大俠正為此煩惱呢。\n" NOR,
        	CYN "僕役低聲的說：在後院做事有好多好處啊。\n" NOR,
        }));
        setup();
        carry_object("/clone/misc/cloth")->wear();
}