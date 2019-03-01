#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(HIM + "昊天塔" NOR, ({ "haotian ta", "haotian", "ta" }) );
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "個");
                set("long", HIM "這是一個擁有吸星換月之力的寶塔，不時地從中投射出\n"
                                "奇異的光芒。\n"                                
                                "當你打通十二重天達到天外天後，能借用該塔之力進入來世。\n" 
                                "*可用之神力進入輪回司中（use haotian ta）。\n"NOR);

        }
        setup();
}

void init()
{
        add_action("do_use", "use");       
}

int do_use(string arg)
{
        object me;
        
        me = this_player();
        
        if(! objectp(present("haotian ta", me)))return 0;
        
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");
        
        if( !query("outdoors", environment(me)) )
                 return notify_fail("你得先到戶外去。\n");
                 
        message_sort(HIM + "\n$N" HIM "祭起手中的昊天塔，猛然間，七色光芒自昊天塔中射"
                     "出，將$N卷了進去。\n" NOR, me);
                
        me->move("/kungfu/class/sky/lunhuisi");
        set("startroom", "/kungfu/class/sky/lunhuisi", me);
        destruct(this_object());

        return 1;
}
