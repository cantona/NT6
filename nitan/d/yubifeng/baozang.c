// /yubifeng/baozang.c
// Last modified by winder 2003.9.2

inherit ROOM;

void create()
{
        set("short", "闖王寶藏");
        set("long", @long
一踏進石門，一陣金光照射，人人眼花撩亂，凝神屏氣，個個張大
了口合不攏來。原來裏面竟是個極大的洞穴，四面堆滿了金磚銀塊，珍
珠寶石，不計其數。只是金銀珠寶都隱在透明的堅冰之後。料想當年闖
王的部屬把金銀珠寶藏入之後，澆上冷水。該地終年酷寒，堅冰不融，
金珠就似藏在水晶之中一般。
long );
        set("exits", ([
                "out" : __DIR__"shimen",
        ]));
        set("objects", ([
                JEWELRY_DIR+"maoeryan" : 1,
                JEWELRY_DIR+"manao" : 1,
                JEWELRY_DIR+"biyu" : 1,
                JEWELRY_DIR+"zhenzhu" : 1,
                JEWELRY_DIR+"shanhu" : 1,
                JEWELRY_DIR+"zumulv" : 1,
                JEWELRY_DIR+"feicui" : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", 6110);
        set("coor/y", 5140);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}