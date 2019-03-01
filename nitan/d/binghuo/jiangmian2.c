// Room: /binghuo/jiangmian2.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "錢塘江面");
        set("long", @LONG
江船穿波越浪下駛。半個多時辰之後，上湧的潮水反退出海，順
風順水，舟行更遠。遠遠望見錢塘江口的東海之中，有個荒涼小島，
山石嶙峋，向無人居。那就是王盤山島。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "wangpan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
