// /d/xingxiu/silk4.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "絲綢之路");
        set("long", @LONG
這是聞名中外的絲綢商道。風沙彌漫，一片荒涼景象。南面連綿的
祁連山脈在陽光的照射下好像是一條玉帶。只是有幾人合抱之粗的古老
胡楊，仍然挺立在荒原上，笑迎風沙，頻頻招呼行人。西邊是一片黃沙，
傳過沙漠就可以到達崑崙山脈。
LONG );
        set("outdoors", "silu");

        set("exits", ([
                "southeast" : __DIR__"shimen",
                "northwest" : __DIR__"shazhou",
                "west"      : "/d/mingjiao/westroad1",
        ]));
        set("objects", ([
                __DIR__"npc/trader" : 1,
        ]));
        set("coor/x", -22500);
        set("coor/y", 800);
        set("coor/z", 0);
        setup();
//        replace_program(ROOM);
}

#include "/d/xingxiu/job2.h";
