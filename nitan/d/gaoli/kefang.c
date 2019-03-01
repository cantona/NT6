// /d/gaoli/jefang
// Room in 高麗
inherit ROOM;

void create()
{
        set("short", "客房");
        set("long", @LONG
這是一間很大的客房，陳設十分華麗。靠牆放了幾張大床，客人們
蓋著大被子睡的正香，滿屋子都是呼呼的打酣聲。西邊有張床是空的，你
躡手躡腳地走了過去。
LONG
        );

        set("sleep_room", "1");
        set("no_fight", "1");
        set("hotel",1);

        set("exits", ([
        "down" : __DIR__"yingbinguan",
        ]));

        setup();
}

int valid_leave(object ob,string dir)
{
   ob->delete_temp("rent_paid");
   return ::valid_leave(ob,dir);
}