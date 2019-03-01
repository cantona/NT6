// Room: yaodian.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "濟世堂藥店");
        set("long", @LONG
濟世堂藥店賣很多中原買不到的藥。託唐門的福，生意一直都很
好。一走進這家藥店，就聞到一股股濃烈刺鼻的藥味。你正奇怪藥店
夥計怎麼能忍受，就看到藥店裏還有一些人正拿奇怪的眼光看你。他
們的腰間鼓鼓囊囊的，顯然不是好惹的。
LONG );
        set("objects", ([
                __DIR__"npc/huoji" : 1,
        ]));
        set("exits", ([
                "southeast" : __DIR__"westroad3",
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15250);
	set("coor/y", -1810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}