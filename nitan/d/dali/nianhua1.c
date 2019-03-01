//Room: /d/dali/nianhua1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","拈花後院");
        set("long",@LONG
你舉步入寺，只聽得叮叮兩聲清磬，悠悠從後院傳出，霎時之間，
只感遍體清涼，意靜神閒。你踏實著寺院中落葉，走進後院。你站在
庭中，眼見庭中一株公孫樹上一片黃葉緩緩飛落，俗念全消。
LONG);
        set("outdoors", "daliw");
        set("no_clean_up", 0);
        set("exits",([ /* sizeof() == 1 */
            "out"  : __DIR__"nianhuasi",
        ]));
	set("coor/x", -19161);
	set("coor/y", -6881);
	set("coor/z", 9);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/nh1", 1, me);
        }
}