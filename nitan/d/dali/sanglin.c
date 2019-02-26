//Room: /d/dali/sanglin.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","桑林");
        set("long",@LONG
一大片桑樹林生長在低山的緩坡山腰上。養蠶、紡絲是擺夷族的
重要副業，擺夷婦女大都擅織絲，編織自己穿着的短裙，也用來和鄰
近部落交換些其它物品。一羣擺夷姑娘正在林間忙着採摘桑葉。
LONG);
        set("objects", ([
           __DIR__"npc/caisangnu": 1,
        ]));
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "northdown"  : __DIR__"yangzong",
        ]));
	set("coor/x", -19020);
	set("coor/y", -6890);
	set("coor/z", 20);
	setup();
}
void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/sl", 1, me);
        }
}