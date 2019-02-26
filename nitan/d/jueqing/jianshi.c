#include <ansi.h>

#define JUNZI   "/clone/lonely/junzijian"
#define SHUNV   "/clone/lonely/shunvjian"

inherit ROOM;

string look_hua();

void create()
{
        set("short", "劍室");
        set("long", @LONG
只見室中的壁上、桌上、架上、擺滿了各類兵刃，式樣繁
多，十之八九都是古劍，或長逾七尺，或短僅數寸，有的鐵斑
駁，有的寒光逼人，直看得人眼光撩亂。不遠處的牆壁上掛着
有一副古畫(hua)。
LONG);
        set("item_desc", ([
               "hua" : ( : look_hua :),
        ]));

        set("exits", ([
               "south" : __DIR__"houtang",
        ]));

        set("no_clean_up", 0);
        setup();
}

string look_hua()
{
      object ob, junzi, shunv;
      string msg;

      if (! ob = find_object(__DIR__"jianshi"))
              ob = load_object(__DIR__"jianshi");

      if( !query_temp("marks/拉", ob) )
              return HIW "古畫已經破舊不堪，畫中一對男女各持一柄無鋒之劍。\n" NOR;

      msg = HIY "畫已被人撕破。" NOR;

      junzi = find_object(JUNZI);
      shunv = find_object(SHUNV);


      if (! junzi) junzi = load_object(JUNZI);
      if (! shunv) shunv = load_object(SHUNV);

      if (! environment(junzi) && ! environment(shunv))    
      { 
              msg += HIY "但見畫後有二柄無鋒之劍，看上去像是一對。\n" NOR;
              return msg;          
      } else
      if (! environment(junzi) || ! environment(shunv))
      {
              msg += HIY "但見畫後有一柄鐵口斑駁，寒光逼人的寶劍。\n" NOR;
              return msg;
      }

      msg += HIY "畫後空空如也，什麼都沒有。\n" NOR;
      return msg;
}

void init()
{       
        add_action("do_pull", ({ "pull" }));
        add_action("do_pick", ({ "pick" }));
}

int do_pull(string arg)
{
        object me = this_player();
        object ob;

        if (! arg || arg != "hua")
                return notify_fail("你要做什麼？\n");

        if (! ob = find_object(__DIR__"jianshi"))
                ob = load_object(__DIR__"jianshi");

        if( query_temp("marks/拉", ob) )
        {
                write("畫已經被拉破了。\n");
                return 1;
        }

        message_vision(HIG "只聽見“咔嚓”一聲，$N " HIG "將牆上的畫"
                       "拉破了。\n" NOR, me);
        set_temp("marks/拉", 1, ob);

        return 1;
}

int do_pick(string arg)
{
        object ob,me;
        object junzi,shunv;

        me = this_player();

        if (! ob = find_object(__DIR__"jianshi"))
                ob = load_object(__DIR__"jianshi");

        if (! arg || (arg != "junzi jian" && arg != "shunv jian" ))
                return notify_fail("你要拿什麼？\n");
        
        if( query_temp("marks/君", ob) && query_temp("marks/女", ob )
             || !query_temp("marks/拉", ob) )
                return notify_fail("你要拿什麼？\n");

        junzi = find_object(JUNZI);
        shunv = find_object(SHUNV);

        if (! junzi) junzi = load_object(JUNZI);
        if (! shunv) shunv = load_object(SHUNV);

        if (arg == "junzi jian")
        {
                 if (! environment(junzi))
                 {
                         junzi->move(me, 1);
                         message_vision(HIC "$N" HIC "將牆上的「君子劍」"
                                        "取了下來。\n" NOR, me);
                         return 1;
                 } else
                         return notify_fail(NOR + YEL "君子劍已被拿走。\n" NOR);
        }   

        if (! environment(shunv))
        {
                shunv->move(me, 1);
                message_vision(HIC "$N" HIC "將牆上的「淑女劍」"
                               "取了下來。\n" NOR, me);
                return 1;
        } else
                return notify_fail(NOR + YEL "淑女劍已被拿走。\n" NOR);        

        return 1;
}