#include <ansi.h>
inherit ROOM;
void create()
{
        set("short","谷後樹林");
        set("long",@LONG
樹林裡鬱鬱蔥蔥，鳥語花香，光線從樹葉的縫隙中洒
向大地，微風吹來，樹影一陣婆娑。四周全是樹，一片綠
色，在碧綠的海洋中，你漸漸地迷失了方向。
LONG
        );
        set("exits",([
                "east":__FILE__,
                "west":__FILE__,
                "north":__FILE__,
                "south":__FILE__,
        ]));
        set("snake_count",5);
        set("outdoors", "jianzhong");
        set("coor/x", -400);
        set("coor/y", -420);
        set("coor/z", 0);
        setup();
}
void init()
{
        object ob1,ob2;
        object me=this_player();
        if( (random(10)<2) && (query("snake_count", this_object())>0) && (query_temp("dugu_visit", me) != 0) && (!present("pusi qushe",environment(this_player()))) )
        {        
                ob1=new(__DIR__"npc/pusiqushe");
                ob1->move(this_object());
                addn("snake_count", -1, this_object());
        }
}
int valid_leave(object me, string dir)
{
        int i;
        string msg;
        if( !query_temp("dugu_visit", me) )
        {
                if(dir=="north")
                {i=query_temp("zhongnan/tree", me);
                        if( (i>0) && (i<10))addn_temp("zhongnan/tree", -1, me);
                        if( (i>9) && (i<12))addn_temp("zhongnan/tree", 1, me);
                        if( i<0)set_temp("zhongnan/tree", 0, me);
                }
                if(dir=="south")
                {i=query_temp("zhongnan/tree", me);
                        if((i<4)||(i==14)) 
                       {        addn_temp("zhongnan/tree",1,me);} else addn_temp("zhongnan/tree",-1,me); 
                        if( i<0)set_temp("zhongnan/tree", 0, me);
                }
                if(dir=="east")
                {i=query_temp("zhongnan/tree", me);
                        if((i>3)&&(i<10))
                       {        addn_temp("zhongnan/tree",1,me);} else addn_temp("zhongnan/tree",-1,me); 
                        if( i<0)set_temp("zhongnan/tree", 0, me);
                }
                if(dir=="west")
                {i=query_temp("zhongnan/tree", me);
                        if((i>11)&&(i<14))
                                addn_temp("zhongnan/tree", 1, me);
                        if( i<0)set_temp("zhongnan/tree", 0, me);
                }
                if( query_temp("zhongnan/tree", me) >= 15 )
                 {
                                 me->move(__DIR__"donghou");
                           delete_temp("zhongnan/tree", me);
                        message("vision",query("name", me)+"一臉倦容地從樹林中鑽了出來。\n",environment(me),me);
                             return notify_fail("你走了半天，終于走出了這片樹林。\n");
                 } else
                if( query_temp("zhongnan/tree", me)<i )
                {
                        message("vision",query("name", me)+"胡亂地在樹林中鑽來鑽去。\n",environment(me),me);
                        msg="你走了幾步，發現你走進了樹林的更深處。\n";
                } else
                if( query_temp("zhongnan/tree", me) == i )
                {
                        message("vision",query("name", me)+"鑽進了樹林，可是一會兒又走回了原地。\n",environment(me),me);
                        msg="你鑽進了樹林，可是一會兒又走回了原地。\n";
                } else
                {
                        message("vision",query("name", me)+"似乎胸有成竹地鑽進了樹林裡。\n",environment(me),me);
                        msg="你走了幾步，發現這兒你似乎曾經走過。\n";
                }
                return notify_fail(msg);//::valid_leave(me,dir);
        }else 
        if( query_temp("dugu_visit", me) == 1 )
        {        if(dir=="north")
                {
                        message("vision",query("name", me)+"向樹林深處走去，消失樹林之中……\n",environment(me),me);
                        me->move(__DIR__"qiaobi");
                        delete_temp("dugu_visit", me);
                        message("vision",query("name", me)+"從樹林中走了過來。\n",environment(me),me);
                        return notify_fail("你往北走了裡許，來到了一座峭壁之前。\n");
                } else
                {
                        message_vision("$N在樹林裡信步而行，邊走邊欣賞風景。\n",me);
                        return ::valid_leave(me,dir);
                }
        }
}
