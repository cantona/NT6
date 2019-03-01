// Room: /d/songshan/qianting.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "前庭");
        set("long", @LONG
這裡是峻極禪院山門內前庭。庭院中青石舖地、古柏森森，可容納
數百人集會。內裡是禪院大殿，兩廂是一些低矮小房。
LONG );
        set("exits", ([
                "north"     : __DIR__"chanyuan",
                "southdown" : __DIR__"junjigate",
        ]));
        set("objects", ([
                __DIR__"npc/shi": 1,
                CLASS_D("songshan")+"/di" : 1,
        ]));
        set("outdoors", "songshan");
        set("coor/x", -20);
        set("coor/y", 860);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}