// room: well1.c
// Jay 4/8/96

inherit ROOM;
#include <ansi.h>
#define THE_BOOK "/clone/book/lbook9"
int do_use(string arg);
int do_zuan(string arg);


void create()
{
        set("short", "暗室");
        set("long", @LONG
這是在高昌最深處的一個暗室，什麼也看不清。
LONG );
        set("exits", ([
                "out" : __DIR__"mishi2",
        ]));
        set("no_clean_up", 0);
                set("item_desc", ([
                                "hole" : "一個不知深淺的石洞，不知該不該搜一搜看。\n"
        ]));
        set("count",1);
        setup();
}

void init()
{
        add_action("do_use", "use");
        add_action("do_search", "search");
}

int do_use(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if (!present("fire", me))  return 0;
        if( arg=="fire" ) {
             message_vision("$N點燃了火折，發現牆壁上有一小洞(hole)，似乎有什麼東西在裡面。\n",me);
         set_temp("marks/fire", 1, me);
         return 1;
       }
}

int do_search(string arg)
{
      object me,ob;
      object book;
      object none;
      me = this_player();
      

                        if( !query_temp("marks/fire", me) )
                        return 0;
                        if (!arg || (arg!="hole" && arg!="小洞"))
                        return notify_fail("你要搜哪裡？\n");
                        if (query("count")<1)
                                {
                                        return notify_fail("洞裡面什麼也沒有了。\n");
                                        }
                        if( query("cor", me)<25 )
                                        return notify_fail("你剛想伸手，忽然有點害怕，想了想還是算了。\n");
                        addn("count",-1);
      book=new(THE_BOOK);
      if (book->violate_unique())
        {
                destruct(book);
                book=none;
        }
                        if (random(4)>0 && book)
                                {
                                        message_vision("$N往洞裡摸了摸，摸出一本古書來。\n",me);
                                         message("channel:rumor",MAG"【謠言】某人："+query("name", me)+"拿到一本"+query("name", book)+"啦。\n"NOR,users());
                                        book->move(me);
                                }
                        else if(random(4)>1)
                                {
                                        ob=new("clone/money/gold");
                                        ob->set_amount(random(30));
                                        message_vision("$N往洞裡摸了摸，摸出了一些黃金。\n",me);
                                        ob->move(me);
                                        }
                        else 
                                {
                                        ob=new("clone/money/silver");
                                        ob->set_amount(random(30));
                                        message_vision("$N往洞裡摸了摸，摸出了一些白銀。\n",me);
                                        ob->move(me);
                                        }
                        
      return 1;
}
