#include <ansi.h>
inherit NPC;

void create()
{
        set_name("流氓兔", ({ "rabbit" }) );
        set("race", "野獸");
        set("age", 5);
        set("long",
"一只白尾巴的野兔，尾巴一翹一翹的。\n");
        set("max_qi", 1000);
        set("env/wimpy", 99);
        set("maze_get",1);
        set("limbs", ({ "頭部", "身體", "尾巴" }) );
        set("verbs", ({ "bite" }) );
        set("death_msg",YEL"\n流氓兔兩眼一閉，腿兒一蹬，直挺挺的躺地上。。。。 \n"NOR);
        set("self_go_msg",1);
        set("arrive_msg","流氓兔蹦蹦跳跳地跑了過來。");
        set("leave_msg","流氓兔一下子竄沒了。");

        set_skill("dodge", 50+random(50));

        set("maze_item",1);
        setup();
}