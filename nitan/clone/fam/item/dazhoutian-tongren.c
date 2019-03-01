// 銅人

#include <ansi.h>

inherit ITEM;

#define TONGREN_D        "/adm/daemons/tongrend2"

int is_wmtongren() { return 1; };

void create()
{
        set_name(HIY "大周天銅人" NOR, ({ "dazhoutian tongren" }) );
        set_weight(50);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "這是一個破舊的銅人，上面繪制了一些圖案，但是已經無法辯識。\n" HIG
                                "使用指令 kg dazhoutian tongren 鑒定沖穴銅人。\n" NOR);
                set("value", 1);
                set("unit", "個");
                set("skill", ([
                        "name" : "jingluo-xue",
                        "exp_required" : 50000,
                        "jing_cost"  : 20,
                        "difficulty" : 80,
                        "max_skill"  : 120,
                        "min_skill"  : 0,                        
                ]));

        }

        setup();
}

void init()
{
        add_action("do_kg", "kg");        
}

int do_kg(string arg)
{
        object ob, me;
        
        me = this_player();
        
        if (! me)return 0;
        
        if (! arg || arg != "dazhoutian tongren")
                return notify_fail("你要對什麼進行開光鑒定。\n");
                
        if (! objectp(ob = present("dazhoutian tongren", me)))
                return notify_fail("你身上沒有這樣物品。\n");        
                
        TONGREN_D->open_tongren(me, ob);
        
        return 1;                        
}

int query_autoload()
{
         return 1;
}
