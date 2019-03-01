// Room: /d/huangshan/wenzhu.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "文殊院");
        set("long", @LONG
相傳當年普門法師所建，供奉著文殊菩薩，所以叫文殊院，當年香
火盛極一時，可惜後來因武林正邪勢力在玉屏峰決戰，殃及文殊院，寺
中從此一蹶不振。遊人至今仍可從牆壁的痕跡遙想當年一戰的慘烈。
LONG
        );
        set("exits", ([ 
                "southwest" : __DIR__"yingke",
                "east"      : __DIR__"yixian",
        ]));
        set("outdoors", "huangshan");
        set("no_clean_up", 0);
        set("coor/x", -575);
        set("coor/y", -1050);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}