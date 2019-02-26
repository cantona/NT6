#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIR "紅包" NOR, ({ "hongbao" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "個");
            set("material", "cloth");
            set("long", "一個小小的紅包，上面繡着：銀鈎賭場，黃。\n");
          }
    set("owner", "老先生");
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
        if(arg != "hongbao" && arg != "紅包") return 0;
        if(query("opened"))
                return notify_fail("你打開小紅包，但裏面是空的！\n");
        gold = new("/clone/money/gold");
        gold->set_amount(2);
        gold->set("name","純金葉子");
        gold->set("base_unit","張");
        gold->move(this_player());
        set("opened",1);
        return notify_fail("你打開小紅包，從裏面拿出幾張純金葉子！\n");
}
