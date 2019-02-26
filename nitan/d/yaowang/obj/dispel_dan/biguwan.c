#include <ansi.h>
inherit ITEM;

void create()
{
     set_name(HIG"辟穀丸"NOR, ({ "bigu wan", "wan" })); set("unit", "顆");
        set("long", "一顆碧綠色的藥丸，。\n");
        set_weight(1000);
        set("yaowang", 1);
        set("no_get", 1);
        set("no_give", 1);
        set("no_sell", 1);
        set("no_drop", 1);
        set("value", 0);
        setup();
}

void init()
{
        object me, ob;
        int obj;

        me = this_player();
        ob = this_object();
        obj = (int)me->query_skill("medical",1);

        if( query_temp("liandan", me) == 1
                 && query("value", ob) == 0 )
        {
                if(obj<100) {
                        set("value", (random(2000)+2000), ob);}
                if(obj>=100 && obj<150) {
                        set("value", (random(4000)+4000), ob);}
                if(obj>=150 && obj<200) {
                        set("value", (random(8000)+7000), ob);}
                if(obj>=200 && obj<250) {
                        set("value", (random(15000)+15000), ob);}
                if(obj>=250) {
                        set("value", (random(20000)+30000), ob);
                        }
        }
        
        add_action("do_eat", "eat");
        add_action("do_eat", "chi");
}

int do_eat(string arg)
{
        object me = this_player();
        int i=query("value", this_object())/10;

        if (!id(arg))
                return notify_fail("你要吃什麼？\n");

        if (me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎着了。\n");

        if( query("food", me) >= ((query("str", me)*10)+100 )
                 && query("water", me) >= ((query("str", me)*10)+100) )
                return notify_fail("你似乎不餓啊？\n");

        addn("food", i, me);
        addn("water", i, me);
//      me->addn("neili", i);
        message_vision(HIG"$N服下一顆辟穀丸，頓覺一股清涼之氣從腹中升起。\n"NOR, me);
        destruct(this_object());
        return 1;
}
