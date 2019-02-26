inherit ITEM;
void create()
{
        set_name("綠草", ({ "grass" , "綠草"}) );
        set_weight(500);
        set_max_encumbrance(8000);
        set("no_get", 1);
        set("no_shown", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "些");
                set("long", "鮮嫩欲滴的綠草，似乎還有幾滴露珠在葉子上閃着微光。\n");
                set("value", 1);
        }
        setup();
} 
int is_container() { return 1; }  
