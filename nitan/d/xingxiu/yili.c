// /d/xingxiu/beijiang.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "伊犁城");
        set("long", @LONG
伊犁位于北面天山雪水匯集而成的伊犁河以北。城內聚居著維吾爾
族人，人來人往，十分熱鬧。只是他們說的話你聽不懂。城西有家小店
舖，西北邊人聲鼎沸，好像在舉行什麼比賽。北邊是一家客棧。客棧內
附一家馬廄。東面有家院落，院門口有棵大樹。
LONG );
        set("exits", ([ 
            "west"      : __DIR__"store",
            "east"      : __DIR__"house",
            "south"     : __DIR__"yiligate",
            "northwest" : __DIR__"saimachang",
            "north"     : __DIR__"kezhan",
        ]));
        set("objects", ([
                __DIR__"npc/woman": 2 ]) );
//        set("no_clean_up", 0);
        set("outdoors", "xiyu");

        set("coor/x", -39000);
        set("coor/y", 13000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
