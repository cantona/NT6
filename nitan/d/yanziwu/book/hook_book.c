// hook_book.c
#include <ansi.h>
inherit ITEM;
int do_study(string arg);
void init()
{
        add_action("do_study","kan");
}
void create()
{
        set_name(HIM"慕容世家"HIG"短兵篇"HIC"鉤章"NOR, ({"hook book","book"}));
        set_weight(500);
        set("unit", "冊");
        set("long","這是慕容世家的藏書中的"HIG"短兵篇"NOR"之"HIC"鉤章"NOR"，包含了普天下所有門派的鉤法精要。\n想修絕世武功，就好好看(kan)吧。\n");
        set("value", 1);
        set("material", "paper");
        setup();
}
int do_study(string arg)
{
        object me = this_player();
        int level = me->query_skill("hook",1);
        if (me->query_skill("shenyuan-gong",1) < 20)
                return notify_fail("你的神元功未入門，無法從書上學到什麼。\n");
        if ( (arg != "book") && (arg != "hook book"))
                return notify_fail("你要學什麼？\n");
        if (level >= 150)
                return notify_fail("你研讀了一會兒，但是發現上面所說的對你而言都太淺了，沒有學到任何東西。\n");
        if (level <= 50)
                return notify_fail("你研讀了一會兒，但是發現上面所說的對你而言都太深奧了，毫無收獲。\n");
        if( query("combat_exp", me)<(level*level*level/10) )
                return notify_fail("你的實戰經驗不足，再怎麼讀也沒用。\n");
        if( query("jing", me)<25 )
                return notify_fail("你現在過于疲倦，無法專心下來研讀新知。\n");
        me->receive_damage("jing", 25);
        me->improve_skill("hook", (int)me->query_skill("literate",1)/5+1); 
        write("你研讀了有關基本鉤法的技巧，似乎有點心得。\n");
        return 1;
}
