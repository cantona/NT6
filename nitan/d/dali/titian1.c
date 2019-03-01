//Room: /d/dali/titian1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","梯田");
        set("long",@LONG
東瀘水河谷氣候較溫暖，烏夷先民沿山坡開墾了不少梯田。此間
乃是低坡，層層梯田沿坡而上，土地看來並不肥沃，作物較稀疏，烏
夷地區農業頗為落後，多行換季輪耕，附近山上的一些梯田在這個季
節正荒蕪著。
LONG);
        set("objects", ([
           __DIR__"npc/nongfu": 1,
        ]));
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "west"  : __DIR__"zhenxiong",
        ]));
	set("coor/x", -19200);
	set("coor/y", -6860);
	set("coor/z", 20);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/tt", 1, me);
        }
}