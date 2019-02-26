//chashi.c                四川唐門—茶室

inherit ROOM;

void create()
{
        set("short", "茶室");
        set("long",
"這裏是蓮藕小築的茶室。通常唐門弟子都喜歡在這裏談天説地，交流\n"
"各自的武功進展，也時常談論一些江湖中恩恩怨怨，從這裏往西是亭榭水閣。\n"
);
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);
        set("item_desc", ([
                "paizi" : "樓上雅房，每夜五十兩白銀。\n",
        ]));
        set("exits", ([        
                        "west" : __DIR__"shuige1",
        ]));
        set("area", "蜀中亭榭水閣");
        setup();
        "/clone/board/tangmen_b"->foo(); 
        replace_program(ROOM);
}