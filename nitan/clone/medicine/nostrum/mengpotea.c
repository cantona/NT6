// tea.c 孟婆茶

#include <ansi.h>
#include <command.h>
#include <login.h>
inherit ITEM;

int mpc_effect(object me);
void create()
{
        set_name(GRN "孟婆茶" NOR,({GRN "mengpo tea" NOR, "cha", "tea"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                 set("long", GRN"這就是傳説中著名的孟婆茶。每個鬼魂在投胎轉世之前，都要喝上一碗孟婆茶，據説喝了這碗茶後，你在陽間的一切一切就都會忘得乾乾淨淨，就此與今世脱離了一切關係。\n");
                set("unit", "碗");
        }
        set("pour_type", "1");
        setup();
}

void init()
{
        add_action("do_drink", "drink");
        add_action("do_drink", "he");
}

int do_drink(string arg)
{
        object me = this_player();

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎着了。\n");
//if a ghost
        if( !me->is_ghost() )
        {
                write("你得先死了才能喝這碗茶......\n\n\n要不，先死一次？......\n");
                return 1;
        }
        message_vision("$N猶豫了一會兒，還是把一碗孟婆茶喝了下去。\n\n\n\n",me);
        remove_call_out("mpc_effect");
        call_out("mpc_effect", 5, me);
        return 1;
}
int mpc_effect(object me)
{     
        string stroom;
        stroom=query("startroom", me);
        if( stroom[0..7] != "/d/death"  )
        if( query("eff_jing", me)<5 && query("eff_qi", me)<5 )
        if( query("dietime", me) && time()-query("dietime", me)<600 )
        {
                set("eff_qi",query("max_qi",  me), me);
                set("qi",query("max_qi",  me), me);
                set("eff_jing",query("max_jing",  me), me);
                set("jing",query("max_jing",  me), me);
        }
        message_vision(BLU "$N覺得一陣頭暈目眩，以前發生的事情似乎忘記了許多許多..........\n\n\n"NOR, me);
        tell_object(me,BLU "忘記吧...................\n\n\n\n" NOR);
        destruct(this_object());
        return 1;
}
