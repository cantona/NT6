// yuchang-jian.c 魚腸劍
// Last Modified by winder on Nov. 17 2000

#include <ansi.h>;
#include <weapon.h>;
inherit SWORD;
inherit F_UNIQUE;

void setup()
{}

void init()
{
        if (!query("got"))
        add_action("do_jian", "jian");
}

void create()
{
        set_name(HIR"魚腸劍"NOR, ({"yuchang jian", "jian", "sword"}) );
        set_weight(10000);

        if( clonep() )
                set_default_object(__FILE__);
        else{
                set("unit", "柄");
                set("long", "這就是傳說中的魚腸劍，沒想到會在這裡出現！\n"
                "你忍不住想把它撿(jian)起來！！！\n");
                set("material", "steel");
                set("no_get",1);
                set("no_drop",1);
                set("count",3);
    set("wield_msg", HIR "一道暗紅血光劃過，魚腸劍已落入$N" HIR "手中。\n" NOR);
    set("unwield_msg", HIR "天地忽暗，$N" HIR "手中的魚腸劍已悄然隱沒 。\n" NOR);
        }
        init_sword(1);
        setup();
}

int do_jian(string arg)
{
        object me = this_player();
        if (!id(arg)) return 0;
        if (query("count") > 0 || me->query_dex()<40)
        {
        if (query("count")<=0) set("count",1);
        message_vision( HIR"$N輕輕地撿起魚腸劍，突然從劍後射出"+chinese_number(query("count"))+"枚鋼針，深深的刺入$N的體內。\n"NOR, me);
        if (me->query_dex()>40)
        addn("count",-1);
        me->unconcious();
        me->move("/d/tiezhang/shanlu-6"); 
        }
        else
        {
                message_vision( HIR"$N輕輕地撿起魚腸劍，突然從劍後射出一枚鋼針。但是$N早有防備，馬上躲了開去。\n"NOR, me);
                message("channel:rumor",MAG"【謠言】某人："+query("name", this_player())+"拿到"+query("name", this_object())+MAG+"啦。\n"NOR,users());
                tell_object(me,"你撿起一把"+query("name", this_object())+"。\n");
                set("long", "這是春秋名匠歐冶子所鑄的五口寶劍之魚腸劍。\n劍身長僅寸余，細看之下隱隱有血光浮現。\n");
//                remove_action(me,"jian");
                set("got",1);
                set("weapon_prop/damage",300);
                set("rigidity",300/4);
                move(me);
                }
        return 1;
}
