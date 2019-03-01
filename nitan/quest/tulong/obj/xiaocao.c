#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
    set_name(HIM "精靈之花" NOR, ({ "flower" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一朵嬌艷美麗，不沾半點世間煙火的精靈之花。\n");
                set("unit", "朵");
                set("value", 6); 
                set("no_get", 1);
                set("material", "plant");
                set("armor_prop/armor", 0);
                set("armor_prop/per", 3);
                set("wear_msg", "$N輕輕地把一朵$n戴在頭上。\n");
                set("unwield_msg", "$N輕輕地把$n從頭上除了下來。\n");
                set("female_only", 1);

        }
        setup();
}

void init()
{
        add_action("do_get","zhai");
}

int do_get(string arg)
{
        object me,ob;
        me=this_player();
        ob=this_object(); 

    if( !arg ) return notify_fail("你要撿起什麼東西？\n");
        if (arg=="flower" ) 
         {
        write(HIM"精靈之花"NOR+HIG"中出現了一只小精靈，\n
小精靈振動著翅膀說：謝謝你解開了第三個封印，請過關吧！\n"NOR);
        ob->move(me);   
 message_vision(HIG"$N被一陣清風送到了另一個房間。\n"NOR, me); 
        me->move("/d/dragon/spirit5");
                set_temp("m_success/初級", 1, me);
        destruct(ob);        return 1;
         }
}
