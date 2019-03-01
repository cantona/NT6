//Room: /d/dali/dadieshui.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","大疊水瀑布");
        set("long", @LONG
延山間小路越丘陵，過村莊，穿田野，約二，三裡後，隱隱聽見
水流的轟鳴，續前進，在一片坡地的前端，呈現倒丫字形深箐，那巨
大的轟鳴聲，就是從這箐溝裡傳出的。延坡上的之字形小路攀籐扶石
眼前。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "northwest"  : "/d/dali/chahuashan6",
            "eastdown"   : "/d/dali/xiaojing",
            "southdown"  : "/d/dali/qingxi",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19110);
	set("coor/y", -6870);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}