//Room: /d/dali/yulin.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","榕樹雨林");
        set("long",@LONG
這是一片濕潤的雨林，腳下水汪汪的無路可行，十數丈高的巨大
榕樹盤根錯節，樹幹粗得幾個人合抱也圍不住。榕樹的樹枝下垂到泥
水中反過來紮根，成為特意的景致。雨林雖然少有走獸，卻是飛禽聚
居的樂土，身手靈活的台夷獵人攀越在大榕樹浮露的根枝上，用短弩
射獵飛鳥。
LONG);
        set("objects", ([
           __DIR__"npc/lieshou": 1,
        ]));
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "west"      : __DIR__"luwang",
        ]));
	set("coor/x", -19110);
	set("coor/y", -6960);
	set("coor/z", 0);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/yl", 1, me);
        }
}