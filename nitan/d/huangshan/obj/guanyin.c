// guanyin.c

inherit ITEM;

void create()
{
        set_name("觀音石", ({ "guanyin shi","guanyin", "shi" }) );
        set_weight(500);
        set_max_encumbrance(8000);
        set("no_get", 1);
        set("no_shown", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "一個亭亭玉立的石人，活象一尊古裝仕女，人稱觀音石。\n");
                set("value", 1);
        }
}

int is_container() { return 1; }
