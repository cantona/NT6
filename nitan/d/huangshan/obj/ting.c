// ting.c

inherit ITEM;

void create()
{
        set_name("桃源亭", ({ "taoyuan ting", "ting", "taoyuan" }) );
        set_weight(500);
        set_max_encumbrance(80000);
        set("no_get", 1);
        set("no_shown", 1);
        set("prep","behind");
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "一個位於桃花峯上的小木亭。
\n");
                set("value", 1);
        }
}

int is_container() { return 1; }
