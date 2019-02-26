inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIB "古玄玉（1級）" NOR, ({"guxuan yu1", "yu1"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", HIB "這是一塊通體黑色的古玉，只有不到小拇指一半的大小，擁有辟邪的作用，\n"
                                "古玄玉又稱黑玉，通常鑲繡於護身符之上，用於驅邪避災，祈求神靈庇佑。\n" HIY
                                "使用方式：鑲嵌於護身符上，增加氣運 +1\n " NOR);
                set("value", 500000);
                set("enchase/name", "古玄玉（1級）");
                set("enchase/qy", 1);
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

