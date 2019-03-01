//Room: /d/dali/sima.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","司馬堂");
        set("long", @LONG
這裡是大理國司馬堂。大理東北強宋，西北吐蕃，歷年來邊疆寧
靖，皆司馬勞頓之功。蓋吐蕃垂涎大理已久，每每強辭脅迫，大理不
得不重兵于西北。
LONG );
        set("objects", ([
            CLASS_D("dali")+"/fanye" : 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "west"  : "/d/dali/zonglichu",
        ]));
	set("coor/x", -19111);
	set("coor/y", -6851);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}