#include <ansi.h>

inherit ROOM;

void create()
{
        set("short","懸崖底");
        
        set("long", @LONG
這裏是衡山懸崖底，四周都被懸崖絕壁包圍着，舉目一望，只見
雲霧深鎖，崖壁陡峭，直沒天際，幾隻老鷹在上空不斷的盤旋。絕壁
上垂下幾根樹藤(teng)，看來可以順着這裏爬上崖頂。聳立在你面前
是一棵巨大的古樹(tree)，剛才你幸好抓住了這棵樹的樹枝，不然早
就粉身碎骨了。你到處看了看，這裏似乎沒有其他路可走。
LONG );

        set("item_desc",([
              "teng": HIG "\n這根樹藤看起來很結實，可以用它爬(climb)上懸崖。\n" NOR,
              "tree": YEL "\n參天古樹，樹幹粗大結實，但是有根樹枝已經被折斷了。\n" NOR,
        ]));        
           
        set("objects",([
              "/clone/quarry/tu" : 7,        
        ]));

        set("outdoors","henshan");

        setup();
}


void init()
{              
        add_action("do_climb",({"climb","pa"}));
        
}

int do_climb(string arg)
{
        object me, here, zigai;
        string msg;
        int qi;

        me = this_player();
        qi=query("qi", me);
        
        if (! arg || (arg != "teng" && arg != "tree"))
                return notify_fail("你想往哪兒爬？\n");
        
        if ( !here = find_object(__DIR__"xuanyandi"))
                here = load_object(__DIR__"xuanyadi");
        if ( !zigai = find_object(__DIR__"zigai"))
                zigai=load_object(__DIR__"zigai");

        if ( arg == "teng")
        {
                 msg = HIG "\n$N" HIG "拉着樹藤往峭壁上爬去。\n"NOR;
        
                if(qi < 100)
                {
                        msg += HIM "\n$N " HIM "體力不知，從峭壁上摔了下來。\n" NOR;
                        message_vision(msg, me);
                        me->unconcious();
                        return 1;
                }

                message_vision(msg, me);
                message("vision",HIG "\n"+me->name()+"從峭壁下面爬了上來。\n", zigai, me);
                me->move(zigai);

                return 1;

        }

        me->move(__DIR__"ontree");

        return 1; 
        
}

