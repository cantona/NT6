//Room: /d/dali/baiyiziguan.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","擺夷字館");
        set("long", @LONG
擺夷文字有悠久的歷史。撒尼敘事長詩『阿詩瑪』，武定石刻『
風詘碑』，祿勸石刻『鐫字崖』都是著名的擺夷文獻。擺夷文一般是
由左向右豎行書寫，用毛筆或竹簽寫在紙或白布上。這兒就有一擺夷
學者為人代寫書信，告文，契約等等。
LONG );
        set("exits",([ /* sizeof() == 1 */
            "south"  : "/d/dali/dahejieeast",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19120);
	set("coor/y", -6890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}