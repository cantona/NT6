// This program is a part of NT MudLIB

inherit ROOM;
void create()
{
        set("short", "林間小屋");
        set("long", @LONG
你走進了一間小屋。四周牆壁都由青竹篾編成，窗外是一望無際的
竹林。屋裡的桌椅、床舖均為竹制。但一陣撲鼻而來的狗肉香味，卻顯
得與這清雅的氣氛格格不入。
LONG );
        set("region", "yz_zone");
        set("exits", ([ /* sizeof() == 1 */
            "west" : __DIR__"gbandao"
        ]));
        set("objects", ([
                CLASS_D("gaibang") + "/first" : 1,
                "/d/city/obj/zhubang": 1,
                "/d/city/obj/gourou": 1,
                "/d/city/obj/jiudai": 1,
                "/d/city/obj/jitui": 1
        ]));

        set("coor/x", 71);
        set("coor/y", 61);
        set("coor/z", 0);
        setup();

        (CLASS_D("gaibang") + "/hong")->come_here();
}

void reset()
{
        ::reset();
        (CLASS_D("gaibang") + "/hong")->come_here();
}
