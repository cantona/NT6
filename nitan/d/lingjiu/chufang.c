inherit ROOM;

void create()
{
        set("short", "藕香榭");
        set("long", @LONG
這是間廚房，濃郁的飯菜香味一個勁地鑽進你的鼻子，你彷彿聽
到『咕咕』的響聲，環顧四周不知來源。原來是你的肚子作怪。
LONG );
        set("exits", ([
                "east" : __DIR__"changl6",
        ]));
        set("objects", ([
                __DIR__"npc/lisao" : 1,
                __DIR__"obj/suanmei" : 2,
                __DIR__"obj/gao" : 2,  
        ]));

        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}