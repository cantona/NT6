#include <ansi.h>
inherit WAITER;

void create()
{
        set_name("店鋪夥計", ({ "huo ji", "huo", "ji" }));
        set("long", "他就是這家店鋪的夥計。\n");
        set("gender", "男性");
        set("age", random(10) + 20);

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}