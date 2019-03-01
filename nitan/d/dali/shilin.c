//Room: /d/dali/shilin.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","路南石林");
        set("long", @LONG
在綠樹叢中隨處可見峭石插天，石筍叢集，石柱挺立，奇異詭質，
各呈異姿。這裡石峰攢聚，如劍戟排空，莽莽蒼蒼，儼然一片林海，
蔚為壯觀。更加叢山之中或飛瀑直瀉，成疊水噴雲，或山泉匯聚，成
明鏡長湖。
LONG );
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "northup"  : "/d/dali/changhu",
            "south"    : "/d/dali/cangshan",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19160);
	set("coor/y", -6810);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}