#include <ansi.h>;
#include "/d/tangmen/npc/job1.h";

void create()
{
        set("short", "客店");
        set("long",
"這是唐門所開的客棧，生意非常興隆。外地遊客多選擇這裏落腳，唐\n"
"門弟子可以自由的進出，睡覺也是免費的。唐小二里裏外外忙得團團轉，\n"
"接待來自五湖四海的朋友。客店的主人從不露面，他究竟是誰，有各種各\n"
"樣的猜測。不過有點是所有來過的人都知道的：這兒是唐門的地盤，容不\n"
"得外姓人在此胡作非為。\n"
);
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room", 1);
        set("item_desc", ([
                "paizi" : "。\n",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
        set("exits", ([
                "west" : __DIR__"bdajie1",
                "up"   : __DIR__"kedian2",
        ]));

        setup();
        
}

int valid_leave(object me, string dir)
{          
        object ob;
        mapping myfam;

        if( !query_temp("rent_paid", me) && dir == "up" )
                return notify_fail("唐小二一下擋在樓梯前，白眼一翻：怎麼着，想白住啊！這裏可是"+HIC"蜀中唐門"NOR+"啊\n");

        if( query_temp("rent_paid", me) && dir == "west" )
        {     
                myfam=query("family", me);
                if (myfam["family_name"] != "唐門世家")
                        return notify_fail("唐小二跑到門邊攔住：客官已經付了銀子，怎麼不住店就走了呢！旁人還以為小店伺候不周呢！\n");
                delete_temp("rent_paid", me);
                me->move("/d/tangmen/bdajie1");
                tell_object(me,"唐小二笑咪咪地説道：這位"+RANK_D->query_respect(ob)+"，歡迎再來"+HIG"唐門客店"NOR+"\n\n");
                return 1;
        }
        return ::valid_leave(me, dir);
}

