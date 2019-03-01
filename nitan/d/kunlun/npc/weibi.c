// Npc: /d/kunlun/npc/weibi.c 衛璧
// Last Modified by winder on Jun. 29 2001

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("衛璧", ({ "wei bi", "wei"}));
        set("long","他容貌英俊，長身玉立，雖在這等大寒天候，卻只\n穿了一件薄薄的淡黃色緞袍，顯是內功不弱。\n");
        set("gender", "男性");
        set("per", 30);
        set("age", 18);

        set_skill("finger", 40);
        set_skill("sun-finger", 40);
        set_skill("dodge", 40);
        set_skill("tiannan-bu", 40);
        set_skill("parry", 40);
        map_skill("dodge", "tiannan-bu");
        map_skill("parry", "sun-finger");
        map_skill("finger", "sun-finger");
        prepare_skill("finger", "sun-finger");

        set("combat_exp", 150000);
        set("shen_type", 1);
        setup();
        carry_object(__DIR__"obj/yellowcloth")->wear();
}
