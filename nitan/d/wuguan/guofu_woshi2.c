inherit ROOM;

void create()
{
    	set("short","休息室");
        set("long", @LONG
這裡是郭府內的休息室，屋子有點點舊，但是打掃的非常
幹凈，一排床舖靠牆擺著，東面過去也是一間休息室，不斷的
有人進來休息或醒後離去，你悄悄的找個空舖睡了下來。
LONG);
        set("exits", ([
            "west" : __DIR__"guofu_woshi1",
        ]));
        set("no_fight", 1);
        set("sleep_room", 1);
        setup();
}