// card3.c

inherit ITEM;

void create()
{
        set_name("青龍堂令牌", ({"card3"}));
           if( clonep() )
                set_default_object(__FILE__);
        else {
        set("long",
                "這是日月神教下第三大堂青龍堂令牌,上面刻有一條青龍神。\n");
        set("unit", "塊");
        set_weight(10);
}
}
