// xiaodao1.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "林間小道");
        set("long", @LONG
這是一條長長的林間小道，從東邊一直通到西邊，一眼望去，看不
到路的盡頭。兩旁百花爭艷。令人留連忘返。
LONG
        );
        set("exits", ([
                "east" : __DIR__"qingcaop",
                "west" : __DIR__"xiaodao2",
        ]));
         set("objects", ([
                CLASS_D("xiaoyao")+"/goudu": 1,
        ]));
        set("outdoors", "xiaoyao");
//         set("no_clean_up", 0);
        set("coor/x", 70);
        set("coor/y", -500);
        set("coor/z", 0);
        setup();
}

int valid_leave(object me,string dir)
{
        if( dir == "west" && (!query("family", me) || query("family", me)["family_name"] != "逍遙派") )
                return notify_fail("路中間豎著一個“小牌”，上面寫到：非逍遙派弟子，請勿進入。\n");
        return ::valid_leave(me,dir);
}