// card1.c

inherit ITEM;

void create()
{
        set_name("風雷堂令牌", ({"card1"}));
           if( clonep() )
                set_default_object(__FILE__);
        else {
        set("long",
                "這是日月神教下第一大堂風雷堂令牌,上面刻有一風雷神。\n");
        set("unit", "塊");
        set_weight(10);
}
}
