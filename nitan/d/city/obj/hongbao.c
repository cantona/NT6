#include <ansi.h>
inherit ITEM;
void create()
{
    set_name( HIR "紅包" NOR, ({ "hongbao" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "個");
            set("material", "cloth");
            set("long", "一個小小的紅包，上面繡著：新wiz上任。小小禮物。\n");
          }
    setup();
}

void init()
{
    if(environment()==this_player())
        add_action("do_open","open");
}
int do_open(string arg)
{
        object gold;
        if(arg != "hongbao" && arg != "紅包") 
                return 0;
        if(query("opened"))
                return notify_fail("你打開小紅包，但裡面是空的！\n");
        gold = new("/clone/money/gold");
        gold->set_amount(10+random(10));
        set("name", "純金葉子", gold);
        set("base_unit", "張", gold);
        gold->move(this_player());
        set("opened",1);
        return notify_fail("你打開小紅包，從裡面拿出幾張純金葉子！\n");
}