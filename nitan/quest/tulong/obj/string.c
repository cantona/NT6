inherit ITEM;

void create()
{
        set_name("細麻線", ({ "string" , "xi xiang"}) );
        set_weight(5);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "條");
                set("long", "一條長長的細麻線。\n");
                set("value", 50);
        }
}
