//Room: /d/dali/dehuabei.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","南詘德化碑");
        set("long", @LONG
南詘閣邏風于大唐天寶年間，同大唐兩次交戰，殲唐軍十六萬。
過後，閣邏風有悔意，為一時交惡，『豈顧前非，而忘大禮』。于是，
派人收拾唐軍陣亡將士，『祭而葬之，以存恩舊』，同時，令人撰文，
詳記天寶戰爭的近因和結果，表達不得已而叛唐的苦衷，將它刻成巨
碑，于天寶十一年立于王都太和城國門外。
LONG );
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/road3",
            "south"  : "/d/dali/taihecheng",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19160);
	set("coor/y", -6830);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}