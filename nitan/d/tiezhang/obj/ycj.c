//ycj.c
//zqb
#include <ansi.h>
#include <weapon.h>
inherit SWORD;


void setup()
{}

void init()
{
        add_action("do_jian", "jian");
}

void create()
{
       set_name("魚腸劍", ({"yuchang jian","jian"}) );
       set_weight(10000);
       
       if( clonep() )
               set_default_object(__FILE__);
       else{
       set("unit", "柄");
       set("long", "這就是傳說中的魚腸劍，沒想到會在這裡出現！\n"
                   "你忍不住想把它撿(jian)起來！！！\n");
       set("value",1000000);
       set("material", "steel");
       set("no_get",1);
       }
       init_sword(1000);
       setup();
}

int do_jian(string arg)
{
       
        object me = this_player();
        if (!id(arg))
                return 0;
       
                
                {
                message_vision(
HIR"$N輕輕地撿起魚腸劍，突然從劍後射出一枚鋼針，深深的刺入$N的體內。\n"NOR, this_player());
                me->unconcious();
         me->move("/d/tiezhang/shanlu-6");
                return 1;
        }
}

