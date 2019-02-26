#include <ansi.h>

inherit ITEM;

int do_use(string arg);

void create()
{
        set_name(NOR + YEL "童男童女符" NOR, ({"tntn fu", "fu"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + YEL "這是一張道符，上面畫着兩個小娃，一個男一個女，形態十分逼真。\n"
                                      "*在蛇精洞扔出此符（reng fu）可引出蛇精。\n\n" NOR);
                set("unit", "張");
                set("value", 8000);
        }
}

int query_autoload()
{
        return 1;
}


void init()
{
        add_action("do_use", "reng");       
}

int do_use(string arg)
{
        object me, ob;
        
        me = this_player();
        
        if(! objectp(present("tntn fu", me)))return 0;
        
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");
                 
        ob = environment(me);
        
        if (base_name(ob) != "/d/shenlong/shejingdong")
                return notify_fail("此符只能在蛇精洞使用。\n");

        ob = find_living("jiutou shejing");
        
        if (objectp(ob) && environment(ob))
        {
                if (base_name(environment(ob)) == "/d/shenlong/shejingdong")
                        return notify_fail("蛇精已經出現了，不需要再使用符。\n");
        }

        // 正在清場則不能扔
        ob = environment(me);
        if( query("doing", ob) )
        {
                return notify_fail("這裏剛戰鬥完，正在清場，你還是等下次吧！\n");
        }
        
        // 使用描述
        message_sort(HIY + "\n$N" HIY "扔出童男童女符，猛然間，地動山搖，遠處傳來嗖~~嗖"
                     "聲，似乎是蛇精在朝這邊移動，一時間，空氣幾乎凝固 ……\n" NOR, me);

        me->start_busy(5);
        
        // 召喚出九頭蛇精
        remove_call_out("summon_shejing");
        call_out("summon_shejing", 5, me);



        return 1;
}

void summon_shejing(object me)
{
        object ob;
        
        ob = find_living("jiutou shejing");
        
        if (objectp(ob) && environment(ob))
        {
                if (base_name(environment(ob)) == "/d/shenlong/shejingdong")
                {
                        write("蛇精已經出現了，不需要再使用符，你趕緊將符收起。\n");
                        return;                        
                }
        }        

        ob = new("/d/shenlong/npc/shejing");
        
        message_sort(HIR + "\n猛然間，一陣攝人心魄的叫聲打破了寂靜，只見一隻巨大的毒蛇出現在"
                           "蛇精洞內，此蛇已化身人形，修煉成精，有九頭，形狀甚是可怕。\n" NOR, me);
        
        ob->move("/d/shenlong/shejingdong");
        set("life_time", time(), ob);
        
        // 摧毀符
        destruct(this_object());
        
        return;        
}
