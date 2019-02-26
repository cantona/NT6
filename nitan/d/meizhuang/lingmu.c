// lingmu.c
inherit ROOM;

void create()
{
        set("short", "古皇陵");
        set("long", @LONG
你一走到這裏，突然一片明亮，原來這裏竟然是古代蠶叢王的陵
墓，中間停放着一具棺木，棺木的上方懸掛着一顆鵝蛋一般大小的夜
明珠，把這裏照得異常明亮，棺木的正中放着一本書，書看起來很陳
舊，似乎是一位前輩異人留下的。 
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "south" : __DIR__"didao5",
            "out" : __DIR__"hupan",
        ]));
        set("objects", ([ /* sizeof() == 1 */
            "/clone/book/qunxing-tu.c" : 1,
        ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
