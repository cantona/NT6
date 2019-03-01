//TOHTQ3.C

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
山路掩在土層下，前面似乎沒有路了。滿山樹林密集，鴉鳥群集，
林中煙霧飄盪，不知所之。
LONG );
        set("exits", ([
                "southup" :__DIR__"tohtq2",
                "enter"   :__DIR__"tohtq4",
        ]));
        set("outdoors", "mingjiao");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}