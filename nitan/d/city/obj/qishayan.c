// qishayan.c 漆沙硯

inherit ITEM;

void create()
{
        set_name("漆沙硯", ({"qisha yan", "yan"}) );
        set_weight(100);
        if ( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","漆沙硯，上有宋宣和內府制六字。其形質類澄沙而絕輕，入水不沉，甚異之。\n");
                set("value", 5000);
                set("unit" , "方");
        }
        setup();
}

        
