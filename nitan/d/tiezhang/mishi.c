// Room: /u/zqb/tiezhang/mishi.c

inherit ROOM;
#include <ansi.h>
void init();
void create()
{
        set("short", HIY"密室"NOR);
        set("long", @LONG
    這是瀑布後面的一間密室，地下塵土堆積，顯是長時間無人到來，
正中孤零零的擺著一張石幾，幾上有一只兩尺見方的石盒(he)，盒口貼了封
條，此外再無別物。
LONG        );
        set("exits", ([ 
        "out" : __DIR__"hhyuan-3",
        ]));

        set("item_desc", ([ 
        "he" : "一個四四方方的石盒，上面落滿了塵土。\n",
        ]));
        set("no_clean_up", 0);

        setup();
}

void init()
{
        
        object me = this_player();
        
        if((int)me->query_skill("dodge",1) <= 30) 
        {
                me->receive_damage("qi", 50);
                me->receive_wound("qi",  50);
                message_vision(HIR"$N只覺得被瀑布沖得左搖右晃，難以站穩，身體不由自主的摔出瀑布之外！\n"NOR, me);
                me->move(__DIR__"hhyuan-3");
                tell_object(me, HIR"你從瀑布中摔了出來，只覺得渾身無處不疼，還受了幾處傷。\n"NOR);
                message("vision",HIR"只見"+query("name", me)+"從瀑布中摔了出來，躺在地上半天爬不起來！\n"NOR,environment(me),me);
        }

        add_action("do_open","open");
}

int do_open(string arg)
{
        object me = this_player();
        object ob;

       
    if (!arg || (arg != "he" && arg != "shi he"))
       {
        return notify_fail("你想打開什麼？\n");
        return 1;
       }
    else
    {
    if (!present("tiezhang zhangpu",me))
       {
        write("你用力打開石盒，發現裡面有一本落滿塵土的書籍。你急忙把它撿起揣在懷中。\n");
        ob=new("/d/tiezhang/obj/zhangpu");
        ob->move(me);
        return 1;
       }
        write("你用力打開石盒，發現裡面空空的什麼也沒有。\n");
        return 1;
    }
}
