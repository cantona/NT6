#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "諸神仙洞");
        set("long", @LONG
舉目四望，周圍盡是懸崖峭壁(bi)，猛一抬頭看見洞口上寫着「
諸神仙洞」四個大字。但是字體經過風雨的沖蝕已經磨損，周圍野草
雜生，心中悲涼不已。
LONG );
        set("item_desc",([
               "bi" :   "光突突的峭壁上垂下數根長騰(teng)。\n",  
               "teng" : YEL "看來很結實，可做攀爬之用。\n" NOR,
        ]));

        set("exits",([
               "enter":__DIR__"inzhushendong",
        ]));        
                     
       setup();
}

void init()
{              
        add_action("do_climb",({"climb","pa"}));
        
}

int do_climb(string arg)
{
        object me, here, shilin;
        string msg;
        int qi;

        me = this_player();
        qi=query("qi", me);
        
        if (! arg || arg != "teng")
                return notify_fail("你想往哪兒爬？\n");
        
        if ( !here = find_object(__DIR__"outzhushendong"))
                here = load_object(__DIR__"outzhushendong");
        if ( !shilin = find_object(__DIR__"shilinfeng"))
                shilin =load_object(__DIR__"shilinfeng");

               msg = HIG "\n$N" HIG "拉着樹藤往峭壁上爬去。\n"NOR;
        
               if(qi < 100)
        {
                msg += HIM "\n$N" HIM "體力不知，從峭壁上摔了下來。\n" NOR;
                message_vision(msg, me);
                me->unconcious();
                return 1;
        }
        message_vision(msg, me);
        message("vision",HIG "\n"+me->name()+"從峭壁下面爬了上來。\n", shilin, me);
        me->move(shilin);

        return 1;

}