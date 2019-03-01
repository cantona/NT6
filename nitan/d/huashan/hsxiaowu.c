inherit ROOM;

void create()
{
    set("short", "後山小屋");
        set("long", @LONG
後山小屋是華山兩位長老的避世居所。擺設簡單，卻清雅自然。
小屋外有個小池塘，幾只鶴有的在池塘邊飛舞，有的站在池塘邊歇息。
兩位長老不喜歡外人打擾，當今華山掌門也甚少到訪。
LONG );

    set("exits", ([
        "southdown" : __DIR__"chaopath2",
    ]));

    set("objects", ([
        CLASS_D("huashan") + "/gao-laozhe" : 1,
        CLASS_D("huashan") + "/ai-laozhe" : 1,
    ]));

    set("no_clean_up", 0);

    setup();
    replace_program(ROOM);
}
