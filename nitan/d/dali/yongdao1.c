//Room: /d/dali/yongdao1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","甬道");
        set("long", @LONG
這是鎮南王府的甬道。兩邊是密密的樹林，風吹得樹葉沙沙聲響
石砌的甬道路面兩側，是如茵的綠草，點綴着一星半點的小花，周圍
十分安靜。唯獨西北角傳來一陣陣打鬥的聲音，在這謐靜的環境越發
聽得真切。
LONG );
        set("outdoors", "daliwang");
        set("exits",([ /* sizeof() == 1 */
            "northeast" : "/d/dali/yongdao2",
            "northwest" : "/d/dali/liangong",
            "south"     : "/d/dali/tingfang",
        ]));
	set("coor/x", -19101);
	set("coor/y", -6831);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}