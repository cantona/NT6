// Room: /d/suzhou/xiyuan.c
// Date: May,31 1998 Java

inherit ROOM;

void create()
{
        set("short","戲園子");
        set("long",@LONG
這是一座蘇州城裡鼎鼎有名的戲園，戲園中生，旦，凈，墨，醜一
應俱全，場中一個大戲台，台上正在唱著《遇長春》，台下不時地傳來
票友們的叫躍，喝彩聲。你也忍不住想坐下來看看戲，放鬆一下筋骨。
LONG);
//        set("no_clean_up", 0);
        set("objects", ([
                __DIR__"npc/piaoyou": 3,
        ]));
        set("exits",([ /* sizeof() == 1 */
                "northeast" : __DIR__"beidajie1",
                "north"     : __DIR__"majiu",
        ]));
	set("coor/x", 1100);
	set("coor/y", -1050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}