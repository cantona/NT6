inherit ROOM;

void create()
{
        set("short", "長安戲院");
        set("long", @LONG
這裡就是京城裡著名的長安戲院，是京城百姓休息和娛樂的佳所。
戲台上面幾個戲子正在唱戲。台下黑壓壓的一片都是人。唱到妙處，
台下的觀眾們禁不住大聲喝採。北邊一條小道通往戲院的後台。
LONG );
        set("exits", ([
                "north" : __DIR__"xiyuanup",
                "west"   : __DIR__"wang_10",
        ]));
        set("objects", ([
                __DIR__"npc/guanzhong" : 3,
                __DIR__"npc/xianren" : 1,
                __DIR__"npc/jumin1" : 1,
        ]));
        

	set("coor/x", -2760);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "north" && userp(me))
        {               
                message_vision(  
                        "只聽嘩啦啦一片掌聲，觀眾們一起鼓掌。有人大聲說道："
                        "凈一凈，請看這位" + RANK_D->query_respect(me)+ "表演。\n",
                        this_player());
                return ::valid_leave(me, dir);
        }
        else return 1;
}