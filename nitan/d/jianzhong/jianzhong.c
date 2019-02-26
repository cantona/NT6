#include <ansi.h>
inherit ROOM;
void create()
{
        set("short","劍冢");
        set("long",@LONG
平台上大石「劍冢」兩個大字之旁，尚有兩行字體較小的石刻：
        「劍魔獨孤求敗既無敵於天下，乃埋劍於斯。
          嗚呼！羣雄束手，長劍空利，不亦悲夫！」
大石之下，許多石塊堆着一個大墳，背向山谷，俯仰空闊，佔盡了
形勢。想劍魔文武全才，抱負非常，但恨生得晚了，無緣得見這位
前輩英雄，你不禁仰天長歎，豪情萬千。
LONG
        );
        set("no_clean_up",1);
        set("move_stone",1);
        set("outdoors", "jianzhong");
        set("exits", ([
                "enter" : "/d/huashan/s",
        ]));
        set("coor/x", -401);
        set("coor/y", -421);
        set("coor/z", 50);
        setup();
}
void init()
{
        add_action("do_move","move");
        add_action("do_move","ban");
        add_action("do_climb","climb");
}
int do_move(string arg)
{
        object me,room,ob,ob1,ob2,ob3;
        me=this_player();
        room=this_object();
        if((arg!="stone")&&(arg!="石塊"))
        {        
                return notify_fail("你要搬什麼？\n");
        }        else        
        {
                if( !query("move_stone", room) )
                        return notify_fail("石塊已被人搬開了！\n");
                message_vision("$N搬開了冢上的石塊，露出了並列的三柄長劍，在第一、二把長劍\n之間，另有一塊長石條片。三把劍和石片並列於一塊大青石之上。\n",me);
                set("move_stone", 0, room);
                ob=new(WEAPON_DIR"treasure/qingguang-jian");
                if ( ob->violate_unique() ) destruct( ob );
                else ob->move(room);
                ob1=new("/clone/book/shipian");
                if ( ob1->violate_unique() ) destruct( ob1 );
                else ob1->move(room);
                ob2=new(WEAPON_DIR"treasure/xuantie-jian");
                if ( ob2->violate_unique() ) destruct( ob2 );
                else ob2->move(room);
                ob3=new(__DIR__"obj/mujian");
                ob3->move(room);
        }        
        return 1;
}
int do_climb(string arg)
{
        object me;
        me=this_player();
        if(arg!="down")        return notify_fail("你要往哪兒爬？\n");
        message_vision("$N順着來路爬了下去。\n",me);
        me->move(__DIR__"qiaobi");
        message_vision("$N從「劍冢」上爬了下來。\n",me);
        return 1;
}

int valid_leave(object me, string dir)
{

        if (dir == "enter")
        {
                write(HIG "\n你進入山洞，只覺四周漆黑一片，你一直不停地往前走… \n" NOR);
                write(HIG "不久，穿過了山洞，只見前方卻是懸崖峭壁。\n\n");
        }
        
        return 1;
}
