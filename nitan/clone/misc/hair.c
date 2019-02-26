// hair.c 頭髮

#include <ansi.h>

inherit ITEM;
inherit F_SILENTDEST;

int is_hair() { return 1; }

void create()
{
        set_name(RED "頭髮" NOR, ({ "hair" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "束");
                set("value", 1);
                set("no_sell", "我這兒不是假髮店，你一邊兒去。");
                set("long", WHT "一束頭髮。\n" NOR);
                set("only_do_effect", 1);
        }
}

int set_from(object owner)
{
        set("gender",query("gender", owner));
        if (query("gender") == "女性")
        {
                set("name", "青絲");
                set("long", CYN "一束青絲。\n" NOR);
        }
        return 1;
}

int do_effect(object me)
{
        message_vision("$N拿起頭髮就咬，結果弄的滿嘴都是頭髮絲。\n",
                       me, this_object());
        return 1;
}