// jlhua.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("金鏤花", ({ "jinlou hua", "hua" }));
        set_weight(400);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", "這是一張用金箔雕刻的花，栩栩如生。\n");
                set("value", 12000);
                set("material", "gold");
        }
        setup();
}