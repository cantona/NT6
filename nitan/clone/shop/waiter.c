#include <ansi.h>
inherit WAITER;

void create()
{
        set_name("店舖伙計", ({ "huo ji", "huo", "ji" }));
        set("long", "他就是這家店舖的伙計。\n");
        set("gender", "男性");
        set("age", random(10) + 20);

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}