// /d/shenlong/lin1.c
// Last Modified by winder on Aug. 18 2002

inherit ROOM;
string* npcs = ({
        __DIR__"npc/jinshe",
        __DIR__"npc/qingshe",
        __DIR__"npc/jinshe",
        __DIR__"npc/qingshe",
        __DIR__"npc/fushe",
});
 
void create()
{
        set("short", "灌木林");
        set("long",@LONG
峰頂北坡是一片陰鬱潮濕的灌木林，小路隱沒在罐木林中。你對這
樣一個孤島上竟有這樣大一片灌木林(bush)感到非常吃驚。四周的密林
中長滿了不知名的雜草。
LONG);
        set("exits", ([
                "southup" : __DIR__"fengding",
	        "south" : __DIR__"haitan",
                "east"  : __DIR__"lin1.1", 
        ]));
        set("item_desc", ([
                "bush" : "這片灌木林太深了，要想過去恐怕只有砍出一條路了(kan)。\n",
        ]));
        set("objects", ([
                __DIR__"npc/dushe" : 1+random(2),
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
        ]) );
        set("outdoors", "shenlong");
        set("coor/x", 4000);
        set("coor/y", 3010);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_kan", "kan");
}

int do_kan ( string arg )
{
        object ob, weapon, me = this_player();
        string dir;

        if( !arg || arg !="bush" ) return notify_fail("你要砍什麼？\n" ) ;
        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("不用武器恐怕不行吧！\n");
        message_vision("$N抽出兵刃，對著灌木叢一陣亂砍。\n", me);
        if( query("neili", me)>100 )
        {
                set("exits/north", __DIR__"lin2");
                message_vision( "$N累得氣喘吁吁，終于砍出一條小路。\n", me);
                addn("neili", -50, me);
                remove_call_out("close");
                call_out("close", 20, this_object());
        }
        else        
        {
                message_vision("$N累得氣喘吁吁，也沒砍開一條路來。\n", me);
                set("neili", 0, me);
        }
        return 1;
}

void close(object room)
{
        message("vision","灌木叢漸漸合攏起來，終于又恢復了原狀。\n", room);
        delete("exits/north", room);
}
