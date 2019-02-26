// ROOM xuanbing.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;
void create()
{
        set("short", "玄兵古洞");
        set("long", @LONG
這裏是玄兵古洞洞口，裏面傳來陣陣的捶打聲。似乎正在鍛造着什
麼。隱隱的透着一股蕭殺的氣息。
LONG );
        set("region", "xiyu");
        set("exits", ([
                "north" : "/d/xingxiu/luzhou",
                "enter" : __DIR__"xuanbing1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -41200);
        set("coor/y", 8980);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
