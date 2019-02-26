#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "中央廣場");
        set("long", @LONG
這裏是城市的正中心，一個很寬闊的廣場，鋪着青石地面。遊手
好閒的人常在這裏溜溜達達，經常有藝人在這裏表演。中央一棵大榕
樹(tree)盤根錯節，據傳已有千年的樹齡，是這座城市的歷史見證。
樹幹底部有一個很大的樹洞(dong)。你可以看到北邊有來自各地的行
人來來往往，南面人聲鼎沸，一派繁華景象，東邊不時地傳來朗朗的
讀書聲，西邊則見不到幾個行人，一片肅靜。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "city");
        set("item_desc", ([
                "dong" : WHT "\n這是一個黑不溜湫的大洞，裏面不知道"
                         "有些什麼古怪。\n" NOR,
                "tree" : GRN "\n這是一棵巨大古老的大榕樹，枝葉非常"
                         "的茂密。\n" NOR,
        ]));

        set("exits", ([
                "east" : __DIR__"dongdajie1",
                "south" : __DIR__"nandajie1",
                "west" : __DIR__"xidajie1",
                "north" : __DIR__"beidajie1",
        ]));

        set("objects", ([
                __DIR__"npc/jpl2": 1,
                __DIR__"npc/liapo" : 1,
                "/clone/npc/walker"  : 1,
        ]));

	set("coor/x", 0);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_enter", "enter");
        add_action("do_climb", "climb");
        add_action("do_jump", "jump");
}

int do_enter(string arg)
{
        object me;
        me = this_player();

        if (! arg || arg == "")
        	return 0;

        if (arg == "dong")
        {
                if( objectp(query_temp("is_riding", me)) )
                        return notify_fail("沒聽説過有人能騎坐騎進樹洞的。\n");

                if (me->is_busy())
                {
                        return notify_fail("你的動作還沒有完成，不能移動。\n");
                        return 1; 
                }

                message("vision", HIC + me->name() + HIC "一彎腰往洞裏走"
                                  "了進去。\n" NOR, environment(me), ({me}));

                me->move("/d/gaibang/inhole");
                message("vision", HIC + me->name() + HIC "從洞裏走了進來"
                                  "。\n" NOR, environment(me), ({me}));
                return 1;
        }
}


int do_jump(string arg)
{
        object room, me=this_player();
        if( !arg || arg != "up" ) return 0;

        room = get_object( "/adm/daemons/fairyland_quest/room_door_hj" );
        if( !room ) return 0;

        tell_room(environment(me),query("name", me)+"使勁地往上一跳，突然捲來一陣旋風，"+
                query("name", me)+"頓時被風颳得不知所蹤。\n",me);

        write("你使勁地往上一跳，忽地平地捲起一陣旋風，恍惚中你已來到了「幻境」。\n");
        me->move(room);
        tell_room(room,"忽然一陣旋風襲過，"+query("name", me)+"已出現在這裏。\n",me);
        return 1;
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
                        return notify_fail("沒聽説過有人能騎坐騎還能爬樹的。\n");

                if (me->is_busy())
                {
                        return notify_fail("你的動作還沒有完成，不能移動。\n");
                        return 1; 
                }

                if( query("gender", me) != "女性" )
                        message("vision",
                                me->name() + "戰戰兢兢地拉着大榕樹的盤根，屁股一扭一扭地往上爬。\n",
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

                me->move(__DIR__"tree");
                
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