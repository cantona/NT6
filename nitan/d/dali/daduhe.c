//Room: /d/dali/daduhe.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","大渡河邊");
        set("long", @LONG
大渡河是蜀中名川，河谷狹窄，水流湍急，極難渡過，只有遠方
下游才有河面寬闊處，可行船渡河。此處是河谷轉彎的淺灘，水流稍
緩，不過仍可見滔滔河水洶湧而去，對岸可望而不可及。南邊山上有
座石城。
LONG );
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "southup"  : "/d/dali/wunong",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19180);
	set("coor/y", -6770);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}