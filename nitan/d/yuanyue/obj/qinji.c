inherit ITEM;

void create()
{
    set_name("琴幾", ({ "qinji", "desk", "ji"}) );
    set_weight(500);
    set_max_encumbrance(8);
    set("no_get", 1);
    set("no_shown", 1);
    if( clonep() )
        set_default_object(__FILE__);
    else {
    set("prep", "on");
        set("unit", "張");
        set("long", "一張琴幾。\n");
        set("value", 1);
    }
    setup();
} 
int is_container() { return 1; }      
