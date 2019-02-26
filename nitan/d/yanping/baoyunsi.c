// Room: /d/yanping/baoyunsi.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "寶雲寺");
        set("long", @LONG
寶雲寺位於九峯山上，始建於唐朝龍紀元年，原名南峯普濟院，元
代改稱“三寺”，遂有“三寺雲深”景名。寺廟宏偉富麗，金碧輝煌，
寺旁古木參天，夕雲起處，若隱若現。
LONG );
        set("exits", ([
                "northdown" : __DIR__"9fengshan",
        ]));
        set("objects", ([
                "/d/hangzhou/npc/seng" : 1,
        ]));
        set("outdoors", "yanping");
        set("coor/x", 1480);
        set("coor/y", -6230);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}