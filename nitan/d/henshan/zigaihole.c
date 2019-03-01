#include <ansi.h>

inherit ROOM;
string look_keng();
string look_desk();

#define ZHUJIAN    "/d/henshan/obj/zigai-book"

void create()
{
        set("short", "紫蓋仙洞");
        set("long", @LONG
這裡便是紫蓋仙洞。聽這裡的人說的由于這裡處于紫蓋峰下，峰
上融化的雪水便經過山澗匯如紫蓋仙洞中，但是這裡卻一點水也沒有，
耳邊卻傳來來淙淙的水流聲，你才發現雪水並不是匯直接流入洞中，
而是從洞壁上順勢向下流，經過一個較深的低窪地帶，積蓄起來，水
滿則溢，便形成了水蓮洞外的飛瀑。往光照來的的地方看去，已沒有
路可走，數丈遠處便是懸崖，原來這個洞竟生于一個峭壁之上。只見
不遠處擺著一個石桌(desk)，顯然這裡曾經有人來過。
LONG );
        
        set("item_desc",([
               "desk" : ( :look_desk: ),
               "keng" : ( :look_keng: ),
        ]));
        
        set("exits",([
                "north" : __DIR__"xuanya",
        ]));

        setup();

}


void init()
{       
        add_action("do_move", "move");
        add_action("do_pick", "pick");
}


int do_move(string arg)
{               
        object here;

        if (! here = find_object(__DIR__"zigaihole"))
                here = load_object(__DIR__"zigaihole");

        if (! arg || (arg != "desk" && arg != "石桌"))
                return notify_fail("你想移什麼？\n");
       
        if( query_temp("marks/移", here) )
        {
                write(HIG "\n你用力一推，將石桌移回了原處。\n\n" NOR);
                delete_temp("marks/移", here);
                return 1;
        }
        
        
        write(HIC "\n你用力一推，石桌下面竟露出一個坑(keng)來。\n\n"NOR);

        set_temp("marks/移", 1, here);
        return 1;
}

int do_pick(string arg)
{
        object here, book, me;

        me = this_player();

        if (! here = find_object(__DIR__"zigaihole"))
                here = load_object(__DIR__"zigaihole");

        if (! arg || (arg != "book"))
                return notify_fail("你要拿什麼？\n");
        
        if( query_temp("marks/拿", here) || !query_temp("marks/移", here) )
                return notify_fail("你要拿什麼？\n");

        // book = find_object(ZHUJIAN);
        book = new(ZHUJIAN);

        if (! book) book = load_object(ZHUJIAN);

        if (! environment(book))
        {
                set_temp("marks/拿", 1, here);
                book->move(me, 1);
                message_vision(HIC"$N"HIC"從坑中將"+query("name", book)+
                               HIC "拿了出來。\n" NOR, me);
                return 1;
        } else
                return notify_fail(YEL "這裡面什麼也沒有。\n" NOR);
        return 1;
}

string look_desk()
{  
       object here;
        
        if (! here = find_object(__DIR__"zigaihole"))
                here = load_object(__DIR__"zigaihole");

        if( query_temp("marks/移", here) )
                return WHT "\n石桌像是已被人推開，下面露出一個坑(keng)來。\n";
        else
   
                return WHT "\n一張石桌，上面已布滿了灰塵。\n";

       
}

string look_keng()
{
        object here, book;

        // book = find_object(ZHUJIAN);
        
        if (! here = find_object(__DIR__"zigaihole"))
                here = load_object(__DIR__"zigaihole");

        if( !query_temp("marks/移", here) )
                return "你要看什麼？\n\n";

        // if (! book) book = load_object(ZHUJIAN);

        // if (environment(book))
        if( query_temp("marks/拿", here) )
                return HIY "\n這個坑中像是藏東西的，但裡面空空如也，顯然裡面的東西已\n"
                           "被人拿走了。\n" NOR;

        return HIY "\n只見裡面放著一本(book)，你忍不住想拿(pick)來看看。\n" NOR;
           
}

void reset()
{
        object here;
        
        if (! here = find_object(__DIR__"zigaihole"))
                here = load_object(__DIR__"zigaihole");

        ::reset();

        delete_temp("marks/移", here);
        delete_temp("marks/拿", here);

        return ;

}