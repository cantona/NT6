#include <ansi.h>

inherit BUILD_ROOM;

void create()
{
        set("short", "東海之濱");
        set("long", @LONG
這裡是大海之濱，浪花拍打著礁石，發出陣陣響聲，海面上一群
群海鷗『歐歐。。』地叫著，不時有魚兒躍出海面，濺起層層的浪花。
邊上有艘大船(chuan)， 船上坐著幾個漁夫打扮的人，乘船可渡過大
海到達海的另一端。西面一直走就是燕京了，東面是一望無際的大海。
極目眺望不禁讓人心胸開擴，神舒意暢，的確是一個好居處。
LONG );
        set("exits", ([
                "west" : "/d/beijing/road10",
                "north" : "/d/tulong/tulong/haian",
        ]));
        set("item_desc", ([
                "chuan" : "一艘大帆船，造得很結實，看來可以出遠海的。\n",
        ]));
        set("objects", ([
                "/d/beijing/npc/flowerg":1,
                "/d/shenlong/npc/chuanfu" : 1,
                "/d/shenlong/npc/xiucai" : 1,
        ]));
        set("max_room", 5);
        set("outdoors", "beijing");
        set("navigate",1);
        set("opposite","/d/shenlong/haitan");
	set("coor/x", -2760);
	set("coor/y", 7550);
	set("coor/z", 0);
	setup();
}

/*
// 路徑改在杭州錢塘江畔
void init()
{
        object dao, room, ren, ding;
        object me = this_player();
        room = get_object("/d/tulong/tulong/huichang");
        ding = present("chang jinpeng", room);

        if (objectp(ding)) 
        dao = present("tulong blade", ding);
        if (! dao)
        {
                ding = present("ding", room);
                if (objectp(ding)) 
                dao = present("tulong blade", ding);
        }

        if (objectp(dao))
        {
                room = get_object("/d/tulong/tulong/daobian");
                ren = present("bai guishou",room);
                tell_object(me, HIC "你看見沙灘上停泊滿了海船，所有的海船全部標記著天鷹教的標記。\n"NOR);
                tell_object(me, CYN "白龜壽對你說道：我天鷹教得到屠龍寶刀，這位武林同道可願意參加揚刀立威大會？\n"NOR);
                message("vision", HIR"\n【倚天屠龍】" NOR+WHT "白龜壽仰天一聲長笑。\n" NOR, all_interactive());
                message("vision", HIR"\n【倚天屠龍】" NOR+WHT "白龜壽：我天鷹教得到屠龍寶刀，今在王盤山島舉行揚刀立威大會。\n" NOR, all_interactive());
                remove_call_out("mes");
                call_out("mes",1,this_player());
                set_temp("to_wang", 1, this_player());
                add_action("do_accept", ({ "accept", "jieshou" }));
        }
        add_action("do_enter", "enter");
}

void mes(object me)
{
      if (!me) return;
        message_vision(HIR "你願意參加(accept/jieshou)王盤山島揚刀立威大會嗎？\n"NOR, me);
}

int do_accept()
{
        object me = this_player();
        if( query_temp("to_wang", me) )
        {
                tell_object(me, HIR "你決定去參加揚刀立威大會。\n" NOR);
                remove_call_out("moveto");
                call_out("moveto",10,me);
        }
        return 1;
}

int moveto(object me)
{
        me->move("/d/tulong/tulong/boat");
        message_vision(HIC "\n$N坐上了天鷹教的大船，聽到舵子手喊道：“開船了！”，大船慢慢的向大海駛進。\n"NOR, me);
        remove_call_out("arrive1");
        call_out("arrive1",10,me);
        return 1;
}

int arrive1(object me)
{
        message_vision(HIB "\n天鷹教的大船在大海上慢慢的漂著......$N不禁感到睡意朦朧。\n"NOR, me);
        remove_call_out("arrive2");
        call_out("arrive2",10,me);
        return 1;
}

int arrive2(object me)
{
        message_vision(HIY "\n$N突然聽到一聲驚喝：“到了，下船吧”！$N頓時提起精神，跟著天鷹教教眾下了船。\n"NOR, me);
        me->move("/d/tulong/tulong/daobian");
        tell_object(me, HIR "\n你突然想到：最好先砸了其他人的船(break boat)，讓他們無路可逃。\n" NOR);
        return 1;
}


int do_enter ( string arg )
{
        object ob ;
        string dir;
        if (! arg || arg != "chuan")
        {
                tell_object(this_player() , "你要 enter 哪兒？\n" ) ;
                return 1 ;
        }
        ob = this_player () ;
        message_vision("船夫一見有人上船，忙叫了一聲：開船嘍！\n", ob);
        message_vision("船夫升起帆，船就向東方航行。\n", ob);
        ob->move("/d/mingjiao/lsd/dahai") ;
        tell_object(ob, BLU "你在海上航行了三天三夜.......\n" NOR ) ;
        call_out("home", 10 , ob );
        return 1 ;
}
void home( object ob )
{
        tell_object(ob , "大船終于抵達了南海岸邊。你走下船來。\n" ) ;
        ob->move("/d/mingjiao/lsd/anbian") ;
}

*/
void init()
{
        add_action("do_enter", "enter");
}

int do_enter(string arg)
{
        object me;

        me = this_player();

        if (! arg || arg != "haigang")
	        return notify_fail("你要到海港麼，請輸入 enter haigang。\n");

        me->move("/d/shenlong/japangames/japan0");

        return 1;
		
}
