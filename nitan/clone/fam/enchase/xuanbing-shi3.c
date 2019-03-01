inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "玄冰石（3級）" NOR, ({"xuanbing shi3", "shi3"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", HIW "這是一塊通體白色的玉石，產自極北之地，傳說即使是掘千尺而不可得，\n"
                                "可見玄冰石是極其的稀有，以至只有當朝達官貴人和地位顯赫之人才擁有。\n"
                                "玄冰石又稱白玉，通常別繡于錦囊或護身符之上，意味著地位顯赫，諸神\n"
                                "庇佑。\n" HIY
                                "使用方式：鑲嵌于護身符上，增加福緣 +3\n " NOR); 
                              
                set("value", 500000);
                set("enchase/name", "玄冰石（3級）");
                set("enchase/fy", 3);
                set("enchase/point", 1);
                set("enchase/type", "myheart");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", ([]) );
        }
        setup();
}

int query_autoload()
{
        return 1;
}

