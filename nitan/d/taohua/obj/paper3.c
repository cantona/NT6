//Cracked by Kafei
// paper.c
inherit ITEM;

void create()
{
        set_name("卷軸", ({"scroll"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "束");
                set("long",
"今有物不知其數，三三數之剩二，五五數之剩三，七七數之剩二，問物幾何？\n");
                set("material", "paper");
        }
}

//三人同行七十希，五樹梅花二十一枝，七子團圓正半月，除百零五便得知。

