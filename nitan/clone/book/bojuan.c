// bojuan.c

#include <ansi.h>
inherit ITEM;
inherit F_UNIQUE;
int do_study(string arg);

void init()
{
        add_action("do_study", "yanxi");        
}
void create()
{
        set_name("帛卷", ({ "bo juan", "bo", "juan" }));
        set_weight(50);
        set("no_drop", "這樣東西不能離開你。\n");
        set("unit", "卷");
        set("long", "這是一卷帛卷，裡面寫著 ：\n莊子“逍遙遊”有雲：窮發之北有冥海者，天池也。有魚焉，其廣數千裡。。。。\n似乎你通過(yanxi)會有所領悟.\n");
        set("value", 500);
        set("material", "silk");
        setup();
}


int do_study(string arg)
{
        object me = this_player();
        int cost=10,myskill;        

        if ( arg != "bo" && arg != "juan" && arg !="bo juan" )
                return notify_fail("你要讀什麼？\n");
        if( query("jing", me)<25 )
        {
                write("你現在過于疲倦，無法專心下來研讀新知。\n");
                return 1;
        }
        if (me->is_busy()) return notify_fail("你現在正忙著呢。\n");
        if( query("family", me) == 0 || query("family", me)["family_name"] != "逍遙派" )
                return notify_fail("想學更高深的北冥神功，必須加入我逍遙派。\n");
        if ( me->is_fighter()) return notify_fail("戰鬥中無法閱讀新知！\n");

        if ( (int)me->query_skill("beiming-shengong",1) >= 20 &&
                (int)me->query_skill("beiming-shengong",1) <= 100 )
        {
            if( query("jing", me)>cost )
                       { myskill=(int)me->query_skill("beiming-shengong",1);
                         if( myskill*myskill*myskill/10>query("combat_exp", me) )
                   {  return notify_fail("也許是缺乏實戰經驗，你對帛卷上所說的東西總是無法領會!\n");
                    }
                        else  
                      { me->receive_damage("jing", 20);
                        me->improve_skill("beiming-shengong",(me->query_skill("beiming-shengong",1)+query("int", me)));
                        message_vision("$N正在專心研讀北冥神功心法。\n", me);
                        return 1;
                       }
                }
            else
                {
                        cost=query("jing", me);
                        write("你現在過于疲倦，無法專心下來研讀北冥神功心法。\n");
                }
        }
        if ((int)me->query_skill("beiming-shengong",1) > 100 )
        {
                return notify_fail("你對著帛卷看來看去，無法從中領悟出更高深的道理。\n");
        }
        return notify_fail("你對著帛卷看來看去，沒看出什麼道理出來。\n");
}

