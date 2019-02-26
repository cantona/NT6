//Room: /d/dali/chahuashan3.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","茶花山");
        set("long", @LONG
你走在茶花山上，這裏遍地是生長茂盛的茶花。當然，大部分是
凡品，但偶爾也會有一兩株佳品藏匿其中。西望不遠是大理城的北門。
有一些毒蜂在飛來飛去，似乎毒蜂巢(fengchao)就在附近茶花叢裏。
LONG );
        set("objects", ([
           "/d/dali/npc/bee": 3,
        ]));
        set("item_desc", ([
           "fengchao" : "這是一個野毒蜂的蜂巢。\n",
        ]));
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "south"     : "/d/dali/chahuashan2",
        ]));
	set("coor/x", -19140);
	set("coor/y", -6850);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}