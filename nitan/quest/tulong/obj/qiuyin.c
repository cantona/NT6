inherit ITEM;

void create()
{
        set_name("蚯蚓", ({ "qiu yin", "qiuyin"}) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "條");
                set("long", "土紅色筷子般粗細的蚯蚓。 \n");
                set("value", 1);
        }
}
