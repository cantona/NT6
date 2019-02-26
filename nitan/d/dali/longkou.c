//Room: /d/dali/longkou.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","龍口城");
        set("long",@LONG
這裏已到大理南疆了，龍口城南臨元江，屬臨江路。大理國南部
雖廣有千多裏，但大城鎮較稀少，此地雖離大理中心不遠，卻也算南
部的重要關口之一了，是和南方臨國通商的口岸。由此北去二十五里
即是喜州城，南邊沿元江有不少台夷村莊。大理官府在此有些駐軍。
LONG);
        set("objects", ([
           __DIR__"npc/bing": 2,
        ]));
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "north"      : __DIR__"feilihueast",
        ]));
	set("coor/x", -19120);
	set("coor/y", -6980);
	set("coor/z", 0);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/lk", 1, me);
        }
}