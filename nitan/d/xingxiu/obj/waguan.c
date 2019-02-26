// This program is a part of NT MudLIB
//10/8/00
//Last Update by Scatter

inherit ITEM;
#include <ansi.h>

void setup() {}


void create()
{
        set_name("瓦罐", ({"wa guan", "wa", "guan"}));
        set_weight(15000);
        set_max_encumbrance(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", "一隻質地精細的瓦罐，不知道有什麼用途。\n");
                set("no_drop", 1);
                set("no_get", 1);
                set("no_steal", 1);
                set("no_sell", 1);
        }
        setup();
}

int is_container() { return 1; }

void init()
{
   add_action("do_hold", "kou");
   add_action("do_xiulian", "xiulian");
}

int do_hold(string arg)
{
        string what;

        object ob;
        object obj=this_object();
        object me=this_player();

        if( !arg || me != this_player(1))
                        return notify_fail("命令格式: kou <物品> 。\n");

        ob = present(arg, environment(me));
        if( !ob || !living(ob))
                return notify_fail("這裏沒有這個生物。\n");

        if( query("sub", ob) != "xx_job")return notify_fail("這東西最好不要抓。\n");

        if (this_player()->is_busy()) return notify_fail("你正忙着呢。\n");

        if( query_temp("hold", this_player()))return notify_fail("已經有毒蟲了，修煉吧。");

        if( query("playerid", ob) != query("id", this_player()) )
                return notify_fail("別人找出來的，你好意思抓嗎？:)\n");




        if( query("combat_exp", this_player())<10000 )
        {

        if(this_player()->query_skill("poison",1)*10 > random(this_player()->query_skill("force")*3)) {
                        message_vision(HIG"$N舉起手中的瓦罐猛地將"+query("name", ob)+"扣住，然後小心翼翼地將瓦罐翻起來蓋住。\n"NOR,this_player());
                        set("bug_hold",1);
                        set("count", random(10));
                        set("long","一隻質地精細的瓦罐。\n裏面盛着一隻"+query("name", ob)+"。\n");
                        set("xiulian", random(5));
                        set("bug_name",query("name", ob));
                        set_temp("bug_hold", 1, this_player());
                        set_temp("found", 1, this_player());
                        destruct(ob);
         }else message_vision("$N猛的出手用瓦罐扣向"+query("name", ob)+",但"+query("name", ob)+"機靈的跳開了。\n",this_player());

         }




         else
         {
         if(this_player()->query_skill("poison",1) > random(this_player()->query_skill("force")*3)) {
                        message_vision(HIG"$N舉起手中的瓦罐猛地將"+query("name", ob)+"扣住，然後小心翼翼地將瓦罐翻起來蓋住。\n"NOR,this_player());
                        set("bug_hold",1);
                        set("count", random(10));
                        set("long","一隻質地精細的瓦罐。\n裏面盛着一隻"+query("name", ob)+"。\n");
                        set("xiulian", random(5));
                        set("bug_name",query("name", ob));
                        set_temp("bug_hold", 1, this_player());
                        set_temp("found", 1, this_player());
                        destruct(ob);
         }else message_vision("$N猛的出手用瓦罐扣向"+query("name", ob)+",但"+query("name", ob)+"機靈的跳開了。\n",this_player());
         }






         addn("neili", -50, this_player());
         this_player()->start_busy(random(1)+1);
         return 1;

}

int do_xiulian()
{
        if(this_player()->is_busy()) return notify_fail("你正忙着呢。\n");
        if (query("bug_hold")!=1) return notify_fail("沒有毒蟲，你想要用空氣修行嗎？\n");
        message_vision(HIR"$N運起內力護住全身大穴，然後閉上眼睛將手指伸入瓦罐。\n"NOR, this_player());
        message_vision(HIR+query("bug_name")+"立刻咬住$N的手吸起血來。\n"NOR, this_player());
        call_out("do_xiulian2", 10, this_player());
        this_player()->start_busy(10);
        return 1;
}

void do_xiulian2(object me){
        object dan;
        message_vision("$N運功完畢，身子一震，慢慢地站了起來。\n",me);
        if (query("xiulian")<=0){
                dan=new("/d/xingxiu/obj/dudan");
                set("player",query("id",  this_player()), dan);
                message_vision(HIG+query("bug_name")+"將血吸完，肚子高高漲起，啪地一身掉進罐底，掙扎了幾下，死了。\n"NOR, this_player());
                message_vision("$N將死"+query("bug_name")+"拿出瓦罐，將其肚子剖開，拿出一粒腥如血的丹丸來。\n"NOR, this_player());
                if( query("combat_exp", me)<100000){
                     tell_object(this_player(),HIR"你中毒了！\n"NOR);
                     this_player()->affect_by("huadu_poison",
                              ([ "level" : me->query_skill("force")/3 + random(me->query_skill("force")/3),
                                 "id":query("id", me),
                                 "duration" :5 ]));
                }
                set_temp("found", 1, this_player());
                delete("bug_hold", this_object());
                set("long", "一隻質地精細的瓦罐。\n");
                dan->move(this_player());
        } else message_vision(HIR+query("bug_name")+"肚子高高漲起，啪地一身掉進罐底。\n"NOR, this_player());
        addn("xiulian",-1);
        if (this_player()->query_skill("poison",1)<420)
                this_player()->improve_skill("poison", this_player()->query_skill("feixing-shu",1));
}
