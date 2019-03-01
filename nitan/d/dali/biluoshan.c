//Room: /d/dali/biluoshan.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","碧羅山下");
        set("long",@LONG
此間正處碧羅山腳下，幾層梯田沿山坡而上，土地看來一點也不
肥沃，作物較稀疏。烏夷地區農業頗落後，行換季輪耕，村民在不同
的季節耕作不同的田地，許多附近的梯田正荒蕪著無人耕作。
LONG);
        set("objects", ([
           __DIR__"npc/nongfu": 1,
        ]));
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "west"      : __DIR__"yixibu",
        ]));
	set("coor/x", -19190);
	set("coor/y", -6900);
	set("coor/z", 20);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/bls", 1, me);
        }
}