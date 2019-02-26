// Room: /city/kefang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
        set("short", "唐門客店二樓");
        set("long",
"這是一間很大的客房，陳設十分簡陋。靠牆放了十幾張小木牀，不少\n"
"客人正和衣而卧，滿屋子都是呼呼的打酣聲。西邊有張牀是空的，你躡手\n"
"躡腳地走了過去。\n"
);

        
        set("valid_startroom", 1);
        set("sleep_room", "1");
        set("no_fight", "1");
        set("hotel",1);

        set("exits", ([
                "down" : __DIR__"kedian",
        ]));

        set("area", "汴梁");

        setup();
}

int valid_leave(object me, string dir)
{
        if( dir == "down")delete_temp("rent_paid", me);

        return ::valid_leave(me, dir);
}


