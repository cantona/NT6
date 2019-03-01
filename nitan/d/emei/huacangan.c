inherit ROOM;

void create()
{
        set("short", "華藏庵");
        set("long", @LONG
華藏庵是金頂的主要建築，規模宏大，中祀普賢菩薩，旁列萬佛。
華藏庵後邊是睹光台，旁邊是臥雲庵。
LONG );
        set("outdoors", "emei");
        set("exits", ([
                "northwest" : __DIR__"jinding", 
                "southwest" : __DIR__"duguangtai",
                "enter"     : __DIR__"hcazhengdian",
        ]));

        set("no_clean_up", 0);
        set("coor/x", -560);
        set("coor/y", -320);
        set("coor/z", 220);
        setup();
        replace_program(ROOM);
}