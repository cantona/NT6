#include <ansi.h>
inherit NPC;

int do_walk();

void create()
{
        set_name("路人", ({ "lu ren", "man", "ren" }) );
        set("gender", "男性");
        set("age", 53 + random(20));
        set("long","這是一個拾荒者，看上去老實巴交的。不過聽說他和官府有交情，最好別去招惹。\n");
        set("attitude", "heroism");
        set("str", 35);
        set("int", 15);
        set("con", 19);
        set("dex", 17);

        setup();
        carry_object(CLOTH_DIR"cloth")->wear();
}