// Room: /d/chengdu/liangting.c
// Last Modifyed by Winder on Jan. 4 2002

inherit ROOM;

void create()
{
        set("short", "涼亭");
        set("long", @LONG
這是一座木製的涼亭，亭前樹着一塊石碑，石碑上用隸書體寫着“
日照亭”三個大字，來往的行人、遊客大多在此處駐足歇腳，亭邊植着
大量的花木，引來了一些蝶鳥在其中嬉戲。
LONG        );
        set("outdoors", "chengdu");
        set("exits", ([
                "southeast" : __DIR__"road1",
        ]));
        set("objects", ([
                __DIR__"npc/xiaofan" : 1,
                __DIR__"npc/youke" : 1,
        ]));
        set("coor/x", -15170);
	set("coor/y", -1810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}