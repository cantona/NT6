//Room: /d/dali/gaolishan2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","高黎山密林");
        set("long",@LONG
高黎山上地勢險惡、樹大林深，附近幾乎毫無人煙。地處高山四
季皆寒，熊虎等猛獸時常出沒，只有勇敢的獵人才敢上這裡來。東面
下山即是瀘水谷地。
LONG);
        set("objects", ([
           "/d/hangzhou/npc/laohu": 1,
        ]));
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "east"  : __DIR__"gaolishan1",
        ]));
	set("coor/x", -19230);
	set("coor/y", -6890);
	set("coor/z", 30);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/gls", 1, me);
        }
}