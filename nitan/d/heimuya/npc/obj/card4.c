// card4.c

inherit ITEM;

void create()
{
        set_name("天香堂令牌", ({"card4"}));
           if( clonep() )
                set_default_object(__FILE__);
        else {
        set("long",
                "這是日月神教下第四大堂天香堂令牌,上面刻有一柱天香。\n");
        set("unit", "塊");
        set_weight(10);
}
}
