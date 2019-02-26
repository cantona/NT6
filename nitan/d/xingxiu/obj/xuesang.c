// Code of ShenZhou
// xuesang.c  
// By Haowen 1/14/98

#include <ansi.h>

inherit ITEM;


void create()
{
        set_name("雪桑",({"xue sang","sang"}));
        set_weight(900000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一棵天山特有的生長在雪峯的雪桑樹。
傳説有一種雪蠶最喜歡生長在這雪桑之上，經常有人來尋找(xunzhao) \n");
                set("unit", "棵");
                set("value", 8);
                set("no_get", 1);
                set("leaves",20);
       }
       
        setup();
}

void init()
{
        add_action("do_search", "search");
        add_action("do_search", "xunzhao");
        add_action("do_feed", "fed");
        add_action("do_look", "look");
        add_action("do_look", "l");
}

int do_search()
{
object obj=this_object(),me=this_player();

if( query_temp("find_can", me) )
        return notify_fail("雪蠶已經在雪桑上了，你還找什麼呀？\n");

if( random(query("kar", me))>15 )
        {
        tell_object(me,HIG"你仔細的翻動雪桑葉，到處尋找起來。\n" NOR);
        if(random(10)>5)
                {
                tell_object(me,HIR"你忽然眼前一亮，一條晶瑩雪白的雪蠶(can)正卧在一片雪桑葉上！\n"NOR);
                set_temp("find_can", 1, me);
                }
        addn("neili", -10, me);
        return 1;
        }
else    {
        addn("neili", -10, me);
        return notify_fail("你找了半天什麼也沒找到！\n");
        }
}

int do_feed(string arg)
{
object ob,obj=this_object(),me=this_player();
string what;

//message_vision(arg);
if (!arg || sscanf(arg,"%s",what)!=1)
        return notify_fail("你要喂什麼？\n");

if (what!="can")
        return notify_fail("這裏的雪桑葉只有天山雪蠶愛吃！\n");

if( !query_temp("find_can", me) )
        return notify_fail("這雪桑上什麼也沒有，你要喂什麼？\n");

if( query_temp("get_si", me) )
        return notify_fail("雪蠶剛吐過絲，恐怕現在不會再吐了！\n");

if( query("leaves", obj)>1 )
        {
        tell_object(me,HIY "你摘了一片雪桑葉餵給雪蠶吃。雪蠶仔細的吃了起來。\n" NOR);
        set("leaves",query("leaves",  obj)-1, obj);
                if (random(10)>5)
                        {
                        tell_object(me,HIY "雪蠶吃完了桑葉，頭一昂，吐出一根蠶絲，你趕緊用手接住。\n" NOR);
                        set_temp("get_si", 1, me);
                        ob=new("/d/xingxiu/obj/xuecan-si");
                        ob->move(me);
                        }
        return 1;}
else 
        {
        call_out("grow",200,obj);
        return notify_fail("雪桑上的葉子都摘完了，等慢慢長出來再來喂吧！\n");
        }
}

int do_look(string arg)
{
        object ob,me=this_player();
        string what;
        ob=this_object();
 
        if( !arg || arg == "" || sscanf(arg,"%s",what)!=1) return 0;

        
        if(what=="sang" || what=="xue sang")
                {        
                if( query_temp("find_can", me) )
                        tell_object(me,query("long", ob)+"現在上面有一隻雪蠶(can)！好像正在等你喂(fed)它。\n");
                else tell_object(me,query("long", ob));
                return 1;
                }

return 0;

}

int grow(object ob)
{
        message_vision(HIG "雪桑上的桑葉又長出來了！\n");
        set("leaves", 20, ob);
}