// xiang.c

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(MAG "召神香" NOR, ({ "magic xiang" }) );
        set_weight(2000);
        if( clonep() ){
                set_default_object(__FILE__);
        } else {
                set("value", 10);
                set("unit", "支");
                set("long", MAG "這是一支召神香，傳説可以在五嶽祭壇那裏召喚神仙出現。\n" NOR);
        }
        setup();
}

void start_borrowing()
{
        remove_call_out("destroy");
        call_out("destroy", 30 + random(20));
}

void destroy()
{
        if (environment())
                message("visoin", RED "召神香漸漸的熄滅了，只留下了一點灰燼。\n" NOR,
                        environment());
        destruct(this_object());
}