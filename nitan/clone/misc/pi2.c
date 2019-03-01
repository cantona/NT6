// pi.c 絆人摔跤的西瓜皮
// By Alf, Last Update 2002.0915

#include <ansi.h>
inherit ITEM;

void create()
{
    set_name(HIY"西瓜皮"NOR,({"xigua pi","pi"}));
    set_weight(200);
    if(clonep())
        set_default_object(__FILE__);
    else
    {
        set("unit","塊");
        set("long","一塊西瓜皮。\n");
        set("no_get","一塊西瓜皮，都給人踩爛了，你也不嫌惡心？\n");
        set("value",1);
        set("env/invisible",1);
        set("pi_gone",10+random(10));
    }
    setup();
}
 

void init()
{
    int chance,age;
    object me,ob;
    string msg;
    me = this_player();
    ob = this_object();

    age=60-query("age", me);
    if (age < 0) age = 0;
    chance = (me->query_dex() + age)/2;
    
    if(interactive(me) && living(me) && random(chance) == 1) 
    {
        msg = HIY""+me->name()+"不小心踩在西瓜皮上，“咕咚”一聲摔了個大馬趴";
        me->start_busy(2);
        
        if( query("pi_gone", ob) <= 0 )
        {
            msg += "，西瓜皮卻不知飛哪去了。\n";
            tell_room(environment(me),msg);
            destruct(ob);
        }
        else
        {
            set("long", "一塊西瓜皮，不知道是誰丟的。\n", ob);
            set("env/invisible", 0, ob);
            addn("pi_gone", -1, ob);
            msg += "。\n"+me->name()+"站起身來，拍了拍屁股，一臉的殺氣：“奶奶的到底是誰幹的？”\n"NOR;
            tell_room(environment(me),msg);
        }
    }
}
