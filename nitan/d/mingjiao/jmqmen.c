//jmqmen.c

inherit ROOM;

void create()
{
        set("short", "巨木旗大門");
        set("long", @LONG
這裏是明教巨木旗的大門，莊嚴古樸，門前對插四面鑲綠游龍旗。
碧綠的大門敞開着，似乎看不出有何設防。從門裏望進去，只有一片
蒼翠的樹林。
LONG );
        set("exits", ([
                "enter"  : __DIR__"jmqshulin1",
                "west"   : __DIR__"tojmq3",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}