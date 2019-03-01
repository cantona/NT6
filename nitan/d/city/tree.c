#include <ansi.h>
#include <room.h>
inherit CREATE_CHAT_ROOM; 

void create()
{
        set("short", "大榕樹上");
        set("long", @LONG
這裡是大樹的頂端，四周全是濃密的枝葉和濕漉漉的苔蘚。一陣
微風吹來，樹葉發出唰啦啦的聲音。從上面望下去你只覺得一陣眼暈，
心想還是趕快下去吧。
LONG );
        set("no_fight", 1); 
        set("valid_startroom", 1); 
        set("no_sleep_room",1); 
        set("outdoors", "city");
        set("item_desc", ([
                "tree" : GRN "\n這是一棵巨大古老的大榕"
                         "樹，枝葉非常的茂密。\n" NOR,
        ]));
        set("exits", ([
                "down" : __DIR__"guangchang",
                "up"  : __DIR__"tree2",
        ]));
        set("objects", ([
               // CLASS_D("xiakedao") + "/shi" : 1,
        ]));
        setup();
        call_other("/clone/board/comm_b", "???");
}

void init() 
{
        add_all_action(); 
        add_action("do_jump", ({ "tiao", "jump" }) );
        add_action("do_climb", ({ "pa", "climb" }) );
}

int do_climb(string arg)
{
        object me;
        me = this_player();

        if (! arg || arg == "")
                return 0;

        if (arg == "tree" || arg == "up")
        {
                if( objectp(query_temp("is_riding", me)) )
                        return notify_fail("沒聽說過有人能騎坐騎還能爬樹的。\n");

                if (me->is_busy())
                {
                        return notify_fail("你的動作還沒有完成，不能移動。\n");
                        return 1; 
                }

                if( query("gender", me) != "女性" )
                        message("vision",
                                me->name() + "戰戰兢兢地拉著大榕樹的盤根，屁股一扭一扭地往上爬。\n",
                                environment(me), ({me}) );
                else 
                if( query("age", me)<40 && query("per", me)>24 )
                        message("vision",
                                me->name() + "輕輕一跳，衣裙飄飄，象仙子般飛上大榕樹。\n",
                                environment(me), ({me}) );
                else 
                        message("vision",
                                me->name() + "戰戰兢兢的抓住樹幹往上爬去。\n", 
                                environment(me), ({me}) );        

                me->move(__DIR__"tree2");
                
                if( query("gender", me) != "女性" )
                        message("vision",
                                me->name() + "氣喘噓噓地爬了上來。\n",
                                environment(me), ({me}) );
                else 
                if( query("age", me)<40 && query("per", me)>24 )
                        message("vision","一陣清香飛來，你定眼一看，"+
                                me->name() + "已經婷婷玉立在你眼前。\n",
                                environment(me), ({me}) );
                else  
                        message("vision", me->name() + "戰戰兢兢地從下面爬了上來。\n", 
                                environment(me), ({me}) );
                                
                return 1;
        }
}

int do_jump(string arg)
{
        object me;
        me = this_player();
        
        if( !arg || arg != "down") return notify_fail("你要往哪跳？\n");
        
        if( me->is_busy() )  
                return notify_fail("你正忙著呢！\n");
        
        message("vision",
                me->name() + "猶豫了一下，鼓起勇氣，跳了下去。\n“□”的一巨響，似乎聽到"+me->name()+"慘嚎了一聲!\n",
                environment(me), ({me}) );
        
        me->move(__DIR__"guangchang");
        message("vision",
                me->name() + "慘嚎一聲，從樹上掉了下來。\n",
                environment(me), ({me}) );
        
        return 1;
}

int valid_leave(object me, string dir)
{

        if ( dir=="down" && !wizardp(me))
                return notify_fail("盤根不知道給哪個壞家伙砍斷了猓□蠢粗荒跳爬(tiao)下去！\n");

        if ( dir=="up" && !wizardp(me))
                return notify_fail("這裡沒法直接走，看來你只能爬(climb)上去！\n");

        return 1;
}
