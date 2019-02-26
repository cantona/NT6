#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "瑩血蛛絲" NOR, ({"yingxue zhusi", "yingxue", "zhusi"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "據説楚國有一劇毒蜘蛛，名為：瑩血，不但其血液晶瑩剔透，且於夜晚處熒光閃\n"
                                                "閃，婉如明珠，劇毒無比，觸之及死。所吐之絲細柔若無，卻絲毫無毒，常年生\n"
                                                                "活在深山祕穴之中，常人即使發現其行蹤，但要捕捉取絲多半也是被其劇毒所傷，\n"
                                                                "無一倖免。\n" HIG 
                                                                "千百年來瑩血蛛絲為製作披風的最佳材料。所鑄造出披風永不磨損。\n" NOR);
                set("unit", "卷");
                set("value", 20000);
                set("item_origin", 1);
                set("material_attrib", "tian jing");
                set("material_name", HIR "瑩血蛛絲" NOR);
                set("can_make", ({ "披風" }));
                set("power_point", 150 + random(10));
        }
}

int query_autoload()
{
        return 1;
}

