// card2.c

inherit ITEM;

void create()
{
        set_name("白虎堂令牌", ({"card2"}));
           if( clonep() )
                set_default_object(__FILE__);
        else {
        set("long",
                "這是日月神教下第二大堂白虎堂令牌,上面刻有一隻白虎神。\n");
        set("unit", "塊");
        set_weight(10);
}
}
