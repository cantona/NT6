//Room: ssyb.c 舍身崖壁

inherit ROOM;

#include <ansi.h>

void create()
{
      set("short","舍身崖壁");
        set("long", @LONG
你終于遊到崖壁。抬頭上望，微見天光。壁面潮濕，裂縫中微有
水滲出。腳下是污濁的臭水，旁邊不遠出有一個墳墓(fenmu)， 向東
就是你來時的水潭。
LONG );
      set("outdoors", "emei");
      set("objects", ([
          __DIR__"npc/frog" : 1 + random(3),
      ]) );

         set("exits",  ([
                 "east" : __DIR__"st0",
         ]));
      set("item_desc", ([
            "fenmu" : NOR + WHT "看來這個墳墓已經在這裡很久了，上面已長滿了青苔，令人一看不禁"
                      "滄然之意頓生。\n" NOR,
      ]));
      set("no_clean_up", 0);
      set("no_fight", 1);
      setup();
}

void init()
{
    add_action("do_climb", "climb");
    add_action("do_bai", "bai");
}

int do_climb()
{
    object me;
    me = this_player();
    message("vision", me->name()+"使勁爬上去，花了九牛二虎之力。\n", environment(me), ({me}) );
    me->move(__DIR__"gudelin1");
    message("vision", me->name()+"花了九牛二虎之力，到了這個地方，卻不知道在哪裡？\n", environment(me), ({me}) );

    return 1;
}

int do_bai(string arg)
{
     object book;

                 object me = this_player();
     if (! arg || arg != "fenmu")
            return 0;
     if (me->is_busy() || me->is_fighting())
     {
            write("你忙完了再說吧！\n");
            return 1;
     }
     if( query("jing", me)<130 )
     {
            write("你精力不足！\n");
            return 1;
     }
     if( query("jing", me)>200)addn("jing", -120, me);
     else set("jing", 1, me);

     write(HIG "你心中滄然之意油然而生 ……\n" NOR);
     write(HIG "你走向墳墓，抹去上面的青苔，跪在地上磕了三個頭。\n" NOR);
     me->start_busy(2 + random(2));
     if (this_player()->query_skill("shaolin-jiuyang", 1) < 180
        || this_player()->query_skill("wudang-jiuyang", 1) < 180)
     {
             write(HIG "你忽然覺得深潭底寒冷無比，心想還是趕快離開為好。\n" NOR);
             return 1;      
     }

     if (random(500) != 1)
     {
             write(HIG "磕頭完畢，你緩緩站起身來。默默地注視著墳墓，不禁思緒萬千。\n" NOR);
             return 1;
     }

     write(HIG "猛然間你覺得一個硬硬的東西碰在頭上，于是你猛地挖開墳墓 ……\n" NOR);
     write(HIG "一個木盒出現在你眼前，你趕忙打開木盒，「嗖」地一聲！一枚暗器從中飛出……\n" NOR);
     if (this_player()->query_skill("dodge", 1) < 220 || 
         this_player()->query_skill("martial-cognize", 1) < 220)
     {
          write(HIG "你閃躲不及，暗器從你胸口穿過！\n" NOR);
          this_player()->unconcious();
     }
     write(HIG "你早在打開盒子之前就已料到其中定藏有暗器，所以你從容不迫地躲了過去！\n" NOR);
     if (! book = find_object("/clone/lonely/book/emeijy-book"))
           book = load_object("/clone/lonely/book/emeijy-book");
     if (environment(book))
     {
          write(HIG "你回頭一看，卻發現盒子是空的！\n" NOR);
          return 1;
     }
     write(HIG "你趕忙將盒子裡的東西拿了出來。\n" NOR);
     book->move(this_player());
     return 1;
                  
}