#include <ansi.h>
inherit ROOM;

string look_wall();
string look_net();

void create()
{
        set("short","芙蓉洞");
        set("long", @LONG
一進入洞中，陽光便射在頭頂上，舉目一望，原來洞頂有一個小
洞，陽光便是從中射進來的，一看四周，這裡長滿了芙蓉花，正由于
上面的小洞(dong)才使這些花不至于枯死也有充足的陽光照射。不遠
處石壁(wall)上布滿了蜘蛛網，看來這裡的主人已經很久沒有來了。
想到這裡不禁蒼涼之意頓起：「芙蓉花開時，不見主人歸」。
LONG );
   
        set("exits",([
                "out" : __DIR__"furong",
        ]));        

        set("item_desc",([
                "wall"  : (: look_wall :),
                "net"   : (: look_net :),

                "dong"  : HIY "陽光從洞外射進來，四周怪石(stone)突出，似乎可"
                          "以從這裡爬(climb)上去。\n" NOR,

                "stone" : "只見這些突石有的堅韌如刀，有的層錯如梯，各顯其異。\n"
        ]));

        setup();
}        

void init()
{       
        add_action("do_pull", "pull");
        add_action("do_think", "think");
        add_action("do_climb", "climb");
}

int do_pull(string arg)
{
        object here;
 
        if (! here = find_object(__DIR__"furong1"))
                here = load_object(__DIR__"furong1");

               if (! arg || arg != "net")
        {
                write("你要拉什麼？\n");
                return 1;
        }

        if( query_temp("marks/拉", here) )
        {
                write("蜘蛛網已經被拉破了。\n");
                return 1;        
        }
    
        write(HIC "\n你把蜘蛛網拉了下來。\n" NOR);
        set_temp("marks/拉", 1, here);

        return 1;
}

int do_think(string arg)
{
        object here, me = this_player();
        int add;

        if (! here = find_object(__DIR__"furong1"))
                here = load_object(__DIR__"furong1");

        if( query("special_skill/clever", me) )
                add = me->query_int() * 4;
        else
                add = me->query_int() * 3;

        if( !query_temp("marks/拉", here) )
                return notify_fail("什麼？\n");

        if (! living(me) || arg != "wall")
                return notify_fail("你要參悟什麼？\n");

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你現在正忙著呢。\n");

        if ((int)me->query_skill("sword", 1) < 30)
                return notify_fail("你的基本劍法火候不夠，無法領悟石壁"
                                   "上的劍法。\n");

        /*
        if ((int)me->query_skill("furong-jian", 1) < 20)
                return notify_fail("你發現牆上所記載的劍法過于深奧，自"
                                   "己一時難以領會。\n");
        */

        if ((int)me->query_skill("furong-jian", 1) > 120)
                return notify_fail("你發現牆上所記載的劍法過于膚淺，自"
                                   "己無法領會到任何東西。\n");

        if( query("jing", me)<25 )
                return notify_fail("你現在精神不濟，過于疲倦，還是休息"
                                   "一會吧。\n");

        me->receive_damage("jing", 20);

        if (me->can_improve_skill("furong-jian"))
                me->improve_skill("furong-jian", add);

        me->start_busy(random(2));
        message_vision(HIY "\n$N" HIY "聚精會神的參詳牆上所記載的劍法，"
                       "似有所悟。\n" NOR, me);
        write(HIC "你對「芙蓉劍法」有了新的領悟。\n" NOR);
        return 1;
}

string look_wall()
{
        object here, me = this_player();
        string msg;

        if (! here = find_object(__DIR__"furong1"))
                here = load_object(__DIR__"furong1");

        if( query_temp("marks/拉", here) )
        {
                message_sort(HIG "\n你走到石壁前，抹去上面多年來積蓄的灰"
                             "塵，發現上面所刻的竟是一套劍法。這些全部都"
                             "是用利器所刻，當可見當初刻繪之人功力深厚，"
                             "用心良苦。你不禁對這位前輩心生敬仰之情。只"
                             "見壁上全是一個個小人，每個人都使出不同的招"
                             "式，劍法精妙令人折服。\n" NOR, me);

                write(WHT @TEXT

  □□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
  □                                                 ****** □
  □   ●>        ●       ●        ●       ●     * 芙 * □
  □   \ __    □v|\     \//>□    \//\__   □v|^    * 蓉 * □
  □   /<        /<       />             />        /<     * 劍 * □
  □                                                     * 法 * □
  □                                                     ****** □
  □□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
                                                             
TEXT NOR);
                return "\n";
         }

         msg = WHT "\n石壁上面布滿了蜘蛛網(net)，顯然很久沒有人來過這裡"
               "了。\n看到此處，你心中悲涼之意頓起！\n" NOR;

         return msg;
}

string look_net()
{
        object me = this_player();
        object here;
        string msg;

        if (! here = find_object(__DIR__"furong1"))
                here = load_object(__DIR__"furong1");

        if( query_temp("marks/拉", here) )
                return "一張被拉破的蜘蛛網懸在半空。\n";

        msg = WHT "\n你走進細看，石壁上幾只蜘蛛還在不停地吐絲織網，透過"
              "蛛網\n竟能隱約看見石壁上殘留的一些文字。你不禁想拉開(pul"
              "l)蛛\n網看個究竟。\n" NOR;

        return  msg;
}

int do_climb(string arg)
{        
        object me = this_player();

          if (! arg || arg != "stone")
                return notify_fail("你想爬什麼？\n");

        write(HIG "\n你踩著洞中突出的石頭上，很快爬出了洞口。\n\n" NOR);

        me->move(__DIR__"furongfeng");
           
        return 1;
}