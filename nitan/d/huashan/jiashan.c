// jiashan.c
inherit ROOM;
void create()
{
        set("short","假山小池");
        set("long", @LONG
這是另一個小園子，裡頭有個小池塘。四周布有假山，增添林園
美景。下雨時雨水落入溪塘中，清脆的水珠聲有如玉珠落盤般悅耳。
水氣朦朧中抬頭西望，只見遠處蒼山如黛，若隱若現，雨景妙趣無窮。
LONG );
        set("exits",([
                "east" : __DIR__"houyuan",
        ]));
        set("outdoors", "huashan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
 