//Cracked by Roath
inherit ITEM;
#include <ansi.h>
void setup()
{}

void init()
{
        add_action("do_make", "make");
}

void create()
{
        set_name("硫磺" NOR, ({"liu huang", "sulphur", "huang"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", "一塊硫磺，通常用來製作火藥。\n");
                set("value", 200);
        }
}

int do_make(string arg)
{
        object  ob, *obj, me = this_player();
        int i;
        if( !arg || arg!="lianxin dan" )
                return notify_fail("你要做什麼？\n");
        if( me->query_skill("poison", 1) < 120)
                return notify_fail("你的毒技火侯不夠，不能製作煉心彈。\n");
        if(! present("wugong ke", me) && !present("xiezi ke", me)
        && !present("shedan", me) && !present("du zhusi", me)
        && !present("shachong ke", me))
                return notify_fail("你沒有足夠的原料！\n");
        message_vision(CYN"$N小心翼翼地把一塊毒藥和硫磺放在一起，注進內力，捏成了一顆煉心彈。\n"NOR, me );
                ob = new("/d/xingxiu/obj/lianxin.c");
                ob->move(me);
        obj = all_inventory(me);
        for(i=sizeof(obj)-1; i>=0; i--) {
        if( query("name", obj[i]) == "蜈蚣殼" || query("id", obj[i]) == "xiezike"
         || query("id", obj[i]) == "shedan" || query("id", obj[i]) == "duzhusi"
         || query("id", obj[i]) == "shachongke" )
        destruct(obj[i]);
        }
                destruct(this_object());
        return 1;
}