inherit ROOM;

void create()
{
        set("short", "中州道");
        set("long", @LONG
這條連接中州和揚州的要道來往車馬不斷。南面是中州城
的北門，再向北通向長江邊的渡口。道路兩邊是一望無邊的綠
色沃野。好一片江南風光。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"to_zhongzhou2",
                  "south":__DIR__"beimen",
        ]));
        set("outdoors", "zhongzhou");

        set("coor/x", -150);
        set("coor/y", 30);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}