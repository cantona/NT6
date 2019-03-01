inherit ROOM;

void create()
{
        set("short", "蓼風軒");
        set("long", @LONG
這是靈鷲宮弟子的兵器庫，你環顧四周，發現牆上嵌滿了各式兵
器，仔細一看，原來滿牆滿壁竟隨依各般兵器之形摳出槽子，兵刃就
懸于槽內。
LONG );
        set("exits", ([
                "east" : __DIR__"changl5",
        ]));
        set("objects",([
                "/d/village/obj/zhujian" : 4,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}