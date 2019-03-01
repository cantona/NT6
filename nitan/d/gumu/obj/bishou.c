// Room: /d/gumu/obj/bishou.c匕首
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>
inherit ITEM;
void create()
{
        set_name( "匕首" , ({ "bi shou", "blade", "bishou" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把邊緣鋒利的匕首，好象可以斬(zhan)東西。\n");
                set("value", 0);
                set("material", "iron");
        }
        setup();
}

void init()
{
        add_action("mark_success", ({"zhan", "斬"}));
}

int mark_success(string arg)
{
        object target, ob,name1, me = this_player();

        name1=query("id", me);
        if(!arg) return notify_fail("你要斬什麼？\n");  
        target = present(arg, environment(me));  
        if(!target)
                return notify_fail("找不到這個東西。\n");
        if(!target->is_corpse())
                return notify_fail("看清楚點，那不是屍體。\n");
        if( query("no_head", target) )
                return notify_fail("那具屍體已經沒有首級了。\n");
        if(!target->is_character())
                return notify_fail("那具屍體已經腐爛了。\n");
        message_vision(HIR"$N揚起匕首 ，對準$n的脖子處猛地斬了下去！\n"NOR, me, target);
        ob=new("/d/gumu/obj/head");
        ob->set_name(query("victim_name", target)+"的首級",({"head"}));
        set("long", "這是一顆"+query("victim_name", target)+"的首級。\n", ob);
        if( query("victim_user", target) )
        set("victim_user", 1, ob);
        if( query("kill_by", target) )
        set("kill_by",query("kill_by",  target), ob);
        delete("kill_by", target);
        message_vision(HIR"$N將$n斬了下來，提在手中。\n"NOR, me, ob);
        ob->move(me);
        set("name", "無頭屍體", target);
        set("no_head", 1, target);
        set("long", "一具無頭屍體，腐臭四溢，情狀可怖。\n", target);
        return 1;
}