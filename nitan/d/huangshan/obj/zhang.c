// zhang.c

inherit ITEM;
void create()
{
        set_name("張志程", ({ "zhang zhicheng", "zhicheng","zhang" }) );
        set_weight(500);
        set_max_encumbrance(80000);
        set("no_get", 1);
        set("no_shown", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "座");
                set("long", "一座腰懸無塵劍的張志程塑像。\n");
                set("value", 1);
        }
}

int is_container() { return 1; }
